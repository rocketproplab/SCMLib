#include "miniunit.h"

namespace RPL {
  MU_TEST(empty_string_results_in_invalid_packet){

  }

  MU_TEST_SUITE(SCM_packet_tests){
    MU_RUN_TEST(empty_string_results_in_invalid_packet);
  }
}
