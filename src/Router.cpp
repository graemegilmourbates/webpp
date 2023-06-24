#include "Router.hpp"

WEBPP::Router::Router(){}

void WEBPP::Router::add(std::string t_route, ROUTE_HANDLER &t_handler){
  std::cout << "Adding route: " << t_route << std::endl;
  routes.insert({t_route, t_handler});
}

void WEBPP::Router::handle_request(int t_client, REQUEST &parsed_request){
  std::string requested = parsed_request["GET"];
  std::string route_path = requested.substr(0, requested.find(" "));
  WEBPP::Responder client_responder(t_client);
  if(routes.find(route_path) == routes.end()){
    std::cout << "Route: " << route_path << " DNE" << std::endl;
    client_responder.send_html("<html><body><h1>404 NOT FOUND</h1></body></html>");
  } else {
    const ROUTE_HANDLER &route_handler = routes.at(route_path);
    route_handler(client_responder, parsed_request);
  }
}
