#ifndef SCM_PACKET_H
#define SCM_PACKET_H

namespace RPL{
  const int SCM_PACKET_LEN = 12;
  const int SCM_CHECKSUMABBLE_PACKET_LEN = SCM_PACKET_LEN-3;
  const int SCM_PACKET_DATA_START = 3;
  const int SCM_PACKET_DATA_END = 7;
  const int SCM_PACKET_CHECKSUM_START = 9;
  class SCMPacket {
  public:
    SCMPacket(const char * stringRep, int len);
    SCMPacket(const char * id, const char * data);
    SCMPacket();

    bool isValid();
    void write(char * buffer);
    const char * getId();
    const char * getData();

  private:
    int calculateChecksum(const char * packet);
    void readData(const char * stringRep);
    bool valid;
    int checksum;
    char id[3];
    char data[SCM_PACKET_DATA_END-SCM_PACKET_DATA_START+2];
  };
}

#endif
