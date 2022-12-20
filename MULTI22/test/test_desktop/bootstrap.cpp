#include <unity.h>

void test_add_adds_two_values(void) {
    int expected = 1 + 3;
    int actual = 4;
    TEST_ASSERT_EQUAL_INT32(expected,actual)
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_add_adds_two_values);
    UNITY_END();

    return 0;
}