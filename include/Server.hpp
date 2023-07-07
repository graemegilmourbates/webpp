#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
// #include <libexplain/accept.h>

#include "Responder.hpp"
#include "BindingSocket.hpp"
#include "HttpHelpers.hpp"
#include "Router.hpp"
#include "Logger.hpp"

using URL_PARAMETERS = std::unordered_map<std::string, std::string>;
using ROUTE_HANDLER = std::function<void(
  WEBPP::Responder& responder,
  std::unordered_map<std::string, std::string>& request,
  URL_PARAMETERS params
)>;

using REQUEST = std::unordered_map<std::string, std::string>;

namespace WEBPP{
  class Server{
  private:
    BindingSocket *server_socket;
    int accept_client();
    void handle_client(int t_client);
    std::unordered_map<std::string, ROUTE_HANDLER&> routes;
    Router *router;
  public:
    Server(
      int domain, // AF_UNIX for local communication, AF_INET for internet domain
      int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
      int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
      int port, // Desired PORT ex 80
      u_long interface, // Address to bind to.
      int backlog
    );
    void start();
    void add_route(std::string route, ROUTE_HANDLER);
    // ACCESS FUNCTIONS
    BindingSocket *get_socket();
  };
}

#endif // SERVER_HPP
