#ifndef SERIAL_HEADER
#define SERIAL_HEADER

namespace TRexLib{
    
    class Serial{
        public:
            Serial(void);
            void printf(char* fmt, ...);
    };
}

#endif