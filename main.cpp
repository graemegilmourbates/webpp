//
//  main.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include <iostream>
#include <string>
#include <iostream>
#include <unordered_map>
#include "webpp.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    WEBPP::Server t(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    t.add_route("/",[](int dest_sck, std::unordered_map<std::string, std::string>)->std::string{
        WEBPP::HTMLResponder responder;
        responder.send_response(dest_sck, "<html><body><h1>Reached: /</h1></body></html>");
        return "/";
    });
    t.add_route("/Hello",[](int dest_sck, std::unordered_map<std::string, std::string>)->std::string{
        WEBPP::HTMLResponder responder;
        responder.send_response(dest_sck, "<html><body><h1>Reached: /Hello</h1></body></html>");
        return "/Hello";
    });
    t.start();
    return 0;
}
