//
//  Server.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include "Server.hpp"

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

void WEBPP::Server::init_ssl(){
    std::cout << "Initializing SSL..." << std::endl;
}

int WEBPP::Server::accept_client(){
    sockaddr_in6 client_addr;
    socklen_t client_addr_length;
    int client_socket = accept(
        get_socket()->get_sock(), (struct sockaddr *)&client_addr,
        &client_addr_length
    );
    if(client_socket < 0){
        std::cout << "Failed to accept client connection" << std::endl;
    }
    return client_socket;
}

void WEBPP::Server::handler(int client_sock){
    char buffer[1024];
    read(client_sock, buffer, sizeof(buffer));
    std::unordered_map<std::string, std::string> parsed_request = WEBPP::parse_http_request(buffer);
    //Split GET to recieve route
    std::string route = parsed_request["GET"].substr(0, parsed_request["GET"].find(" "));
    WEBPP::Responder responder(client_sock);
    //run route handler
    if(routes.find(route) == routes.end()){
        //handle route does not exist
        std::cout << "Route: " << route << " does not exist" << std::endl;
        responder.send_html("<html><body><h1>404 NOT FOUND</h1></body></html>");
    }
    else {
        const ROUTE_HANDLER& route_handler = routes.at(route);
        route_handler(responder, parsed_request);
    }
}

void WEBPP::Server::attach_ssl_to_client_sock(){
    std::cout << "Attaching SSL to client sock" << std::endl;
}


void WEBPP::Server::start(){
    std::cout << "Starting Server..." << std::endl;
    init_ssl();
    std::vector<std::thread> client_threads;
    while(true){
        int client_sock = accept_client();
        client_threads.push_back(std::thread(&Server::handler, this, client_sock));
    }
}

WEBPP::BindingSocket * WEBPP::Server::get_socket(){
    return socket;
}


void WEBPP::Server::add_route(std::string route, ROUTE_HANDLER route_handler){
    std::cout << "Adding route: " << route << std::endl;
    routes.insert({route, route_handler});
}


