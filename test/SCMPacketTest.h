#include "miniunit.h"
#include "SCMPacket.h"

namespace RPL {
  MU_TEST(empty_string_results_in_invalid_packet){
    SCMPacket packet("", 1);
    mu_check(packet.isValid() == false);
  }

  MU_TEST(valid_packet_string_reports_valid_packet){
    const char packetStr[] = "HB,12345,81;";
    SCMPacket packet(packetStr, sizeof(packetStr)-1);
    mu_check(packet.isValid() == true);
  }

  MU_TEST(invalid_checksum_in_string_returns_invalid_packet){
    const char packetStr[] = "HB,12345,82;";
    SCMPacket packet(packetStr, sizeof(packetStr)-1);
    mu_check(packet.isValid() == false);
  }

  MU_TEST_SUITE(SCM_packet_tests){
    MU_RUN_TEST(empty_string_results_in_invalid_packet);
    MU_RUN_TEST(valid_packet_string_reports_valid_packet);
    MU_RUN_TEST(invalid_checksum_in_string_returns_invalid_packet);
  }
}
