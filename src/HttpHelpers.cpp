#include "HttpHelpers.hpp"

/* HTTP Requst format
A Request-line
Request-Line = Method SP Request-URI SP HTTP-Version CRLF

Zero or more header (General|Request|Entity) fields followed by CRLF

An empty line (i.e., a line with nothing preceding the CRLF)
indicating the end of the header fields

Optionally a message-body
*/

std::unordered_map<std::string, std::string> WEBPP::parse_http_request(
  char *http_request
){
    std::string line, request_method, uri, http_version, tmp;
    std::istringstream request(http_request);
    //Our map
    std::unordered_map<std::string, std::string> parsed_request;
    // Get first line (aka request type)
    std::getline(request, line);
    request_method = line.substr(0, line.find(" "));
    tmp = line.substr(line.find(" ")+1, line.length()-1);
    uri = tmp.substr(0, tmp.find(" "));
    http_version = tmp.substr(tmp.find(" ")+1, tmp.length()-1);
    parsed_request.insert({"Method", request_method});
    parsed_request.insert({"URI", uri});
    parsed_request.insert({"Version", http_version});
    while(std::getline(request, line)){
        if(line.length() > 1 && line != "\n"){
            std::string first = line.substr(0, line.find(" "));
            std::string second = line.substr(line.find(" ")+1, line.length()-1);
            parsed_request.insert({{first, second}});
        }
    }
    return parsed_request;
}
