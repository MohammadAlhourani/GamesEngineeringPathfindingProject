#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <mutex>
#include <stack>
#include <queue>
#include <condition_variable>


class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();

	void push(std::function<void()> func);

	void done();

	static void infiniteLoopFunc(ThreadPool* t_pool);

	int getThreadNums();

private:

	int numThreads;

	std::condition_variable m_condition;

	std::vector<std::thread> m_threads;

	std::queue<std::function<void()>> m_function_queue;

	std::mutex m_lock;

	std::condition_variable m_data_condition;

	std::atomic<bool> m_accept_functions;

	
};
#endif // !THREAD_POOL_H

