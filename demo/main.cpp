#include <iostream>
#include <unordered_map>
#include <WEBPP/webpp.hpp>
#include <WEBPP/Responder.hpp>
#include <stdlib.h>

using REQUEST = std::unordered_map<std::string, std::string>;
using RESPONDER = WEBPP::Responder;

void home_page(RESPONDER res, REQUEST req){
  std::cout << "Sending INDEX PAGE" << std::endl;
  res.send_file("index.html", "html");
}

void favicon(RESPONDER res, REQUEST req){
  std::cout << "Sending FAV" << std::endl;
  res.send_image("public/images/favicon.ico");
}

int main(int argc, const char * argv[]) {
    WEBPP::Server t(AF_INET6, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/", home_page);
    t.add_route("/favicon.ico", favicon);
    t.add_route("/json", [](WEBPP::Responder responder, REQUEST req)->void{
      std::cout << "Sending JSON" << std::endl;
      responder.send_json(
        "{\n\"JSON\":\"data\",\n\"array\":[1,2,3],\n\"key\":\"value\"\n}"
      );
    });
    t.start();
    return 0;
}
