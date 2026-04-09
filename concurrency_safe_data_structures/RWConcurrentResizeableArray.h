//
// Created by Ivan Riumkin on 2026-04-02.
//

#ifndef MAKINGDSS_RWCONCURRENTRESIZEABLEARRAY_H
#define MAKINGDSS_RWCONCURRENTRESIZEABLEARRAY_H
#include <shared_mutex>
#include <stdexcept>

template<typename T>
class RWConcurrentResizeableArray {
public:
    RWConcurrentResizeableArray() {
        arr = new T[16];
        capacity = 16;
        currentSize = 0;
    }

    ~RWConcurrentResizeableArray() {
        delete[] this->arr;
    }

    RWConcurrentResizeableArray(const RWConcurrentResizeableArray &) = delete;

    RWConcurrentResizeableArray &operator=(const RWConcurrentResizeableArray &) = delete;

    void append(T item) {
        std::unique_lock uniqueLock(sharedArrayMutex);
        if (currentSize == capacity) {
            resizeUp();
        }
        arr[currentSize] = item;
        currentSize++;
    }

    T pop() {
        std::unique_lock uniqueLock(sharedArrayMutex);
        if (currentSize == 0) {
            throw std::out_of_range("pop() called on empty array");
        }

        T item = arr[currentSize - 1];
        currentSize--;

        if (currentSize <= capacity / 4) {
            resizeDown();
        }
        return item;
    }

    T getValue(int index) {
        std::shared_lock sharedLock(sharedArrayMutex);
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("index out of range");
        }
        T item = arr[index];
        return item;
    }

    size_t getSize() {
        std::shared_lock sharedLock(sharedArrayMutex);
        return currentSize;
    }

    size_t getCapacity() {
        std::shared_lock sharedLock(sharedArrayMutex);
        return capacity;
    }

private:
    T *arr;
    std::size_t capacity;
    size_t currentSize;
    std::shared_mutex sharedArrayMutex;

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


#endif //MAKINGDSS_RWCONCURRENTRESIZEABLEARRAY_H
