#include <iostream>
#include <unordered_map>
#include <WEBPP/webpp.hpp>
#include <stdlib.h>
#include <string>
#include <WEBPP/Templater.hpp>

void home_page(RESPONDER &res, REQUEST &req, URL_PARAMETERS params){
  res.send_file("pages/app.html", "html");
}

int main(int argc, const char * argv[]) {
  WEBPP::Server t;
  t.add_route("/", home_page);
  if(argc == 1){
    logger >> "No extra commands passed... Sever not deployed...";
    t.start();
  } else {
    std::string arg = argv[1];
    if(arg=="deploy"){
      t.deploy();
    } else {
      t.start();
    }
  }
  return 0;
}
