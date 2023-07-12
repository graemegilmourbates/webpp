#include "BaseSocket.hpp"

WEBPP::BaseSocket::BaseSocket(
  int domain,  // AF_UNIX for local, AF_INET for internet domain
  int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET
  int protocol, // Standard is 0
  int port // Desired PORT ex 80
  // u_long interface // ??
){
  // Define the address
  address.sin6_family = domain;
  address.sin6_addr = in6addr_any;
  address.sin6_port = htons(port);
  // Create socket and store the file descriptor...
  socket_fd = socket(domain, type, protocol);
  check_connection(socket_fd, strdup("socket error"));
}

void WEBPP::BaseSocket::check_connection(int t_socket_fd, char* err_msg){
  try{
    if(t_socket_fd < 0){
      throw SocketSystemCallException(err_msg);
    }
  }
  catch(SocketSystemCallException ssce){
    logger << ssce.what();
    exit(EXIT_FAILURE);
  }
}
// Access Functions... Constant referernces...
const struct sockaddr_in6& WEBPP::BaseSocket::get_address(){
  return address;
}

const int &WEBPP::BaseSocket::get_sock(){
  return socket_fd;
}
