#ifndef CONCURRENT_QUEUE_H_
#define CONCURRENT_QUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue {
 public:
  T pop () {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
      cond_.wait(mlock);
    }
    auto val = queue_.front();
    queue_.pop();
    mlock.unlock();
    cond_.notify_one();
    return val;
  }

  void pop (T& item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty()) {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
    mlock.unlock();
    cond_.notify_one();
  }

  void push (const T& item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.size() >= BUFFER_SIZE) {
      cond_.wait(mlock);
    }
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
  ConcurrentQueue()=default;
  ConcurrentQueue(const ConcurrentQueue&) = delete;            // disable copying
  ConcurrentQueue& operator=(const ConcurrentQueue&) = delete; // disable assignment
  
  unsigned int getCurrentQSize (void) {
    return queue_.size();
  }
    
 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
  const static unsigned int BUFFER_SIZE = 1000;
};

extern ConcurrentQueue <Transaction *> conQ;

#endif
