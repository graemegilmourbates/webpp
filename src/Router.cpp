#include "Router.hpp"

std::vector<std::string> WEBPP::Route::split_route(std::string &t_route){
  std::vector<std::string> s_route;
  std::stringstream buf;
  std::string seg;
  buf << t_route;
  while(std::getline(buf, seg, '/')){
    s_route.push_back(seg);
  }
  return s_route;
}
// Constructor for route
// Has to split by '/'
// par: parameter, pos: position
WEBPP::Route::Route(std::string t_route){
  int i=0;
  route = split_route(t_route);
  raw_route = t_route;
  while(i < route.size()){
    if(route[i][0] == ':'){
      url_parameters.push_back(std::make_pair(i, route[i].substr(1)));
    }
    i++;
  }
}

// Compare a route with route template.
bool WEBPP::Route::compare(std::string &t_route){
  int i=0;
  std::vector<std::string> comp_route = split_route(t_route);
  if(route.size() != comp_route.size()) return false;
  // Handle case where the route has no parameters
  if(t_route == raw_route){
    return true;
  } else {
  // Iterate over route templates
    for(std::string &element : route){
      // Check if given route matches template
      if(element != comp_route[i]){
        // Ceck if template element is a parameter.
        if(element[0] != ':'){
          return false;
        }
      }
      i++;
    }
  }
  std::cout << "Found route match :" << t_route << raw_route << std::endl;
  return true;
}
// Get url parameters from a url string.
URL_PARAMETERS WEBPP::Route::get_parameters(std::string &t_route){
  URL_PARAMETERS parameters;
  std::vector<std::string> req_url = split_route(t_route);
  for(URL_PARAMETER &par : url_parameters){
    parameters.insert({par.second, req_url[par.first]});
  }
  return parameters;
}

void WEBPP::Router::add_route(std::string t_route, ROUTE_HANDLER &t_handler){
  std::pair<Route, ROUTE_HANDLER&> route(Route(t_route), t_handler);
  routes.push_back(route);
}

void WEBPP::Router::handle_request(WEBPP::Responder t_responder, REQUEST &t_request){
  std::cout << "REQUEST URI: " << t_request["URI"] << std::endl;
  for(std::pair<WEBPP::Route, ROUTE_HANDLER&> route: routes){
    if(route.first.compare(t_request["URI"])){
      URL_PARAMETERS params = route.first.get_parameters(t_request["URI"]);
      return route.second(t_responder, t_request, params);
    }
  }
  t_responder.send_html("<html><body><h1>404 NOT FOUND</h1></body></html>");
}
