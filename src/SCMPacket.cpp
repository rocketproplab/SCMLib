#include "SCMPacket.h"

using namespace RPL;

SCMPacket::SCMPacket(const char * stringRep, int len){
  this->valid = this->validate(stringRep, len);
  if(this->valid){
    this->checksum = this->calculateChecksum(stringRep);
  }
}

bool SCMPacket::isValid(){
  return this->valid;
}

bool SCMPacket::validate(const char * stringRep, int len){
  return len == SCM_PACKET_LEN;
}

/*
 * Function: calculateChecksum
 * ---------------------------
 * adds the ASCII values of the package characters(except the checksum) together and
 * takes modulo 100. If the checksum sent differs to the one calculated, the package
 * is corrupted and needs to be sent again
 *
 * package: the package to check, assumed to be at least 12 chars long
 *
 * returns: the calculated checksum
 */
int SCMPacket::calculateChecksum(const char * packet) {
  int addedASCII = 0;

  //loop through the package, but leave out the checksum for calculating the checksum
  for (int i = 0; i < SCM_PACKET_LEN; i++) {
    addedASCII += (int)packet[i];
  }

  //take modulo to calculated checksum
  int calculatedChecksum = addedASCII % 100;
  return calculatedChecksum;
}
