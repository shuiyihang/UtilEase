#ifndef __LOG_H__
#define __LOG_H__

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include "../locker/locker.h"
namespace UtilEase
{

class CLLog
{
public:
    static CLLog* get_instance();
    void write_log(int level,const char* format,...);
private:

    CLLog();
    ~CLLog();
private:
    FILE* m_fp;
    char* m_log_buff;
    static CLLog* m_pLog;
    bool m_switch_log;
    CLMutex m_mutex;
};

}

#define ENABLE_DEBUG    1

#if ENABLE_DEBUG == 1
    #define LOG_DEBUG(format, ...) {UtilEase::CLLog::get_instance()->write_log(0, format, ##__VA_ARGS__);}
    #define LOG_INFO(format, ...) {UtilEase::CLLog::get_instance()->write_log(1, format, ##__VA_ARGS__);}
    #define LOG_WARN(format, ...) {UtilEase::CLLog::get_instance()->write_log(2, format, ##__VA_ARGS__);}
    #define LOG_ERROR(format, ...) {UtilEase::CLLog::get_instance()->write_log(3, format, ##__VA_ARGS__);}
#else
    #define LOG_DEBUG(format, ...)
    #define LOG_INFO(format, ...)
    #define LOG_WARN(format, ...)
    #define LOG_ERROR(format, ...)
#endif













#endif