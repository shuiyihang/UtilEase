#include "log/log.h"
#include "locker/locker.h"


void* test_fun(void* arg)
{
    for(int i = 0;i < 100;i++)
    {
        LOG_INFO("thread %d %s",pthread_self()," entry");
        UtilEase::CLEvent* val = (UtilEase::CLEvent*)arg;
        LOG_INFO("thread %d %s",pthread_self()," return");
    }
    UtilEase::CLEvent* cond = (UtilEase::CLEvent*)arg;
    cond->Set();
}
int main()
{
    UtilEase::CLEvent cond;
    pthread_t tid_1;
    pthread_t tid_2;
    pthread_t tid_3;
    pthread_create(&tid_1,nullptr,test_fun,&cond);// fork 返回新创建的子进程的进程ID
    pthread_detach(tid_1);
    pthread_create(&tid_2,nullptr,test_fun,&cond);// fork 返回新创建的子进程的进程ID
    pthread_detach(tid_2);
    pthread_create(&tid_3,nullptr,test_fun,&cond);// fork 返回新创建的子进程的进程ID
    pthread_detach(tid_3);

    cond.Wait();
    cond.Wait();
    cond.Wait();

    LOG_DEBUG("%s %s",__func__," return");
    return 0;
}