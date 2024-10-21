#include "util.h"

void time_log(FILE *stream, const char* fmt, ...)
{
    /*auto currentTime = std::chrono::system_clock::now(); // get the time
    auto formattedTime = std::chrono::system_clock::to_time_t(currentTime);
    const char* time_str = std::ctime(&formattedTime);
    fprintf(stream,"%s ", time_str);*/
    va_list arg;
    va_start(arg,fmt);
    vfprintf(stream,fmt,arg);
    va_end(arg);
}

//TODO : Create exit function that destroy Imgui and GLFW 
