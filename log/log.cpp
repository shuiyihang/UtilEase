#include "log.h"


namespace UtilEase
{
    #define BUFF_SIZE_LOG_FILE  1024
    #define FILE_NAME   "debug.txt"
    CLLog* CLLog::m_pLog = 0;
    CLLog::CLLog()
    {
        m_log_buff = new char[BUFF_SIZE_LOG_FILE];
        m_fp = fopen(FILE_NAME,"w+");
    }

    CLLog* CLLog::get_instance()
    {
        if(m_pLog == 0)
        {
            m_pLog = new CLLog;
        }
        return m_pLog;
    }

    void CLLog::write_log(int level,const char* format,...)
    {
        char type[16] = {0};
        switch (level)
        {
        case 0:
            strcpy(type, "[debug]:");
            break;
        case 1:
            strcpy(type, "[info]:");
            break;
        case 2:
            strcpy(type, "[warn]:");
            break;
        case 3:
            strcpy(type, "[erro]:");
            break;
        default:
            strcpy(type, "[info]:");
            break;
        }

        va_list valst;
        va_start(valst,format);//第一个参数为va_list型变量，第二个参数为省略参数前的第一个参数，这个参数不可省略

        m_mutex.lock();

        int len_1 = snprintf(m_log_buff,16,"%s ",type);

        int len_2 = vsnprintf(m_log_buff + len_1,BUFF_SIZE_LOG_FILE - len_1 - 1,format,valst);

        m_log_buff[len_1+len_2] = '\n';
        m_log_buff[len_1+len_2+1] = '\0';

        fputs(m_log_buff,m_fp);

        fflush(m_fp);
        m_mutex.unlock();

        va_end(valst);
    }
}