//
//  httpHelpers.hpp
//  WEBPP
//
//  Created by Graeme Bates on 6/13/23.
//

#ifndef HttpHelpers_hpp
#define HttpHelpers_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>

namespace WEBPP{
std::unordered_map<std::string, std::string> parse_http_request(
                                                                    char http_request[30000]
                                                                    );
}

#endif /* httpHelpers_hpp */
