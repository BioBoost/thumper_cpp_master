#include "I2C.h"

#ifndef MY_I2C_HEADER
#define MY_I2C_HEADER

namespace TRexLib{

    class MyI2C: public I2C{
        public:
            /*
             * Constructor
             *
             * @device the device path of the I2C bus (for example /dev/i2c-1)
             * @i2caddress the I2C slave device address
             */
            MyI2C(const char * device, int i2caddress);

            /*
             * Write data to an I2C slave device.
             *
             * @address the I2C slave device address (not actually used but kept for compatibility with mbed functions)
             * @data buffer containing the bytes that should be written to the slave
             * @length number of bytes in the buffer to write
             *
             * @return 0 on failure
             */
		int write(int address, char * data, int length);

            /*
             * Read data from an I2C slave device.
             *
             * @address the I2C slave device address (not actually used but kept for compatibility with mbed functions)
             * @data buffer to store the byte values received from the device
             * @length number of bytes to read from the device (should be at least size of data buffer)
             *
             * @return 0 on failure
             */
		int read(int address, char * data, int length);

        protected:
            /*
             * Open the I2C bus device so the read and write functions can be used.
             *
             * @return a non-negative integer if the open action was succesful
             */
            int openBus(void);

            /*
             * Set the slave device address and thereby acquire the bus.
             *
             * @i2caddress the I2C slave device address
             *
             * @return a non-negative integer if the aquire action was succesful
             */
            int acquireBus(int i2caddress);
    };
}

#endif