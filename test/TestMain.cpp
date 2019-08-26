#include "miniunit.h"
#include "SCMPacketTest.h"
#include "SCMParserTest.h"

using namespace RPL;

int main(){
  MU_RUN_SUITE(SCM_packet_tests);
  MU_RUN_SUITE(SCMParserTest::SCM_parser_tests);
	MU_REPORT();
	return minunit_status;
}
