//
//  main.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "webpp.hpp"

using REQUEST = std::unordered_map<std::string, std::string>;

int main(int argc, const char * argv[]) {
    
    WEBPP::Server t(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/",[](WEBPP::Responder responder, REQUEST req)->void{
        responder.send_html("<html><body><h1>Welcome to WEBPP</h1><p>This is a c++ backend framework</p></body></html>");
    });
    t.add_route("/Hello",[](WEBPP::Responder responder, REQUEST req)->void{
        responder.send_html("<html><body><h1>Hello World</h1></body></html>");
    });
    t.add_route("/favicon.ico",[](WEBPP::Responder responder, REQUEST req)->void{
        responder.send_image("/Users/gb/static/favicon.ico");
    });
    t.start();
    return 0;
}
