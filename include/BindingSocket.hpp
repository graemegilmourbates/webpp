#ifndef BINDINGSOCKET_HPP
#define BINDINGSOCKET_HPP

#include <iostream>
#include <sys/types.h>
#include "Logger.hpp"
#include "BaseSocket.hpp"


namespace WEBPP{
  class BindingSocket : public BaseSocket{
  private:
    int backlog;
    int listener;
  public:
    BindingSocket(
      int domain, // AF_UNIX for local communication, AF_INET for internet domain
      int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
      int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
      int port, // Desired PORT ex 80
      // u_long interface, // Address to bind to.
      int bcklog
    );
    int connect_to_network(int t_socket_fd, struct sockaddr_in6 t_address);
    void start_listening();
    // Access functions: get private member values without direct Access
    const int& get_back_log();
    const int& get_listener();
  };
}// END NAMESPACE WEBPP

#endif // BINDINGSOCKET_H
