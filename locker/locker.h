#ifndef __LOCKER_H__
#define __LOCKER_H__
#include <pthread.h>

namespace UtilEase
{

class CLMutex
{
public:
    CLMutex()
    {
        pthread_mutex_init(&m_mutex,NULL);
    }
    ~CLMutex()
    {
        pthread_mutex_destroy(&m_mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&m_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
};


class CLEvent
{
public:
    CLEvent(int is_b_sem = true)
    {
        // 类内成员不会自动初始化
        this->m_flag = 0;
        this->m_is_bSem = is_b_sem;
        pthread_mutex_init(&m_mutex,0);
        pthread_cond_init(&m_cond,0);
    }
    virtual ~CLEvent()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }

    void Set()
    {
        pthread_mutex_lock(&m_mutex);
        m_flag++;
        pthread_mutex_unlock(&m_mutex);
        pthread_cond_signal(&m_cond);// 唤醒条件变量上的一个线程
    }
    void SetAll()
    {
        pthread_mutex_lock(&m_mutex);
        m_flag++;
        pthread_mutex_unlock(&m_mutex);
        pthread_cond_broadcast(&m_cond);// 唤醒所有等待线程
    }
    void Wait()
    {
        /**
         * pthread_cond_wait在进入阻塞之前，会解锁
         * 在被唤醒之后，内部又会加锁
         * 因此：
         * 按照 
         *      pthread_mutex_lock
         *      pthread_cond_wait
         *      pthread_mutex_unlock
         * 顺序
        */
        pthread_mutex_lock(&m_mutex);
        while(m_flag == 0)
        {
            pthread_cond_wait(&m_cond,&m_mutex);
        }
        if(m_is_bSem == true){
            m_flag = 0;
        }else{
            m_flag--;
        }
        pthread_mutex_unlock(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    int m_flag;
    int m_is_bSem; // 二进制信号量和计数信号量，分别用于实现互斥访问和资源池管理
};
}


#endif