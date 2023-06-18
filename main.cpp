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
    t.add_route("/",[](std::unordered_map<std::string, std::string>)->std::string{
        std::cout << "I am at the route" << std::endl;
        return "/";
    });
    t.start();
    return 0;
}
