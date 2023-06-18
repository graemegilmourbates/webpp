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

int main(int argc, const char * argv[]) {
    // insert code here...
    WEBPP::Server t(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/",[](int dest_sck, std::unordered_map<std::string, std::string>)->void{
        WEBPP::Responder responder(dest_sck);
        responder.send_html("<html><body><h1>Reached: /</h1></body></html>");
    });
    t.add_route("/Hello",[](int dest_sck, std::unordered_map<std::string, std::string>)->void{
        WEBPP::Responder responder(dest_sck);
        responder.send_html("<html><body><h1>Reached: /Hello</h1></body></html>");
    });
    t.start();
    return 0;
}
