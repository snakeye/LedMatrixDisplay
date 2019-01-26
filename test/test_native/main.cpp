#include <unity.h>

#include "common.h"
#include "cc_sq.h"
#include "ca_sq.h"
#include "ca.h"

void run_tests()
{
    UNITY_BEGIN();

    run_tests_common();

    run_tests_cc_sq();
    run_tests_ca_sq();

    run_tests_ca();

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