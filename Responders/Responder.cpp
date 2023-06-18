//
//  Responder.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/18/23.
//

#include "Responder.hpp"

WEBPP::Responder::Responder(){}

void WEBPP::Responder::set_response_header(char* header){
    response_header = header;
}

std::string WEBPP::Responder::get_response_header(){
    return response_header;
}

void WEBPP::Responder::send_response(int dest_socket, char* response){
    //Create new char* that adds response header to the response
    char* outflow{new char[strlen(response_header) + strlen(response) + 2]};
    outflow = strcpy(outflow, response_header);
    outflow = strcat(outflow, "\n");
    outflow = strcat(outflow, response);
    send(dest_socket, outflow, strlen(outflow), 0);
    close(dest_socket);
}
