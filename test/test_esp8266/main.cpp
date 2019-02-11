#include <unity.h>

void run_tests()
{
    UNITY_BEGIN();

    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>

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