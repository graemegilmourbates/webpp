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

namespace WEBPP{
    class Server{
    private:
        char buffer[30000];
        BindingSocket * socket;
        // Routes hash table will accept a string representing the "/route" and
        // a reference to a function, that will handle the route.
        // The referenced route funtion must take in a reference to the request.
        std::unordered_map<std::string, std::function<std::string(int dst_sck, std::unordered_map<std::string, std::string>&)>> routes;
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
        //This is a bit of a mess,
        //Essentially, a route consists of a string "/route"
        //A pair, thats first element is the reponse type(for now just a string html, json etc...) Will need to standardize with a enum or something
        //and get a helper that will load the header
        //The second element of the pair is the function that will do the route work.
        void add_route(std::string, std::function<std::string(int dest_sck, std::unordered_map<std::string, std::string>&)>);
    };
}

#endif /* Server_hpp */
