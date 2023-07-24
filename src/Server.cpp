#include "Server.hpp"

WEBPP::Server::Server(
  int domain, // AF_UNIX for local communication, AF_INET for internet domain
  int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
  int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
  int port, // Desired PORT ex 80
  // u_long interface, // Address to bind to.
  int backlog
){
  router = new Router();
  server_socket = new BindingSocket(
    domain, type, protocol, port, /* interface, */ backlog
  );
  server_instance = this;
  shouldRun = true;
}

int WEBPP::Server::accept_client(){
  struct sockaddr_in6 client_address;
  socklen_t client_address_length = sizeof(client_address);
  int client_socket_fd = accept(
    get_socket()->get_sock(),
    (struct sockaddr *)&client_address,
    &client_address_length
  );
  try{
    if(client_socket_fd < 0){
      logger >> "server: accept error";
      throw SocketSystemCallException(strdup("accept error"));
    }
  }
  catch(SocketSystemCallException ssce){
    logger << ssce.what();
    exit(EXIT_FAILURE);
  }
  return client_socket_fd;
}

void WEBPP::Server::handle_client(int t_client){
  char buffer[1024];
  read(t_client, buffer, sizeof(buffer));
  std::unordered_map<std::string, std::string> parsed_request;
  parsed_request = WEBPP::parse_http_request(buffer);
  std::string route = parsed_request["route"];
  WEBPP::Responder responder(t_client);
  router->handle_request(responder, parsed_request);
}

void WEBPP::Server::sig_term(int signal){
  server_instance->handle_termination_sig(signal);
}

void WEBPP::Server::sig(int signal){
  server_instance->handle_signal(signal);
}

void WEBPP::Server::handle_termination_sig(int signal){
  logger << "server: recieved termination signal...";
  shouldRun = false;
  // Handle clean up...
  server_socket->deactivate();
  delete server_socket;
  logger >> "Server deactive";
  exit(EXIT_SUCCESS);
}

void WEBPP::Server::handle_signal(int signal){
  logger << ("server: recieved signal: " + std::to_string(signal));
}

void WEBPP::Server::accept_connections(std::mutex& mutex){
  int client_socket_fd;
  while(shouldRun){
    if((client_socket_fd = accept_client()) < 0){
      std::unique_lock<std::mutex> lock(mutex);
      logger << "Error accepting client";
      lock.unlock();
    }
    std::thread(&Server::handle_client, this, client_socket_fd).detach();
  }
}

void WEBPP::Server::start(){
  int client_socket_fd, child_pid;
  std::mutex mutex;
  server_socket->activate();

  // Register signals
  signal(SIGTERM, &Server::sig_term);
  signal(SIGINT, &Server::sig_term);

  // Create thread to accept clients
  std::thread accepting_thread(&Server::accept_connections, this, std::ref(mutex));
  accepting_thread.join();
}

void WEBPP::Server::deploy(){
  logger >> "Deploying Server...";
  logger.print(false);
  int daemon_pid, child_pid, client_fd;
  daemon_pid = fork(); // Fork off parent..
  try{
    if(daemon_pid < 0 ){
      throw ForkSystemCallException();
    }
    if(daemon_pid > 0){ // Child process success...
      logger >> ("server pid: " + std::to_string(daemon_pid)).c_str();
      logger.print(false);
      exit(EXIT_SUCCESS); // Termintate parent process...
    }
    if(setsid() < 0){ // Make daemon session leader
      logger << "failed to make daemon session leader";
      exit(EXIT_FAILURE);
    }

    // Start server
    start();
  }
  catch(ForkSystemCallException fsce){
    logger << fsce.what();
    exit(EXIT_FAILURE);
  }
}

void WEBPP::Server::add_route(std::string route, ROUTE_HANDLER *route_handler){
    router->add_route(route, route_handler);
}

WEBPP::BindingSocket *WEBPP::Server::get_socket(){
  return server_socket;
}
