#include <iostream>
#include <thread>

#include "concurrency_safe_data_structures/NaiveConcurrentResizeableArray.h"
#include "simple_data_structures/resizeable_array/ResizeableArray.h"

void task1(ResizeableArray<int> &arr) {
    for (int i = 0; i < 100000; i++) {
        arr.append(i);
    }
}

void task2(ResizeableArray<int> &arr) {
    for (int i = 0; i < 100000; i++) {
        arr.append(i+100);
    }
}

void task3(NaiveConcurrentResizeableArray<int> &arr) {
    for (int i = 0; i < 10000; i++) {
        arr.append(i);
    }
}

void task4(NaiveConcurrentResizeableArray<int> &arr) {
    for (int i = 0; i < 10000; i++) {
        arr.append(i + 1);
    }
}

bool isOrdered(ResizeableArray<int> &arr) {
    for (int i = 1; i < arr.getSize() / 2; i++) {
        if (arr.getValue(i) < arr.getValue(i -1)) {
            std::cout<<"Fail at: "<<" index " << i << " " << arr.getValue(i) << " prev: " << arr.getValue(i-1) <<std::endl;
            return false;
        }
    }
    return true;
}


int main() {
    ResizeableArray<int> array;
    NaiveConcurrentResizeableArray<int> concurrentArray;
    // task1(array);
    // task2(array);
    // std::thread t1(task1, std::ref(array));
    // std::thread t2(task2, std::ref(array));

    // bool ordered = isOrdered(array);
    // std::cout<< "Ordered: " << ordered << std::endl;

    std::thread t3(task3, std::ref(concurrentArray));
    std::thread t4(task4, std::ref(concurrentArray));

    t4.join();
    t3.join();

    bool ordered = isOrdered(array);
    std::cout<< "Ordered: " << ordered << std::endl;

    return 0;
}
