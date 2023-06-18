//
//  MasterSocket.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include "MasterSocket.hpp"

/// Constructor
/// - Parameters:
///   - domain: Communication domain for socket
///   - type: Specifies the type of socket to be created
///   - protocol: specifying a protocol of 0 causes socket() to use an unspecified default protocol appropriate for the requested socket type.
///   - port: Port number to bind
///   - interface: Address to bind to
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

/// A quick error checker for sockets
/// - Parameter sck: socket to check
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
