//
//  BindingSocket.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include "BindingSocket.hpp"

WEBPP::BindingSocket::BindingSocket(
    int domain, int type, int protocol,
    int port, u_long interface, int bcklg
) : MasterSocket(domain, type, protocol, port, interface){
    backlog = bcklg;
    int bound = connect_to_network(get_sock(), get_address());
    check_connection(bound);
    start_listening();
    check_connection(get_listener());
}

int WEBPP::BindingSocket::connect_to_network(int sck, sockaddr_in addr){
    // cast address
    return bind(sck, (struct sockaddr *)&addr, sizeof(addr));
}

void WEBPP::BindingSocket::start_listening(){
    listener = listen(get_sock(), backlog);
}

int WEBPP::BindingSocket::get_back_log(){
    return backlog;
}

int WEBPP::BindingSocket::get_listener(){
    return listener;
}
