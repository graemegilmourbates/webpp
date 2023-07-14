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
}

int WEBPP::Server::accept_client(){
  struct sockaddr_in6 client_address;
  socklen_t client_address_length;
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

void WEBPP::Server::start(){
  int client_socket_fd, child_pid;
  server_socket->activate();
  while(true){
    client_socket_fd = accept_client();
    try{
      if((child_pid = fork()) < 0 ){
        logger << "server: fork error.";
        throw ForkSystemCallException();
      }
      else if(child_pid == 0){ // Child process
        close(server_socket->get_sock()); // Close the original socket
        handle_client(client_socket_fd); // Handle the request
        exit(0);
      }
      close(client_socket_fd); // Parent;
    }
    catch(ForkSystemCallException fsce){
      logger << fsce.what();
      exit(EXIT_FAILURE);
    }
  }
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
    // TODO: SIGNAL HANDLING...
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
