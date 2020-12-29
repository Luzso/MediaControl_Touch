//#include "Arduino.h"
#include "unity.h"
#include "MyTools.h"
#include <iostream>
#include <string>
#include <numeric>
#include <iterator>
#include <cstdint>

void test_row_size(){
    int testRowSize = tools::getRowSizeBytes(4, 480);
    int testRowSize2 = tools::getRowSizeBytes(8, 5);

    TEST_ASSERT_EQUAL(testRowSize, 240);
    TEST_ASSERT_EQUAL(testRowSize2, 5);
}


int main(){
    UNITY_BEGIN();

    RUN_TEST(test_row_size);


    UNITY_END();
}