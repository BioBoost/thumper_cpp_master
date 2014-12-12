#include "I2C.h"
#include <string.h>

namespace TRexLib{

    /*
     * Constructor
     *
     * @device the device path of the I2C bus (for example /dev/i2c-1)
     * @i2caddress the I2C slave device address
     */
    I2C::I2C(const char * device, int i2caddress)
    {
        // Copy the device path
        strcpy(this->device, device);
    }
}