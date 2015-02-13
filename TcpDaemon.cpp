#include "TcpDaemon.h"
#include "Log.h"
#include "TRex.h"
#include "MyStatusDataPacket.h"
#include "MyCommandDataPacket.h"
#include "rapidjson/document.h"
#include "wait.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace rapidjson;
using namespace std;

// Incomming message end
#define END_MSG_SEQUENCE "\r\n\r\n"

// Outgoing message end
#define END_STATUS_SEQUENCE "\r\n"

namespace TRexLib{
    /*
     * TcpDaemon constructor
     *
     * @trex the trex which this daemon is controlling
     * @server_port the port the daemon will be listening on
     */
    TcpDaemon::TcpDaemon(TRex * trex, int server_port) {
        this->trex = trex;
        this->server_port = server_port;
        this->keepListening = true;
    }

    /*
     * Make the daemon start listening for incoming connections
     */
    void TcpDaemon::startListening() {
        if (this->createSocket() && this->bindSocket()) {
            this->doListen();
        }
    }

    /*
     * Create server socket
     *
     * @return true on success
     */
    bool TcpDaemon::createSocket() {
        // Create TCP socket
        this->socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        if (this->socket_desc == -1) {
            Log::e("Could not create socket\r\n");
            return false;
        } else {
            Log::d("Listening socket created\r\n");
            return true;
        }
    }

    /*
     * Bind to server socket
     *
     * @return true on success
     */
    bool TcpDaemon::bindSocket() {
        // Prepare the sockaddr_in structure
        this->server.sin_family = AF_INET;
        this->server.sin_addr.s_addr = INADDR_ANY;
        this->server.sin_port = htons(this->server_port);
         
        // Bind
        if( bind(this->socket_desc,(struct sockaddr *)&this->server , sizeof(this->server)) < 0) {
            Log::e("Bind failed. Error\r\n");
            return false;
        } else {
            Log::d("Bind ok\r\n");
            return true;
        }
    }

    /*
     * Listen for incoming connections
     */
    void TcpDaemon::doListen() {
        // Start listening
        while (this->keepListening) {
            // Listen for incomming connections (second param determines 
            // the maximum length that the queue of pending connections may grow to)
            listen(this->socket_desc, MAX_BACKLOG_CONNECTIONS);
            Log::d("Waiting for incoming connection ...\r\n");
             
            // Accept connection from an incoming client
            int address_length = sizeof(struct sockaddr_in);
            int client_sock = accept(this->socket_desc, (struct sockaddr *)&this->client, (socklen_t*)&address_length);
            if (client_sock < 0) {
                Log::w("Client accept failed\r\n");
            } else {
                Log::d("Client connected\r\n");

                // Keep receiving messages from the client the client
                int read_size = 0;
                while((read_size = recv(client_sock, this->buffer, BUFFER_SIZE, 0)) > 0) {
                    int total_read_size = read_size;

                    // Keep reading until full message is received
                    char * end = strstr(this->buffer, END_MSG_SEQUENCE);
                    while (total_read_size < BUFFER_SIZE && read_size > 0 && end == NULL) {
                        read_size = recv(client_sock, this->buffer+total_read_size, BUFFER_SIZE-total_read_size, 0);
                        total_read_size += read_size;
                        end = strstr(this->buffer, END_MSG_SEQUENCE);
                    }

                    // Null-terminate json string
                    this->buffer[total_read_size] = '\0';

                    if (end != NULL) {
                        // Command and status packets
                        MyStatusDataPacket status;
                        MyCommandDataPacket command;

                        // Full string received, lets do our thing
                        Log::v("Received: %s\r\n", this->buffer);

                        // First we need to decide if it is a status request or a command push
                        // This can be determined by the "request" key

                        // First we need to parse the json string
                        Document doc;
                        doc.Parse(this->buffer);

                        // Get the "request" value
                        const char * request = doc["request"].GetString();
                        Log::v("request: %s\r\n", request);

                        if (strcmp(request, "command") == 0) {
                            // First populate the command with the json info
                            string json(buffer);
                            command.fromJSON(json);
                            Log::v("Command parsed from JSON: %s\r\n", command.toJSON().c_str());
                            
                            // Next we send the command to the trex
                            if (trex->writeCommand(&command)) {
                                Log::v("Command send to Trex successfully\r\n");
                            } else {
                                Log::e("Command send to Trex failed\r\n");
                            }

                            // Wait some time
                            wait(0.02);
                        }

                        // Read the status of the device
                        if (this->trex->readStatus(&status)) {
                            // Get the json string and send it to the client
                            const char * status_result = status.toJSON().c_str();
                            write(client_sock, status_result, strlen(status_result));
                            write(client_sock, END_STATUS_SEQUENCE, strlen(END_STATUS_SEQUENCE));   // Indicate end
                            Log::d("Read status from TRex: %s\r\n", status_result);
                        } else {
                            Log::e("Status read failed\r\n");
                        }
                    } else {
                        Log::w("Buffer full\r\n");
                    }

                    Log::d("Awaiting new command\r\n");
                }
                 
                // Check if client disconnected or receive failed
                if(read_size == 0) {
                    Log::d("Client disconnected\r\n");
                    fflush(stdout);
                }
                else if(read_size == -1) {
                    Log::e("recv failed\r\n");
                }
            }
        }
    }
}