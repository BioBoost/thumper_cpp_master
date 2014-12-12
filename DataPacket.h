#include <string>

#ifndef TREX_DATA_PACKET_H
#define TREX_DATA_PACKET_H

namespace TRexLib{

    class DataPacket{
        public:
        	/*
        	 * Convert the internal values to a JSON string
        	 *
        	 * @return json string
        	 */
            virtual std::string toJSON(void) = 0;

            /*
             * Parse the json representation of the DataPacket
             * and set the internal values accordingly.
			 *
			 * @json json string representation
             */
            virtual void fromJSON(std::string json) = 0;

        	/*
        	 * Convert the internal values to a char buffer representation ready 
        	 * for writing to the TRex controller using I2C.
        	 *
        	 * @buffer buffer to which the values should be written (should be big enough for all values to fit)
        	 */
            virtual void toTRex(char * buffer) = 0;

            /*
             * Parse the TRex representation of the DataPacket
             * and set the internal values accordingly.
			 *
        	 * @buffer char buffer which contains the values that should be parsed
             */
            virtual void fromTRex(char * data) = 0;
    };
}

#endif