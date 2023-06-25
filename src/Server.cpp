#include "Server.hpp"

WEBPP::Server::Server(
  int domain, // AF_UNIX for local communication, AF_INET for internet domain
  int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
  int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
  int port, // Desired PORT ex 80
  u_long interface, // Address to bind to.
  int backlog
){
  server_socket = new BindingSocket(
    domain, type, protocol, port, interface, backlog
  );
}

WEBPP::BindingSocket *WEBPP::Server::get_socket(){
  return server_socket;
}

int WEBPP::Server::accept_client(){
  struct sockaddr_in6 client_address;
  socklen_t client_address_length;
  int client_socket = accept(
    get_socket()->get_sock(),
    (struct sockaddr *)&client_address,
    &client_address_length
  );
  return client_socket;
}

void WEBPP::Server::handle_client(int t_client){
  char buffer[1024];
  read(t_client, buffer, sizeof(buffer));
  std::unordered_map<std::string, std::string> parsed_request;
  parsed_request = WEBPP::parse_http_request(buffer);
  std::string route = parsed_request["route"];
  // router->handle_request(t_client, parsed_request);
  WEBPP::Responder responder(t_client);
  //run route handler
  if(routes.find(route) == routes.end()){
    //handle route does not exist
    std::cout << "Route: " << route << " does not exist" << std::endl;
    responder.send_html("<html><body><h1>404 NOT FOUND</h1></body></html>");
  }
  else {
    const ROUTE_HANDLER& route_handler = routes.at(route);
    route_handler(responder, parsed_request);
  }
}

void WEBPP::Server::start(){
  std::vector<std::thread> client_threads;
  while(true){
    int client_socket = accept_client();
    client_threads.push_back(std::thread(
      &Server::handle_client, this, client_socket
    ));
  }
}

void WEBPP::Server::add_route(std::string route, ROUTE_HANDLER route_handler){
    routes.insert({route, route_handler});
}