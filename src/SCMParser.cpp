#include "SCMParser.h"

using namespace RPL;

SCMParser::SCMParser(int (*availableFunc)(), char (*readFunc)(),
 void (*callback)(SCMPacket)){
   this->readFunc = readFunc;
   this->availableFunc = availableFunc;
   this->callbackFunc = callback;
}

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
