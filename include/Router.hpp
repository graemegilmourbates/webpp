#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <iostream>
#include <unordered_map>

#include "Responder.hpp"

using ROUTE_HANDLER = std::function<void(
  WEBPP::Responder& responder,
  std::unordered_map<std::string, std::string>& request
)>;

using REQUEST = std::unordered_map<std::string, std::string>;

namespace WEBPP{
  class Router{
  private:
    std::unordered_map<std::string, const ROUTE_HANDLER&> routes;
  public:
    Router();
    void add(std::string t_route, const ROUTE_HANDLER &t_handler);
    void handle_request(int t_client, REQUEST &parsed_request);
  };
}

#endif // ROUTER_HPP
