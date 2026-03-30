//
// Created by Ivan Riumkin on 2026-03-30.
//

#include <gtest/gtest.h>

#include "../simple_data_structures/resizeable_array/ResizeableArray.h"

TEST(ResizeableArrayTest, ResizeIncreasesTheCapacityOfTheArray) {
    ResizeableArray<int> array;
    size_t initialCapacity = array.getCapacity();
    for (int i = 0; i < 12; i++) {
        array.append(i);
    }

    ASSERT_EQ(array.getCapacity() > initialCapacity, true);
}

TEST(ResizeableArrayTest, ResizeDecreasesTheCapacityOfTheArray) {
    ResizeableArray<int> array;
    size_t initialCapacity = array.getCapacity();

    for (int i = 0; i < 100; i++) {
        array.append(i);
    }

    ASSERT_EQ(array.getCapacity() > initialCapacity, true);

    for (int i = 100; i > 4; i--) {
        array.pop();
    }

    ASSERT_EQ(array.getCapacity() == initialCapacity, true);
}

TEST(ResizeableArrayTest, TheOrderOfElementsPreserved) {
    ResizeableArray<int> array;

    for (int i = 0; i < 12; i++) {
        array.append(i);
    }

    for (int i = 0; i < array.getSize(); i++) {
        ASSERT_EQ(array.getValue(i), i);
    }
}

TEST(ResizeableArrayTest, AccessingIndexesOutOfBoundsThrows) {
    ResizeableArray<int> array;

    ASSERT_ANY_THROW(array.getValue(-1));
    ASSERT_ANY_THROW(array.getValue(1));
}
