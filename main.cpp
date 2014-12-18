#include "MyTRex.h"
#include "MyStatusDataPacket.h"
#include "MyI2C.h"
#include "wait.h"

#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

using namespace TRexLib;

const int MAX_BACKLOG_CONNECTIONS = 3;
const int BUFFER_SIZE = 4096;
const char END_MSG_SEQUENCE[] = "\r\n\r\n";

/*
 * Start the deamon for the TRex controller
 */
int deamon(char * i2c_device, int i2c_address, int server_port) {
    int socket_desc, client_sock, address_length, read_size;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE+1];
    bool keepListening = true;

    // Command and status buffer
    char status[StatusDataPacket::SIZE_STATUS_DATA_PACKET];
    char command[CommandDataPacket::SIZE_TREX_DATA_PACKET];

    // Create TCP socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("Could not create socket\r\n");
        return -1;
    } else {
        printf("Listening socket created\r\n");
    }
     
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(server_port);
     
    // Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("Bind failed. Error\r\n");
        return -1;
    } else {
        printf("Bind ok\r\n");
    }

    // Open the i2c device
    // MyI2C i2c(i2c_device, i2c_address);    
    // MyTRex trex(&i2c, i2c_address);

    // Start listening
    while (keepListening) {
        // Listen for incomming connections (second param determines 
        // the maximum length that the queue of pending connections may grow to)
        listen(socket_desc, MAX_BACKLOG_CONNECTIONS);
        printf("Waiting for incoming connection ...\r\n");
         
        // Accept connection from an incoming client
        address_length = sizeof(struct sockaddr_in);
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&address_length);
        if (client_sock < 0) {
            perror("Client accept failed\r\n");
        } else {
            printf("Client connected\r\n");

            // Keep receiving messages from the client the client
            while((read_size = recv(client_sock, buffer, 48, 0)) > 0) {
                int total_read_size = read_size;

                // Keep reading until full message is received
                char * end = strstr(buffer, END_MSG_SEQUENCE);
                while (total_read_size < BUFFER_SIZE && read_size > 0 && end == NULL) {
                    read_size = recv(client_sock, buffer+total_read_size, BUFFER_SIZE-total_read_size, 0);
                    total_read_size += read_size;
                    end = strstr(buffer, END_MSG_SEQUENCE);
                }

                if (end != NULL) {
                    // Full string received, lets do our thing
                    buffer[total_read_size] = '\0';
                    printf("Received: %s\r\n", buffer);
                } else {
                    perror("Buffer full\r\n");
                }

                //Send the message back to client
                //write(client_sock , buffer , strlen(buffer));

                printf("Awaiting new command\r\n");
            }
             
            // Check if client disconnected or receive failed
            if(read_size == 0) {
                printf("Client disconnected\r\n");
                fflush(stdout);
            }
            else if(read_size == -1) {
                perror("recv failed\r\n");
            }
        }
    }

    return 0;
}
 
int main(int argc, char* argv[])
{
    // Check arguments
    if (argc < 4) {
        printf("Usage:\r\n");
        printf("\ti2c_pi_trex_master <device_path> <address> <server_port>\r\n");
        return -1;
    }

    // Get server port
    char * i2c_device = argv[1];
    int i2c_address = atoi(argv[2]);
    int server_port = atoi(argv[3]);
     
    // Start the daemon
    int result = deamon(i2c_device, i2c_address, server_port);

    return result;
}
