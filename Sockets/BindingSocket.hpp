//
//  BindingSocket.hpp
//  WEBPP
//
//  Created by Graeme Bates on 6/12/23.
//

#ifndef BindingSocket_hpp
#define BindingSocket_hpp

#include <stdio.h>
#include <iostream>
#include "MasterSocket.hpp"

namespace WEBPP{
    class BindingSocket : public MasterSocket{
    private:
        int backlog;
        int listener;
    public:
        // Constructor
        BindingSocket(
            int domain, // AF_UNIX for local communication, AF_INET for internet domain
            int type, // SOCK_STREAM, SOCK_DGRAM or SOCK_SEQPACKET (SOCK_STREAM is norm)
            int protocol, // Standard is 0, read https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html
            int port, // Desired PORT ex 80
            u_long interface, // ??
            int backlog
        );
        int connect_to_network(int sck, sockaddr_in addr);
        void start_listening();
        int get_back_log();
        int get_listener();
    };
}

#endif /* BindingSocket_hpp */
