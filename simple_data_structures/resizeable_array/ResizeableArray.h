//
// Created by Ivan Riumkin on 2026-03-29.
//

#ifndef MAKINGDSS_RESIZEABLEARRAY_H
#define MAKINGDSS_RESIZEABLEARRAY_H
#include <iostream>
#include <stdexcept>


template<typename T>
class ResizeableArray {
public:
    ResizeableArray() {
        arr = new T[10];
        capacity = 10;
        currentSize = 0;
    }

    ~ResizeableArray() {
        delete[] this->arr;
    }

    ResizeableArray(const ResizeableArray &) = delete;

    ResizeableArray &operator=(const ResizeableArray &) = delete;

    void append(T item) {
        if (currentSize == capacity) {
            resizeUp();
        }
        arr[currentSize] = item;
        currentSize++;
    }

    T pop() {
        if (currentSize == 0) {
            throw std::out_of_range("pop() called on empty array");
        }
        if (currentSize == capacity / 4) {
            resizeDown();
        }
        currentSize--;
        T item = arr[currentSize];
        return item;
    }

    T getValue(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("index out of range");
        }
        return arr[index];
    }

    int getSize() {
        return currentSize;
    }

    int getCapacity() {
        return capacity;
    }

    void print() {
        for (int i = 0; i < currentSize; i++) {
            std::cout << arr[i] << " ";
        }
    }

private:
    T *arr;
    int capacity;
    int currentSize;

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
        capacity /= 2;
        T *newArr = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
};

#endif //MAKINGDSS_RESIZEABLEARRAY_H
