#ifndef HTTP_HELPERS_HPP
#define HTTP_HELPERS_HPP

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <iostream>

namespace WEBPP{
  std::unordered_map<std::string, std::string> parse_http_request(
    char *http_request
  );
  std::unordered_map<std::string, std::string> get_form_data(
    std::string &body
  );
}

#endif // HTTP HELPERS
