#include "Serial.h"
#include <stdio.h>
#include <stdarg.h>

namespace TRexLib{
    
    Serial::Serial()
    { }
 
    void Serial::printf(char* fmt, ...)
    {
        va_list args;
        va_start(args,fmt);
        vprintf(fmt,args);
        va_end(args);
    }
}