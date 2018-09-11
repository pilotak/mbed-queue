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

#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H

#include <deque>
#include "mbed.h"

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

  T res = _queue.front();
  _queue.pop_front();

  return res;
}

template <class T, size_t N>
void DynamicQueue<T, N>::push_back(T value) {
  _queue.push_back(value);

  if (_queue.size() > N) {
    _queue.pop_front();
  }
}

template <class T, size_t N>
void DynamicQueue<T, N>::push_front(T value) {
  _queue.push_front(value);

  if (_queue.size() > N) {
    _queue.pop_back();
  }
}

template <class T, size_t N>
void DynamicQueue<T, N>::reset() {
  for (size_t i = 0; i < _queue.size(); ++i) {
    _queue.pop_front();
  }
}

template <class T, size_t N>
size_t DynamicQueue<T, N>::size() {
  return _queue.size();
}

template <class T, size_t N>
bool DynamicQueue<T, N>::empty() {
  return _queue.size() == 0;
}

#endif  // DYNAMICQUEUE_H
