#include "SCMParser.h"

using namespace RPL;

/*
 * Create a new parses with the given available function, read function
 * and callback. All three are mandatory.
 *
 * @param availableFunc function that returns how many characters can be read
 * @param readFunc function that returns the next character to be read.
 * @param callback function called when packet recieved
 */
SCMParser::SCMParser(int (*availableFunc)(), char (*readFunc)(),
 void (*callback)(SCMPacket)){
   this->readFunc = readFunc;
   this->availableFunc = availableFunc;
   this->callbackFunc = callback;
}

/*
 * Reads, if available, from the readFunction and parses result into packets.
 */
void SCMParser::read(){
  while(this->availableFunc() >= SCM_PACKET_LEN){
    char packetBuf[SCM_PACKET_LEN];
    int readCharacters;
    for(readCharacters = 0; readCharacters<SCM_PACKET_LEN; readCharacters++){
      packetBuf[readCharacters] = this->readFunc();
      if(packetBuf[readCharacters] == ';'){
        break;
      }
    }
    if(readCharacters < SCM_PACKET_LEN-1){
      continue;
    }
    SCMPacket packet(packetBuf, sizeof(packetBuf));
    this->callbackFunc(packet);
  }
}
