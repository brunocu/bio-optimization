#pragma once
#include <functional>
#include <mutex>
#include <queue>
// adapted from
// https://stackoverflow.com/a/32593825

class ThreadPool
{
public:
    void Start();
    void push(const std::function<void()> &job);
    void Stop();
    bool busy();

private:
    void ThreadLoop();

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
};

