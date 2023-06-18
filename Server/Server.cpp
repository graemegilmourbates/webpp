//
//  Server.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//
#define MAX_CONNECTIONS 30;
#include "Server.hpp"
#include <unordered_map>

WEBPP::Server::Server(
    int domain, int type, int protocol,
    int port, u_long interface, int bcklg
){
    socket = new BindingSocket(
        domain, type, protocol, port, interface, bcklg
    );
    max_clients = MAX_CONNECTIONS;
    for(int i=0; i<max_clients; i++){
        client_sockets[i];
    }
}

WEBPP::Server::~Server(){
    close(get_socket()->get_sock());
}

int WEBPP::Server::accepter(){
    sockaddr_in client_addr;
    socklen_t client_addr_length;
    int client_socket = accept(
        get_socket()->get_sock(), (struct sockaddr *)&client_addr,
        &client_addr_length
    );
    if(client_socket < 0){
        std::cout << "Failed to accept client connection" << std::endl;
    }
    read(client_socket, buffer, 30000);
    return client_socket;
}

void WEBPP::Server::handler(int d_sck){
    std::unordered_map<std::string, std::string> parsed_request = WEBPP::parse_http_request(buffer);
    //Split GET to recieve route
    std::string route = parsed_request["GET"].substr(0, parsed_request["GET"].find(" "));
    //run route handler
    if(routes.find(route) == routes.end()){
        //handle route does not exist
        std::cout << "Route: " << route << " does not exist" << std::endl;
        WEBPP::Responder responder(d_sck);
        responder.send_html("<html><body><h1>404 NOT FOUND</h1></body></html>");
    }
    else {
        const std::function<void(int, std::unordered_map<std::string, std::string>&)>& route_handler = routes.at(route);
        route_handler(d_sck, parsed_request);
    }
}


void WEBPP::Server::start(){
    while(true){
        int d_sck = accepter();
        handler(d_sck);
    }
}

WEBPP::BindingSocket * WEBPP::Server::get_socket(){
    return socket;
}


void WEBPP::Server::add_route(std::string route, std::function<void(int dest_sck, std::unordered_map<std::string, std::string>&)> route_handler){
    routes.insert({route, route_handler});
}


