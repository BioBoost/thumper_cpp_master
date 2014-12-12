#include "MyTRex.h"
#include "MyStatusDataPacket.h"
#include "MyI2C.h"
#include "wait.h"

using namespace TRexLib;

int main(int argc, char* argv[]) {
    char status[StatusDataPacket::SIZE_STATUS_DATA_PACKET];
    char command[CommandDataPacket::SIZE_TREX_DATA_PACKET];

    if (argc < 3) {
        printf("Usage:\r\n");
        printf("\ti2c_pi_trex_master <device_path> <address>\r\n");
        printf("\ti2c_pi_trex_master <device_path> <address> <command_buffer>\r\n");
        return -1;
    }

    char * device = argv[1];
    int address = atoi(argv[2]);

    // We need to supply the device path
    MyI2C i2c(device, address);    
    MyTRex trex(&i2c, address);

    if (argc == 3) { // Status request
        // Read the status of the device and output to stdout
        if (trex.readStatus(status, StatusDataPacket::SIZE_STATUS_DATA_PACKET)) {
            for (int i = 0; i < StatusDataPacket::SIZE_STATUS_DATA_PACKET; i++) {
                printf("%d ", status[i]);
            }
            printf("\r\n");
        } else {
            return -1;
        }
    }
     else if (argc == (3 + CommandDataPacket::SIZE_TREX_DATA_PACKET)) {
        // Get the command data
        for (int i = 0; i < CommandDataPacket::SIZE_TREX_DATA_PACKET; i++) {
            command[i] = atoi(argv[3+i]);
        }

        trex.writeCommand(command, CommandDataPacket::SIZE_TREX_DATA_PACKET);
        TRexLib::wait(0.02);
        
        // Read the status        
        trex.readStatus(status, StatusDataPacket::SIZE_STATUS_DATA_PACKET);

        // Return status
        for (int i = 0; i < StatusDataPacket::SIZE_STATUS_DATA_PACKET; i++) {
            printf("%d ", status[i]);
        }
        printf("\r\n");
    }

    return 0;
}
