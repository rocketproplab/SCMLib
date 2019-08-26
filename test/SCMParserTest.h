#include "miniunit.h"
#include "SCMParser.h"
#include "TEST_HELP_MACROS.h"

namespace RPL {
  namespace SCMParserTest{
    int availableRet;
    int available(){
      return availableRet;
    }

    int readCalls;
    const char * readString;
    char read(){
      char readChar = readString[readCalls];
      readCalls ++;
      availableRet --;
      return readChar;
    }

    SCMPacket lastPacket;
    int callbackCallCount;
    void sCMCallback(SCMPacket packet){
      lastPacket = packet;
      callbackCallCount ++;
    }

    MU_TEST(non_available_read_does_not_get_called){
      availableRet = 0;
      readString = "";
      readCalls = 0;
      SCMParser parser(available, read, sCMCallback);
      parser.read();
      mu_assert_int_eq(readCalls, 0);
    }

    MU_TEST(available_correct_packet_reads_correctly){
      availableRet = 12;
      readString = "HB,12345,81;";
      readCalls = 0;
      lastPacket = SCMPacket();
      SCMParser parser(available, read, sCMCallback);
      parser.read();
      mu_assert_int_eq(readCalls, 12);
      mu_assert(lastPacket.isValid(), "Packet should be valid");
      mu_assert_string_eq("HB", lastPacket.getId());
      mu_assert_string_eq("12345", lastPacket.getData());
    }

    MU_TEST(available_correct_packet_with_leading_bad_packet_reads_correctly){
      availableRet = 23;
      readString = "NOTAPACKET;HB,12345,81;";
      readCalls = 0;
      callbackCallCount = 0;
      lastPacket = SCMPacket();
      SCMParser parser(available, read, sCMCallback);
      parser.read();
      mu_assert_int_eq(readCalls, 23);
      mu_assert_int_eq(callbackCallCount, 1);
      mu_assert(lastPacket.isValid(), "Packet should be valid");
      mu_assert_string_eq("HB", lastPacket.getId());
      mu_assert_string_eq("12345", lastPacket.getData());
    }

    MU_TEST(two_consecutive_packets_are_read_at_the_same_time){
      availableRet = 24;
      readString = "HB,12345,81;HB,12345,81;";
      readCalls = 0;
      callbackCallCount = 0;
      lastPacket = SCMPacket();
      SCMParser parser(available, read, sCMCallback);
      parser.read();
      mu_assert_int_eq(readCalls, 24);
      mu_assert_int_eq(callbackCallCount, 2);
      mu_assert(lastPacket.isValid(), "Packet should be valid");
      mu_assert_string_eq("HB", lastPacket.getId());
      mu_assert_string_eq("12345", lastPacket.getData());
    }

    MU_TEST_SUITE(SCM_parser_tests){
      MU_RUN_TEST(empty_string_results_in_invalid_packet);
      MU_RUN_TEST(available_correct_packet_reads_correctly);
      MU_RUN_TEST(available_correct_packet_with_leading_bad_packet_reads_correctly);
      MU_RUN_TEST(two_consecutive_packets_are_read_at_the_same_time);
    }
  }
}
