//
//  Responder.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/18/23.
//
//  This is specifically an http responder... assume all reponses are for http clients.
//

#include "Responder.hpp"

WEBPP::Responder::Responder(int dst_sck){
    dest_socket = dst_sck;
}

void WEBPP::Responder::set_response_header(char* header){
    response_header = header;
}


void WEBPP::Responder::send_response(char* response){
    //Create new char* that adds response header to the response
    char* outflow{new char[strlen(response_header) + strlen(response) + 2]};
    outflow = strcpy(outflow, response_header);
    outflow = strcat(outflow, "\n");
    outflow = strcat(outflow, response);
    send(dest_socket, outflow, strlen(outflow), 0);
    close(dest_socket);
}

void WEBPP::Responder::send_file(std::string file_path, std::string content_type){
    // Load in file
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    // Check that file was obtained
    if(!file){
        perror("FILE DNE:");
        exit(EXIT_FAILURE);
    }
    // Move to end of file to get total size
    file.seekg (0, file.end);
    std::streamsize file_size = file.tellg();
    // Create reponse header
    std::stringstream responseStream;
    responseStream << "HTTP/1.1 200 OK\r\n";
    responseStream << "Content-Type: " << content_type << "\r\n";
    responseStream << "Content-Length: " << file_size << "\r\n\r\n";
    
    std::string response = responseStream.str();
    // Send response Header
    if (send(dest_socket, response.c_str(), response.length(), 0) == -1) {
        std::cout << "Failed to send HTTP response" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Return to beginning of the file
    // Initialize chunks of 1024 bytes to send
    file.seekg (0, file.beg);
    char buffer[1024];
    std::streamsize bytes_read;
    while(file_size > 0){
        // read in a chunk
        bytes_read = file.read(buffer, sizeof(buffer)).gcount();
        if(bytes_read <= 0){
            std::cout << "Problem with file read" << std::endl;
            break;
        }
        if(send(dest_socket, buffer, bytes_read, 0) == -1){
            std::cout << "Failed to send image data" << std::endl;
            exit(EXIT_FAILURE);
        }
        file_size -= bytes_read;
    }
    file.close();
    close(dest_socket);
}

void WEBPP::Responder::send_html(char* html){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
    send_response(html);
}

void WEBPP::Responder::send_json(char* json){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n");
    send_response(json);
}

void WEBPP::Responder::send_image(std::string file_path){
    // Get image type:
    int index;
    std::string file_p, file_type, content_type;
    file_p = file_path;
    index = file_p.find_last_of(".");
    file_type = file_p.substr(index+1);
    if(file_type == "ico") content_type = "image/x-icon";
    else if (file_type == "jpeg" || file_type == "jpg") content_type = "image/jpeg";
    send_file(file_path, content_type);
}
