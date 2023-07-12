#include "BindingSocket.hpp"

// The Constructor will call BaseSockets constructor...
WEBPP::BindingSocket::BindingSocket(
  int domain, // AF_UNIX for local communication, AF_INET for internet domain
  int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
  int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
  int port, // Desired PORT ex 80
  // u_long interface, // Address to bind to.
  int bcklog
) : BaseSocket(domain, type, protocol, port /* interface */){
  backlog = bcklog;
  int bound = connect_to_network(get_sock(), get_address());
  check_connection(bound, strdup("bind error..."));
  start_listening();
  check_connection(get_listener(), strdup("listen error"));
}

// Binding call...
int WEBPP::BindingSocket::connect_to_network(
  int t_socket_fd,
  struct sockaddr_in6 t_address
) {
  // Bind system call, cast to generic sockaddr from sockaddr_in6
  return bind(t_socket_fd, (struct sockaddr *)&t_address, sizeof(t_address));
}

// Listen system call... Careful with backlog 5 is traditional
void WEBPP::BindingSocket::start_listening(){
  listener = listen(get_sock(), backlog);
  struct sockaddr_in6 addy = get_address();
  logger("Listening on :" + std::to_string(addy.sin6_port));
}

const int& WEBPP::BindingSocket::get_back_log(){
  return backlog;
}

const int& WEBPP::BindingSocket::get_listener(){
  return listener;
}
