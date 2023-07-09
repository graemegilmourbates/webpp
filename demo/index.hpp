#include <WEBPP/Templater.hpp>
#include <map>
#include "./components/navbar.hpp"
#include "./components/headTags.hpp"
#include "./pages/home.hpp"

using namespace HTML;
std::string index(){
  std::map<std::string, std::string> nav_links{
    {"Sockets", "#"},
    {"Server", "#"},
    {"Router", "#"},
    {"Responder", "#"}
  };
  Doc doc;
  // Set meta
  for(const auto& tg : head_tags()){
    doc[tg];
  }
  doc(
    tag("title", "Web PlusPlus")
  );
  doc(navbar(nav_links));
  doc[{
    home_page()
  }];
  // Add bootstrap js
  doc[{
    tag("script", {
      attr("src", {"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"}),
      attr("integrity", {"sha384-geWF76RCwLtnZ8qwWowPQNguL3RmwHVBC9FhGdlKrxdiJJigb/j/68SIy3Te4Bkz"}),
      attr("crossorigin", {"anonymous"})
    })
  }];

  return doc.render();
}
