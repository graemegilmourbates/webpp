//
//  Responder.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/18/23.
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

void WEBPP::Responder::send_html(char* html){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n");
    send_response(html);
}

void WEBPP::Responder::send_json(char* json){
    set_response_header("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n");
    send_response(json);
}
