#include "BindingSocket.hpp"

WEBPP::BindingSocket::BindingSocket(
  int domain, // AF_UNIX for local communication, AF_INET for internet domain
  int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
  int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
  int port, // Desired PORT ex 80
  u_long interface, // Address to bind to.
  int bcklog
) : BaseSocket(domain, type, protocol, port, interface){
  backlog = bcklog;
  int bound = connect_to_network(get_sock(), get_address());
  check_connection(bound);
  start_listening();
  check_connection(get_listener());
}

int WEBPP::BindingSocket::connect_to_network(
  int t_sock,
  struct sockaddr_in6 t_address
) {
  // Cast address
  return bind(t_sock, (struct sockaddr *)&t_address, sizeof(t_address));
}

void WEBPP::BindingSocket::start_listening(){
  listener = listen(get_sock(), backlog);
  struct sockaddr_in6 addy = get_address();
  logger->log("Listening on :" + std::to_string(addy.sin6_port));
}

int WEBPP::BindingSocket::get_back_log(){
  return backlog;
}

int WEBPP::BindingSocket::get_listener(){
  return listener;
}
