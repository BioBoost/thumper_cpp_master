#include "TRex.h"
#include <arpa/inet.h>

#ifndef TCP_DAEMON_HEADER
#define TCP_DAEMON_HEADER

namespace TRexLib{
    
    class TcpDaemon{
        public:
            const static int BUFFER_SIZE = 4096;
            const static int MAX_BACKLOG_CONNECTIONS = 3;

        private:
            TRex * trex;
            int server_port;
            int socket_desc;

            struct sockaddr_in server;
            struct sockaddr_in client;

            char buffer[BUFFER_SIZE+1];
            bool keepListening;

        public:
            /*
             * TcpDaemon constructor
             *
             * @trex the trex which this daemon is controlling
             * @server_port the port the daemon will be listening on
             */
            TcpDaemon(TRex * trex, int server_port);

            /*
             * Make the daemon start listening for incoming connections
             */
            void startListening();

        private:
            /*
             * Create server socket
             *
             * @return true on success
             */
            bool createSocket();

            /*
             * Bind to server socket
             *
             * @return true on success
             */
            bool bindSocket();

            /*
             * Listen for incoming connections
             */
            void doListen();
    };
}

#endif