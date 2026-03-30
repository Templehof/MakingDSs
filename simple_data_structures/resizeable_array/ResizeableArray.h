//
// Created by Ivan Riumkin on 2026-03-29.
//

#ifndef MAKINGDSS_RESIZEABLEARRAY_H
#define MAKINGDSS_RESIZEABLEARRAY_H
#include <iostream>
#include <stdexcept>

/*
 * Resizeable array
 *
 * What to think about when designing one:
 * - Resizing policy to achieve reasonable memory and time efficiency.
 * - Typically:
 * -- Insertions must achieve amortized O(1) efficiency.
 * -- Memory: Must achieve a balance on the frequency of resizing and unused space size.
 */
template<typename T>
class ResizeableArray {
public:
    ResizeableArray() {
        // a small initial allocation to avoid allocating on the first insert
        arr = new T[16];
        capacity = 16;
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
        // Possible optimization: move instead of copy
        arr[currentSize] = item;
        currentSize++;
    }

    void addAtIndex(T item, int index) {

        if (index < 0 || index >= capacity || index >= currentSize) {
            throw std::out_of_range("index out of range");
        }

        if (currentSize == capacity) {
            resizeUp();
        }

        arr[index] = item;
        currentSize++;
    }

    T pop() {
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
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("index out of range");
        }
        return arr[index];
    }

    size_t getSize() {
        return currentSize;
    }

    size_t getCapacity() {
        return capacity;
    }

    void print() {
        for (int i = 0; i < currentSize; i++) {
            std::cout << arr[i] << " ";
        }
    }

private:
    T *arr;
    size_t capacity;
    size_t currentSize;

    // Double the size - Achieves amortized O(1) - Total number of resizes: Θ(log_φ n).
    void resizeUp() {
        capacity *= 2;

        T *newArr = new T[capacity];

        // Possible optimization: move instead of copy
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

#endif //MAKINGDSS_RESIZEABLEARRAY_H
