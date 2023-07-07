#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <functional>

#include "Responder.hpp"
#include "Logger.hpp"

using REQUEST = std::unordered_map<std::string, std::string>;
using URL_PARAMETERS = std::unordered_map<std::string, std::string>;
using URL_PARAMETER = std::pair<int, std::string>;
using ROUTE_HANDLER = std::function<void(
  WEBPP::Responder& responder,
  REQUEST& request,
  URL_PARAMETERS params
)>;

namespace WEBPP{
  class Route{
  private:
    // Hold copy of the raw route template
    std::vector<std::string> route;
    // Store parameters and their location
    // URL location 0/1/2/3/4/5 (location seperated by '/')
    std::vector<std::pair<int, std::string>> url_parameters;
    std::vector<std::string> split_route(std::string &a_route);
  public:
    std::string raw_route;
    // The constructor takes in a route template
    // ex. this/route/has/:id
    // actual request: this/route/has/3
    Route(std::string t_route);
    // Compares a real route vs the route template
    bool compare(std::string &t_route);
    // Returns url parameters
    URL_PARAMETERS get_parameters(std::string &t_route);
  };

  class Router{
  private:
    std::vector<std::pair<Route, ROUTE_HANDLER&>> routes;
  public:
    void add_route(std::string t_route, ROUTE_HANDLER *t_handler);
    // void add_route(std::string t_route, std::string t_method, ROUTE_HANDLER &t_handler);
    void handle_request(WEBPP::Responder t_responder, REQUEST &t_request);
  };
}

#endif
