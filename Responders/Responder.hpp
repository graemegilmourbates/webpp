//
//  Responder.hpp
//  WEBPP
//
//  Created by Graeme Bates on 6/18/23.
//

#ifndef Responder_hpp
#define Responder_hpp

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <unordered_map>
#include <sys/time.h>

namespace WEBPP{

    class Responder{
    private:
        char* response_header;
    public:
        Responder();
        void set_response_header(char* header);
        std::string get_response_header();
        void send_response(int dest_socket, char* response);
    };
}

#endif /* Responder_hpp */
