#include <iostream>
#include <unordered_map>
#include <WEBPP/webpp.hpp>
#include <WEBPP/Responder.hpp>

using REQUEST = std::unordered_map<std::string, std::string>;
using RESPONDER = WEBPP::Responder;

void home_page(RESPONDER res, REQUEST req){
  res.send_file("index.html", "html");
}

int main(int argc, const char * argv[]) {
    WEBPP::Server t(AF_INET6, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/", home_page);
    t.add_route("/Hello",[](WEBPP::Responder responder, REQUEST req)->void{
        responder.send_html("<html><body><h1>Hello World</h1></body></html>");
    });
    t.add_route("/favicon.ico",[](WEBPP::Responder responder, REQUEST req)->void{
        responder.send_image("/Users/gb/static/favicon.ico");
    });
    t.add_route("/json", [](WEBPP::Responder responder, REQUEST req)->void{
        responder.send_json("{'array':[1,2,3], 'key':'value'}");
    });
    t.start();
    return 0;
}
