#ifndef BASESOCKET_HPP
#define BASESOCKET_HPP

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Logger.hpp"

namespace WEBPP{
  class BaseSocket{
  private:
    struct sockaddr_in6 address;
    int sock;
  public:
    BaseSocket(
      int domain,  // AF_UNIX for local, AF_INET for internet domain
      int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET
      int protocol, // Standard is 0
      int port, // Desired PORT ex 80
      u_long interface // ??
    );
    // Virutal function will need to be fufilled by child class
    // Connect to network will differ depending on the socket
    virtual int connect_to_network(int t_sck, struct sockaddr_in6 t_addr) = 0;
    // Check socket connection
    void check_connection(int t_connection_sock);
    // Access functions: get private values without direct access
    struct sockaddr_in6 get_address();
    int get_sock();
  };
} // END NAMESPACE WEBPP

#endif // BASESOCKET_HPP
