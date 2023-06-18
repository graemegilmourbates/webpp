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
#include <fstream>

namespace WEBPP{

    class Responder{
    private:
        char* response_header;
        // Destination
        int dest_socket;
        void set_response_header(char* header);
        void send_response(char* response);
        void send_file(char* file_path);
    public:
        Responder(int dest_socket);
        void send_html(char* html);
        void send_json(char* json);
        /// Grabs file type from path
        void send_image(char* file_path);
        void send_audio(char* file_path);
        void send_video(char* file_path);
    };
}

#endif /* Responder_hpp */
