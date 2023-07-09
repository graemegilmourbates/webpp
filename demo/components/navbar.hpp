#include <WEBPP/Templater.hpp>
#include <string>
#include <vector>

using namespace HTML;

Node generate_nav_brand(std::string t_brand){
  return tag(
    "a", {attr("class", {"navbar-brand"}), attr("href", {"#"})}, "Web ++"
  );
}

Node generate_nav_button(){
  return tag("button", {
    attr("class", {"navbar-toggler", "collapsed"}),
    attr("type", {"button"}),
    attr("data-bs-toggle", {"collapse"}),
    attr("data-bs-target", {"#navbarNav"}),
    attr("aria-controls", {"navbarNav"}),
    attr("aria-expanded", {"false"}),
    attr("aria-label", {"Toggle navigation"})
  })(
    tag("span", {attr("class", {"navbar-toggler-icon"})})
  );
}

Node generate_nav_li(std::string t_name, std::string t_target){
  Node t_li = tag("li", {attr("class", {"nav-item"})})(
    tag("a", {
      attr("class", {"nav-link"}),
      attr("aria-current", {"page"}),
      attr("href", {t_target})
    })(t_name)
  );
  return t_li;
}

Node generate_nav_ul(const std::map<std::string, std::string>& links){
  Node t_ul = tag(
    "ul", {attr("class", {"navbar-nav", "mr-auto"})}
  );
  for(const auto& link : links){
    std::string l_name = link.first;
    std::string l_target = link.second;
    t_ul(generate_nav_li(l_name, l_target));
  }
  return t_ul;
}

Node generate_nav_content(const std::map<std::string, std::string>& links){
  return tag("div", {
    attr("class", {"collapse", "navbar-collapse"}), attr("id", {"navbarNav"})
  })( generate_nav_ul(links) );
}

Node navbar(const std::map<std::string, std::string>& links){
  Node nav = tag("nav", {
    attr("class", {"navbar", "navbar-expand-lg", "navbar-light", "bg-light"})
  });
  nav(
    tag("div", {
      attr("class", {"container-fluid"})
    })[{
      generate_nav_brand("WEBPP"),
      generate_nav_button(),
      generate_nav_content(links)
    }]
  );
  return nav;
}
