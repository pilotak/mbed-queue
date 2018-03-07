#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H

#include "mbed.h"
#include <queue>
#include <climits>

template <class T, size_t N>
class DynamicQueue {
  public:
    DynamicQueue();
    virtual ~DynamicQueue(void);

    void push_back(T value);
    void push_front(T value);
    T get();
    void reset();
    size_t size();
    bool empty();

  private:
    Mutex _mutex;
    deque<T> _queue;
};

template <class T, size_t N>
DynamicQueue<T, N>::DynamicQueue() {
}

template <class T, size_t N>
DynamicQueue<T, N>::~DynamicQueue(void) {
}

template <class T, size_t N>
T DynamicQueue<T, N>::get() {
    if (_queue.size() == 0) {
        return T();
    }

    _mutex.lock();
    T res = _queue.front();
    _queue.pop_front();
    _mutex.unlock();

    return res;
}

template <class T, size_t N>
void DynamicQueue<T, N>::push_back(T value) {
    _mutex.lock();
    _queue.push_back(value);

    if (_queue.size() > N) {
        _queue.pop_front();
    }

    _mutex.unlock();
}

template <class T, size_t N>
void DynamicQueue<T, N>::push_front(T value) {
    _mutex.lock();
    _queue.push_front(value);

    if (_queue.size() > N) {
        _queue.pop_back();
    }

    _mutex.unlock();
}

template <class T, size_t N>
void DynamicQueue<T, N>::reset() {
    _mutex.lock();

    for (size_t i = 0; i < _queue.size(); ++i) {
        _queue.pop_front();
    }

    _mutex.unlock();
}

template <class T, size_t N>
size_t DynamicQueue<T, N>::size() {
    return _queue.size();
}

template <class T, size_t N>
bool DynamicQueue<T, N>::empty() {
    return _queue.size() == 0;
}

#endif
