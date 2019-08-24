#include "miniunit.h"
#include "SCMPacketTest.h"

using namespace RPL;

int main(){
  MU_RUN_SUITE(SCM_packet_tests);
	MU_REPORT();
	return minunit_status;
}
