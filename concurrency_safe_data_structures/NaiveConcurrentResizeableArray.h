//
// Created by Ivan Riumkin on 2026-03-30.
//

#ifndef MAKINGDSS_NAIVECONCURRENTRESIZEABLEARRAY_H
#define MAKINGDSS_NAIVECONCURRENTRESIZEABLEARRAY_H

#include <cstddef>
#include <mutex>
#include <iostream>

template<typename T>
class NaiveConcurrentResizeableArray {
public:
    NaiveConcurrentResizeableArray() {
        arr = new T[16];
        capacity = 16;
        currentSize = 0;
    }

    ~NaiveConcurrentResizeableArray() {
        delete[] this->arr;
    }

    NaiveConcurrentResizeableArray(const NaiveConcurrentResizeableArray &) = delete;

    NaiveConcurrentResizeableArray &operator=(const NaiveConcurrentResizeableArray &) = delete;

    void append(T item) {
        try {
            arrayMutex.lock();
            if (currentSize == capacity) {
                resizeUp();
            }
            arr[currentSize] = item;
            currentSize++;
            arrayMutex.unlock();
        } catch (...) {
            arrayMutex.unlock();
        }
    }

    T pop() {
        try {
            arrayMutex.lock();
            if (currentSize == 0) {
                throw std::out_of_range("pop() called on empty array");
            }

            T item = arr[currentSize - 1];
            currentSize--;

            if (currentSize <= capacity / 4) {
                resizeDown();
            }
            arrayMutex.unlock();
            return item;
        } catch (...) {
            arrayMutex.unlock();
            throw std::out_of_range("pop() called on non-empty array");
        }
    }

    T getValue(int index) {
        try {
            arrayMutex.lock();
            if (index < 0 || index >= currentSize) {
                throw std::out_of_range("index out of range");
            }
            T item = arr[index];
            arrayMutex.unlock();
            return item;
        } catch (...) {
            throw std::out_of_range("index out of range");
        }
    }

    size_t getSize() {
        arrayMutex.lock();
        size_t sz = currentSize;
        arrayMutex.unlock();
        return sz;
    }

    size_t getCapacity() {
        arrayMutex.lock();
        size_t cp = capacity;
        arrayMutex.unlock();
        return cp;
    }

private:
    T *arr;
    std::size_t capacity;
    size_t currentSize;
    std::mutex arrayMutex;

    void resizeUp() {
        capacity *= 2;

        T *newArr = new T[capacity];

        for (int i = 0; i < currentSize; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }

    void resizeDown() {
        if (capacity <= 16) {
            return;
        }

        capacity /= 2;
        T *newArr = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
    }
};


#endif //MAKINGDSS_NAIVECONCURRENTRESIZEABLEARRAY_H
