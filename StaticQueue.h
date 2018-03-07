/*
MIT License

Copyright (c) 2018 Pavel Slama

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
