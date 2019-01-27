#include <unity.h>

#include "common.h"

void run_tests()
{
    UNITY_BEGIN();

    run_tests_common();

    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    run_tests();
}

void loop()
{
}

#else

int main(int argc, char **argv)
{
    run_tests();
    return 0;
}

#endif