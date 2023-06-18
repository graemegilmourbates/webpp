//
//  HtmlResponder.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/18/23.
//

#include "HtmlResponder.hpp"

WEBPP::HTMLResponder::HTMLResponder(){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
}
