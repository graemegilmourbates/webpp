//
//  Server.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include "Server.hpp"
#include <unordered_map>

/// Constructor
/// - Parameters:
///   - domain: Communication domain for socket
///   - type: Specifies the type of socket to be created
///   - protocol: specifying a protocol of 0 causes socket() to use an unspecified default protocol appropriate for the requested socket type.
///   - port: Port number to bind
///   - interface: Address to bind to
///   - bcklg: Maximum rate new tcp connections can be accepted
WEBPP::Server::Server(
    int domain, int type, int protocol,
    int port, u_long interface, int bcklg
){
    /* Constructor, generates binding socket */
    socket = new BindingSocket(
        domain, type, protocol, port, interface, bcklg
    );
}

WEBPP::Server::~Server(){
    // Not certain this is essential
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
        const ROUTE_HANDLER& route_handler = routes.at(route);
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


void WEBPP::Server::add_route(std::string route, ROUTE_HANDLER route_handler){
    routes.insert({route, route_handler});
}


