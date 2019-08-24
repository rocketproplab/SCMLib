
namespace RPL{
  const int SCM_PACKET_LEN = 12;
  class SCMPacket {
  public:
    SCMPacket(const char * stringRep, int len);

    bool isValid();

  private:
    bool validate(const char * stringRep, int len);
    int calculateChecksum(const char * packet);
    bool valid;
    int checksum;
  };
}
