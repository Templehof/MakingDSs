#include <iostream>
#include <thread>

#include "concurrency_safe_data_structures/NaiveConcurrentResizeableArray.h"
#include "concurrency_safe_data_structures/RWConcurrentResizeableArray.h"
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
    // NaiveConcurrentResizeableArray<int> naiveConcurrentArray;
    // RWConcurrentResizeableArray<int> rwConcurrentArray;


    // array.append(10);
    // array.append(20);
    // int item = array.getValue(0);
    // std::cout<<item<<std::endl;


    return 0;
}
