#include <iostream>
#include "Example.h"
#include "miniunit.h"

MU_TEST(test_failing_check) {
  Example e;
  mu_check(e.printThing() == 0);
}

MU_TEST(test_passing_check) {
  Example e;
	mu_check(e.printThing() == 1);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test_passing_check);
	MU_RUN_TEST(test_failing_check);
}

int main(){
  MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return minunit_status;
}
