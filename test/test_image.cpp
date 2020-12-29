//#include "Arduino.h"
#include "unity.h"
#include "MyTools.h"
#include <iostream>
#include <string>
#include <numeric>
#include <iterator>
#include <cstdint>

void test_reverse_image(){

    const int bufferSize = 15;
    uint8_t testBuffer[bufferSize] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    uint8_t destBuffer[bufferSize] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    tools::flipBufferVertical(testBuffer, destBuffer, 3, 5, 8);

    printf("\n");
    printf("%d \n\n", sizeof(testBuffer) / sizeof(testBuffer[0]));
    for(int i = 0; i < bufferSize; i++){
        printf("%hhu ", testBuffer[i]);
    }
    printf("\n");
    for(int i = 0; i < bufferSize; i++){
        printf("%hhu ", destBuffer[i]);
    }
    printf("\n\n");

    TEST_ASSERT_EQUAL(testBuffer[0], destBuffer[10]);
    TEST_ASSERT_EQUAL(testBuffer[14], destBuffer[4]);
}

void test_row_size(){
    int testRowSize = tools::getRowSizeBytes(4, 480);
    int testRowSize2 = tools::getRowSizeBytes(8, 5);

    TEST_ASSERT_EQUAL(testRowSize, 240);
    TEST_ASSERT_EQUAL(testRowSize2, 5);
}


int main(){
    UNITY_BEGIN();

    RUN_TEST(test_reverse_image);
    RUN_TEST(test_row_size);


    UNITY_END();
}