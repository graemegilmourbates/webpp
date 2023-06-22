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
#include <mbedtls/net_sockets.h>
#include <mbedtls/ssl.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/debug.h>
#include <mbedtls/error.h>
#include <thread>

#include "../Sockets/webpp-sockets.hpp"
#include "../Responders/webpp-responders.hpp"
#include "../Utilities/webpp-utilities.hpp"

// Define "route handler" function to make more readable
using ROUTE_HANDLER = std::function<void(WEBPP::Responder& responder, std::unordered_map<std::string, std::string>& request)>;

namespace WEBPP{
    class Server{
    private:
        BindingSocket * socket;
        mbedtls_ssl_context ssl;
        // Key: "/route" Package: route_handler()
        std::unordered_map<std::string, ROUTE_HANDLER&> routes;
        
        void init_ssl();
        
        int accept_client();
        void attach_ssl_to_client_sock();
        void handler(int client_sock);
        int max_clients;
        
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
