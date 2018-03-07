#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "mbed.h"

template <class T, size_t N>
class StaticQueue {
  public:
    StaticQueue();
    virtual ~StaticQueue(void);

    void push_back(T value);
    T get();
    void reset();
    bool empty();

  private:
    size_t head_;
    size_t tail_;
    Mutex _mutex;
    T buf_[(N + 1)];
};

template <class T, size_t N>
StaticQueue<T, N>::StaticQueue():
    head_(0),
    tail_(0) {
}

template <class T, size_t N>
StaticQueue<T, N>::~StaticQueue(void) {
}

template <class T, size_t N>
T StaticQueue<T, N>::get() {
    _mutex.lock();

    if (empty()) {
        return T();
    }

    // Read data and advance the tail (we now have a free space)
    T val = buf_[tail_];
    tail_ = (tail_ + 1) % (N + 1);

    _mutex.unlock();

    return val;
}

template <class T, size_t N>
void StaticQueue<T, N>::push_back(T value) {
    _mutex.lock();

    buf_[head_] = value;
    head_ = (head_ + 1) % (N + 1);

    if (head_ == tail_) {
        tail_ = (tail_ + 1) % (N + 1);
    }

    _mutex.unlock();
}

template <class T, size_t N>
void StaticQueue<T, N>::reset() {
    _mutex.lock();
    head_ = tail_;
    _mutex.unlock();
}

template <class T, size_t N>
bool StaticQueue<T, N>::empty() {
    return head_ == tail_;
}

#endif
