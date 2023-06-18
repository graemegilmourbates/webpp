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
        // Destination
        int dest_socket;
        void set_response_header(char* header);
        void send_response(char* response);
    public:
        Responder(int dest_socket);
        void send_html(char* html);
        void send_json(char* json);
    };
}

#endif /* Responder_hpp */
