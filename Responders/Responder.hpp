//
//  Responder.hpp
//  WEBPP
//
//  Created by Graeme Bates on 6/18/23.
//
//  This is specifically an http responder... assume all reponses are for http clients.
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
#include <sstream>
#include <filesystem>

namespace WEBPP{

    class Responder{
    private:
        char* response_header;
        // Destination
        int dest_socket;
        void set_response_header(char* header);
        void send_response(char* response);
        void send_file(std::string file_path, std::string file_type);
    public:
        Responder(int dest_socket);
        void send_html(char* html);
        void send_json(char* json);
        /// Grabs file type from path
        void send_image(std::string file_path);
        void send_audio(char* file_path);
        void send_video(char* file_path);
    };
}

#endif /* Responder_hpp */
