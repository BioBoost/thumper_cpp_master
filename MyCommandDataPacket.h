#include "CommandDataPacket.h"

#ifndef TREX_MY_COMMAND_DATA_PACKET_H
#define TREX_MY_COMMAND_DATA_PACKET_H

namespace TRexLib{

    class MyCommandDataPacket: public CommandDataPacket{

        public:
            /*
             * Constructor
             */
            MyCommandDataPacket(void);

        /* Parse methods */
        public:
            /*
             * Convert the internal values to a JSON string
             *
             * @return json string
             */
            std::string toJSON(void);

            /*
             * Parse the json representation of the DataPacket
             * and set the internal values accordingly.
             *
             * @json json string representation
             */
            void fromJSON(std::string json);

            /*
             * Convert the internal values to a char buffer representation ready 
             * for writing to the TRex controller using I2C.
             *
             * @buffer buffer to which the values should be written (should be big enough for all values to fit)
             */
            void toTRex(char * buffer);

            /*
             * Parse the TRex representation of the DataPacket
             * and set the internal values accordingly.
             *
             * @buffer char buffer which contains the values that should be parsed
             */
            void fromTRex(char * data);
    };
};

#endif