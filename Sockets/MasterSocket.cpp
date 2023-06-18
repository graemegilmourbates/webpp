//
//  MasterSocket.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include "MasterSocket.hpp"

WEBPP::MasterSocket::MasterSocket(
    int domain, int type, int protocol,
    int port, u_long interface
  ){
    // Define the address
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    // Create socket
    sock=socket(domain, type, protocol);
    check_connection(sock);
}

void WEBPP::MasterSocket::check_connection(int sck){
    if(sck < 0){
        perror("FAILED TO CONNECT");
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in WEBPP::MasterSocket::get_address(){
    return address;
}

int WEBPP::MasterSocket::get_sock(){
    return sock;
}
