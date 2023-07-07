#include "BaseSocket.hpp"

WEBPP::BaseSocket::BaseSocket(
  int domain,  // AF_UNIX for local, AF_INET for internet domain
  int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET
  int protocol, // Standard is 0
  int port, // Desired PORT ex 80
  u_long interface // ??
){
  // Define the address
  address.sin6_family = domain;
  address.sin6_addr = in6addr_any;
  address.sin6_port = htons(port);
  // Create socket
  sock=socket(domain, type, protocol);
  check_connection(sock);
}

void WEBPP::BaseSocket::check_connection(int t_connection_sock){
  if(t_connection_sock < 0){
    logger->error("Socket Failed to Connect");
    exit(EXIT_FAILURE);
  }
}

struct sockaddr_in6 WEBPP::BaseSocket::get_address(){
  return address;
}

int WEBPP::BaseSocket::get_sock(){
  return sock;
}
