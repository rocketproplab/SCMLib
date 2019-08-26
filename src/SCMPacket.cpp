#include "SCMPacket.h"

using namespace RPL;

/*
 * Creates empty invalid packet.
 */
SCMPacket::SCMPacket(){
  this->valid = false;
}

/*
 * Create a new SCM packet from the given string of length len.
 * This will make sure the string is of the right length and has the right
 * checksum.
 *
 * @param stringRep the string reperesentation of the packet. Ie "HB,12345,81;"
 * @param len the length of the string red
 */
SCMPacket::SCMPacket(const char * stringRep, int len){
  this->valid = len == SCM_PACKET_LEN;
  if(this->valid){
    int checksum = this->calculateChecksum(stringRep);
    this->readData(stringRep);
    this->valid = this->checksum == checksum;
  }
}

/*
 * Create a packet with the given ID and Data.
 *
 * @param id the ID string to create the packet with. (length 2)
 * @param data the data string to use (length 5)
 */
SCMPacket::SCMPacket(const char * id, const char * data){
  this->valid = true;
  this->id[0] = id[0];
  this->id[1] = id[1];
  for(int i = 0; i<=(SCM_PACKET_DATA_END-SCM_PACKET_DATA_START); i++){
    this->data[i] = data[i];
  }
}

/*
 * Determins if the packet is valid
 * @return if the packet is valid
 */
bool SCMPacket::isValid(){
  return this->valid;
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
  for (int i = 0; i < SCM_CHECKSUMABBLE_PACKET_LEN; i++) {
    addedASCII += (int)packet[i];
  }

  //take modulo to calculated checksum
  int calculatedChecksum = addedASCII % 100;
  return calculatedChecksum;
}

/*
 * Reads the data from a given string representation of the packet.
 * @param packet the packet to read the data from (len 12)
 */
void SCMPacket::readData(const char * packet){
  this->id[0] = packet[0];
  this->id[1] = packet[1];
  this->id[2] = '\0';
  for(int i = SCM_PACKET_DATA_START, k = 0; i<=SCM_PACKET_DATA_END; i++, k++){
    this->data[k] = packet[i];
  }
  this->data[sizeof(this->data)-1] = '\0';
  this->checksum = packet[SCM_PACKET_CHECKSUM_START] - '0';
  this->checksum *= 10;
  this->checksum += packet[SCM_PACKET_CHECKSUM_START + 1] - '0';
}

/*
 * Returns the internal data string.
 * @return the internal data string.
 */
const char * SCMPacket::getData(){
  return this->data;
}

/*
 * @return the internal ID String.
 * Returns the internal ID String.
 */
const char * SCMPacket::getId(){
  return this->id;
}

/*
 * Writes the packet to the supplied buffer which must be of length 12 or
 * longer.
 *
 * @param bufToWriteTo the buffer that is to be written to.
 */
void SCMPacket::write(char * bufToWriteTo){
  bufToWriteTo[0] = this->id[0];
  bufToWriteTo[1] = this->id[1];
  bufToWriteTo[2] = ',';

  for(int i = SCM_PACKET_DATA_START, k = 0; i<=SCM_PACKET_DATA_END; i++, k++){
     bufToWriteTo[i] = this->data[k];
  }
  bufToWriteTo[SCM_PACKET_DATA_END+1] = ',';

  int checksum = this->calculateChecksum(bufToWriteTo);
  bufToWriteTo[SCM_PACKET_CHECKSUM_START+1] = (checksum % 10) + '0';
  checksum /= 10;
  bufToWriteTo[SCM_PACKET_CHECKSUM_START] = (checksum % 10) + '0';
  bufToWriteTo[SCM_PACKET_CHECKSUM_START+2] = ';';
}
