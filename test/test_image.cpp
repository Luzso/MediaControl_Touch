//#include "Arduino.h"
#include "unity.h"
#include "MyTools.h"

void test_reverse_image(){
    int testNum = tools::returnOne();

    TEST_ASSERT_EQUAL(testNum, 1);
}


void test_test2(){
    
    int testNum = tools::returnOne();
    TEST_ASSERT_EQUAL(testNum, 2);
}


int main(){
    UNITY_BEGIN();

    RUN_TEST(test_reverse_image);
    RUN_TEST(test_test2);


    UNITY_END();
}