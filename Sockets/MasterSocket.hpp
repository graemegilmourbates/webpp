//
//  MasterSocket.hpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#ifndef MasterSocket_hpp
#define MasterSocket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace WEBPP{
    class MasterSocket{
    private:
        struct sockaddr_in6 address;
        int sock;
    public:
        // Constructor
        MasterSocket(
            int domain, // AF_UNIX for local communication, AF_INET for internet domain
            int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
            int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
            int port, // Desired PORT ex 80
            u_long interface // ??
        );
        // Virutal function will need to be fufilled by child class
        // Connect to network will differ depending on the socket
        virtual int connect_to_network(int sck, struct sockaddr_in6 addr) = 0;
        // Verify that socket connected
        void check_connection(int sck);
        struct sockaddr_in6 get_address();
        int get_sock();
    };
}
#endif /* MasterSocket_hpp */
