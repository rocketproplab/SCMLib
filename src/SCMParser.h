#ifndef SCM_PARSER_H
#define SCM_PARSER_H
#include "SCMPacket.h"

namespace RPL{
  class SCMParser {
  public:
    SCMParser(int (*available)(), char (*read)(), void (*callback)(SCMPacket));
    void read();

  private:
    int (*availableFunc)();
    char (*readFunc)();
    void (*callbackFunc)(SCMPacket);
  };
}

#endif
