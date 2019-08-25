#include "miniunit.h"
#include "SCMPacket.h"
#include "TEST_HELP_MACROS.h"

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

  MU_TEST(properties_read_correctly_off_of_valid_packet){
    const char packetStr[] = "HB,12345,81;";
    SCMPacket packet(packetStr, sizeof(packetStr)-1);
    mu_assert_int_eq(packet.getId()[0], 'H');
    mu_assert_int_eq(packet.getId()[1], 'B');

    mu_assert_int_eq(packet.getData()[0], '1');
    mu_assert_int_eq(packet.getData()[1], '2');
    mu_assert_int_eq(packet.getData()[2], '3');
    mu_assert_int_eq(packet.getData()[3], '4');
    mu_assert_int_eq(packet.getData()[4], '5');
  }

  MU_TEST(reflexive_call_to_string_ctor_and_write_returns_same_string){
    const char packetStr[] = "HB,12345,81;";
    char writePacket[sizeof(packetStr)];
    ZERO_MEM(writePacket);
    SCMPacket packet(packetStr, sizeof(packetStr)-1);
    packet.write(writePacket);
    mu_check(strncmp(packetStr, writePacket, sizeof(writePacket) - 1) == 0);
  }

  MU_TEST(write_with_valid_data_generates_packet){
    const char packetStr[] = "HB,12345,81;";
    char writePacket[sizeof(packetStr)];
    ZERO_MEM(writePacket);
    SCMPacket packet("HB", "12345");
    packet.write(writePacket);
    mu_check(strncmp(packetStr, writePacket, sizeof(writePacket) - 1) == 0);
  }

  MU_TEST_SUITE(SCM_packet_tests){
    MU_RUN_TEST(empty_string_results_in_invalid_packet);
    MU_RUN_TEST(valid_packet_string_reports_valid_packet);
    MU_RUN_TEST(invalid_checksum_in_string_returns_invalid_packet);
    MU_RUN_TEST(properties_read_correctly_off_of_valid_packet);
    MU_RUN_TEST(reflexive_call_to_string_ctor_and_write_returns_same_string);
    MU_RUN_TEST(write_with_valid_data_generates_packet);
  }
}
