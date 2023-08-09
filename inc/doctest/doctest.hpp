// Skip tests in bare metal ARM builds
#ifdef __ARM_EABI__
static void do_nothing() {}
#define TEST_CASE(x) static void dummy##__COUNTER__() 
#define CHECK(x) do_nothing()
#else
#include "doctest_full.hpp"
#endif // __ARM_EABI__