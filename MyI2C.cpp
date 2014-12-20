#include "MyI2C.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>          //O_RDWR
#include <stdio.h>          //perror

namespace TRexLib{
    
    /*
     * Pointer to write function used for i2c communication.
     * Also see http://linux.die.net/man/2/write
     */
    ssize_t (* pi_i2c_write)(int, const void *, size_t) = write;
    
    /*
     * Pointer to read function used for i2c communication.
     * Also see http://linux.die.net/man/2/read
     */
    ssize_t (* pi_i2c_read)(int, void *, size_t) = read;

    /*
     * Constructor
     *
     * @device the device path of the I2C bus (for example /dev/i2c-1)
     * @i2caddress the I2C slave device address
     */
    MyI2C::MyI2C(const char * device, int i2caddress)
        : I2C(device, i2caddress)
    {
        if (this->openBus() < 0) {
            /* ERROR HANDLING: you can check errno to see what went wrong */
            perror("Failed to open the i2c bus");
            printf("Failed to open the i2c bus");
        }

        if (this->acquireBus(i2caddress) < 0) {
            /* ERROR HANDLING: you can check errno to see what went wrong */
            perror("Failed to acquire the i2c bus");
            printf("Failed to acquire the i2c bus");
        }
    }

    /*
     * Open the I2C bus device so the read and write functions can be used.
     *
     * @return a non-negative integer if the open action was succesful
     */
    int MyI2C::openBus(void)
    {
        // In order to communicate with an I²C peripheral with this simple structure,
        // you must first open the bus for reading and writing like you would any file.
        // A call to open must be used rather than fopen so that writes to the bus are not buffered.
        // Open returns a new file descriptor (a non-negative integer) which can then be used to configure the bus.

        return (this->handle = open(this->device, O_RDWR));
    }

    /*
     * Set the slave device address and thereby acquire the bus.
     *
     * @i2caddress the I2C slave device address
     *
     * @return a non-negative integer if the aquire action was succesful
     */
    int MyI2C::acquireBus(int i2caddress)
    {
        // Before the device can be used for communication we need to set the slave address. This can be achieved using 
        // an ioctl function call.
        return (ioctl(this->handle, I2C_SLAVE, i2caddress) < 0);
    }

    /*
     * Write data to an I2C slave device.
     *
     * @address the I2C slave device address (not actually used but kept for compatibility with mbed functions)
     * @data buffer containing the bytes that should be written to the slave
     * @length number of bytes in the buffer to write
     *
     * @return the actual number of bytes written or -1 on failure
     */
    int MyI2C::write(int address, char * data, int length)
    {
        /*
            We need to use the pi_i2c_write function pointer here and not the write function.
            Using the write function would lead to a recursive call and a stack overflow.
        */

        int bytes_written = 0;
        int total_bytes_written = 0;

        do {
            bytes_written = pi_i2c_write(this->handle, data+total_bytes_written, length-total_bytes_written);
            if (bytes_written != -1) {
                total_bytes_written += bytes_written;
            }
        } while (bytes_written != -1 && total_bytes_written < length);

        if (bytes_written != -1) {
            return total_bytes_written;
        } else {
            return bytes_written;
        }
    }

    /*
     * Read data from an I2C slave device.
     *
     * @address the I2C slave device address (not actually used but kept for compatibility with mbed functions)
     * @data buffer to store the byte values received from the device
     * @length number of bytes to read from the device (should be at least size of data buffer)
     *
     * @return the actual number of bytes read or -1 on failure
     */
    int MyI2C::read(int address, char * data, int length)
    {
        /*
            We need to use the pi_i2c_read function pointer here and not the read function.
            Using the read function would lead to a recursive call and a stack overflow.
        */

        int bytes_read = 0;
        int total_bytes_read = 0;

        do {
            bytes_read = pi_i2c_read(this->handle, data+total_bytes_read, length-total_bytes_read);
            if (bytes_read != -1) {
                total_bytes_read += bytes_read;
            }
        } while (bytes_read != -1 && total_bytes_read < length);

        if (bytes_read != -1) {
            return total_bytes_read;
        } else {
            return bytes_read;
        }
    }
}