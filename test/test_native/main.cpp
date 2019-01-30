#include <unity.h>

#include "common.h"
#include "max7219.h"

void run_tests()
{
    UNITY_BEGIN();

    run_tests_common();

    run_tests_max7219();

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