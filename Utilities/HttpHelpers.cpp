//
//  httpHelpers.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/13/23.
//

#include "HttpHelpers.hpp"

std::unordered_map<std::string, std::string> WEBPP::parse_http_request(char http_request[30000]){
    std::string line;
    std::istringstream request(http_request);
    //Our map
    std::unordered_map<std::string, std::string> parsed_request;
    while(std::getline(request, line)){
        if(line.length() > 1){
            std::string first = line.substr(0, line.find(" "));
            std::string second = line.substr(line.find(" ")+1, line.length()-1);
            parsed_request.insert({{first, second}});
        }
    }
    return parsed_request;
}

