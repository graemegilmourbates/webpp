//
//  Server.hpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//
//
// Should be noted that all routes are assumed to be json api calls(for now)

#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <unordered_map>
#include <sys/time.h>

#include "../Sockets/webpp-sockets.hpp"
#include "../Utilities/webpp-utilities.hpp"
#include "../Responders/webpp-responders.hpp"

// Define "route handler" function to make more readable
using ROUTE_HANDLER = std::function<void(WEBPP::Responder& responder, std::unordered_map<std::string, std::string>& request)>;

namespace WEBPP{
    class Server{
    private:
        char buffer[30000];
        BindingSocket * socket;
        // Key: "/route" Package: route_handler()
        std::unordered_map<std::string, ROUTE_HANDLER&> routes;
        int accepter();
        void handler(int dst_sck);
        void route();
        int max_clients;
        int client_sockets[];
    public:
        Server(
            int domain, int service, int protocol,
            int port, u_long interface, int bcklg
        );
        ~Server();
        void start();
        BindingSocket * get_socket();
        void add_route(std::string route, ROUTE_HANDLER);
    };
}

#endif /* Server_hpp */
