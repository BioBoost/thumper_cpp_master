#include <stdio.h>
#include <stdarg.h>

#ifndef LOG_HEADER
#define LOG_HEADER

namespace TRexLib{
    
    class Log{
        public:
            static void e(char* fmt, ...) {
		        va_list args;
		        va_start(args,fmt);
		        printf("[ERROR] ");
		        vprintf(fmt,args);
		        va_end(args);
            }

            static void w(char* fmt, ...) {
		        va_list args;
		        va_start(args,fmt);
		        printf("[WARNING] ");
		        vprintf(fmt,args);
		        va_end(args);
            }

            static void d(char* fmt, ...) {
		        va_list args;
		        va_start(args,fmt);
		        printf("[DEBUG] ");
		        vprintf(fmt,args);
		        va_end(args);
            }

            static void v(char* fmt, ...) {
		        va_list args;
		        va_start(args,fmt);
		        printf("[VERBOSE] ");
		        vprintf(fmt,args);
		        va_end(args);
            }

    };
}

#endif