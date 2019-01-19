#include "unity.h"
#include "SPI_FUNCTIONS_TEST.h"

void setUp(void){}

void tearDown(void){}

void test_compareSpiCommand_compare_write_and_write_expect_5(void)
{
    TEST_ASSERT_EQUAL(5, compareSpiCommand("write", "write"));
}

void test_compareSpiCommand_compare_minus_write_and_write_expect_5(void)
{
    TEST_ASSERT_EQUAL(-1, compareSpiCommand("-write", "write"));
}
void test_compareSpiCommand_compare_space_write_and_write_expect_8(void)
{
    TEST_ASSERT_EQUAL(6, compareSpiCommand(" write", "write"));
}

void test_compareSpiCommand_compare_10_space_write_and_write_expect_8(void)
{
    TEST_ASSERT_EQUAL(15, compareSpiCommand("          write", "write"));
}

void test_compareSpiCommand_compare_space_space_write_and_write_expect_6(void)
{
    TEST_ASSERT_EQUAL(-1, compareSpiCommand("   wrote", "write"));
}

void test_compareSpiCommand_compare_write_space_and_write_expect_5(void)
{
    TEST_ASSERT_EQUAL(5, compareSpiCommand("write ", "write"));
}

void test_compareSpiCommand_compare_write_10_space_and_write_expect_5(void)
{
    TEST_ASSERT_EQUAL(5, compareSpiCommand("write          ", "write"));
}

void test_numberInString_12_25_expect_saved_in_buffer(void){
  numbersInString("12 25", 16);
  TEST_ASSERT_EQUAL(18, buffer[0]);
  TEST_ASSERT_EQUAL(37, buffer[1]);
}
