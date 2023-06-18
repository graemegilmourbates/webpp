//
//  Server.cpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#include "Server.hpp"
#include <unordered_map>

WEBPP::Server::Server(
    int domain, int type, int protocol,
    int port, u_long interface, int bcklg
){
    socket = new BindingSocket(
        domain, type, protocol, port, interface, bcklg
    );
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

void WEBPP::Server::handler(){
    std::unordered_map<std::string, std::string> parsed_request = WEBPP::parse_http_request(buffer);
    //Split GET to recieve route
    std::string route = parsed_request["GET"].substr(0, parsed_request["GET"].find(" "));
    //run route handler
    if(routes.find(route) == routes.end()){
        //handle route does not exist
        std::cout << "Route: " << route << " does not exist" << std::endl;
    }
    else {
        const std::pair<std::string, std::function<std::string(std::unordered_map<std::string, std::string>&)>>& route_handler = routes.at(route);
        std::string response = route_handler.second(parsed_request);
        std::string response_type = route_handler.first;
    }
}

void WEBPP::Server::responder(int dest_socket){
    // Serve the HTML content
    const char* response = "HTTP/1.1 200 OK\r\n"
                                   "Content-Type: text/html\r\n"
                                   "\r\n"
                                   "<html><body>"
                                   "<h1>Hello, world!</h1>"
                                   "<p>Welcome to my website.</p>"
                                   "</body></html>";
    send(dest_socket, response, strlen(response), 0);
    close(dest_socket);
}

void WEBPP::Server::start(){
    while(true){
        int d_sck = accepter();
        handler();
        responder(d_sck);
    }
}

WEBPP::BindingSocket * WEBPP::Server::get_socket(){
    return socket;
}


void WEBPP::Server::add_route(std::string route, std::pair<std::string, std::function<std::string(std::unordered_map<std::string, std::string>&)>> route_handler){
    routes.insert({route, route_handler});
}


