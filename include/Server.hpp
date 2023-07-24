#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <thread>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <signal.h>
#include "webpp.hpp"

const int MAX_THREADS = 5; // Max number of threads to handle clients

using URL_PARAMETERS = std::unordered_map<std::string, std::string>;
using ROUTE_HANDLER = void(
  WEBPP::Responder& responder,
  std::unordered_map<std::string, std::string>& request,
  URL_PARAMETERS params
);

using REQUEST = std::unordered_map<std::string, std::string>;

namespace WEBPP{
  class Server{
  private:
    BindingSocket *server_socket;
    int accept_client();
    void handle_client(int t_client);
    static Server* server_instance;
    static void sig_term(int signal);
    static void sig(int signal);
    void handle_termination_sig(int signal);
    void handle_signal(int signal);
    void accept_connections(std::mutex& mutex);
    std::unordered_map<std::string, ROUTE_HANDLER*> routes;
    Router *router;
    bool shouldRun;
  public:
    Server(
      int domain, // AF_UNIX for local communication, AF_INET for internet domain
      int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
      int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
      int port, // Desired PORT ex 80
      // u_long interface, // Address to bind to.
      int backlog
    );
    Server():
      Server(AF_INET6, SOCK_STREAM, 0, 80, 5){};
    void start();
    void deploy();
    void add_route(std::string route, ROUTE_HANDLER*);
    // ACCESS FUNCTIONS
    BindingSocket *get_socket();
  };
  Server* Server::server_instance = nullptr;
}
#endif // SERVER_HPP
