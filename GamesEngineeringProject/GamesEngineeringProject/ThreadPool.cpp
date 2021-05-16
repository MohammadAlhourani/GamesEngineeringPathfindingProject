#include "ThreadPool.h"

ThreadPool::ThreadPool() {
	
	numThreads = std::thread::hardware_concurrency() - 1;

    for (int i = 0; i < numThreads; i++)
    {
        m_threads.push_back(std::thread(&ThreadPool::infiniteLoopFunc, this));
    }
}

ThreadPool::~ThreadPool() 
{
}

void ThreadPool::push(std::function<void()> func)
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_function_queue.push(func);
    // when we send the notification immediately, the consumer will try to get the lock , so unlock asap
    lock.unlock();
    m_data_condition.notify_one();
}

void ThreadPool::done()
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_accept_functions = false;
    lock.unlock();
    // when we send the notification immediately, the consumer will try to get the lock , so unlock asap
    m_data_condition.notify_all();
    //notify all waiting threads.
}

void ThreadPool::infiniteLoopFunc(ThreadPool* t_pool)
{
    std::function<void()> func;
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(t_pool->m_lock);          

            t_pool->m_data_condition.wait(lock, [&]() {return !t_pool->m_function_queue.empty() || t_pool->m_accept_functions; });
            if (!t_pool->m_accept_functions && t_pool->m_function_queue.empty())
            {
                //lock will be release automatically.
                //finish the thread loop and let it join in the main thread.
                return;
            }
            func = t_pool->m_function_queue.front();
            t_pool->m_function_queue.pop();
            //release the lock
        }
        func();
    }
}

int ThreadPool::getThreadNums()
{
    return numThreads;
}
