#include "MyTRex.h"
#include "MyI2C.h"
#include "TcpDaemon.h"

using namespace TRexLib;
 
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
     
    // Create i2c and trex
    MyI2C i2c(i2c_device, i2c_address);
    MyTRex trex(&i2c, i2c_address);

    // Start the daemon
    TcpDaemon daemon(&trex, server_port);
    daemon.startListening();

    return 0;
}
