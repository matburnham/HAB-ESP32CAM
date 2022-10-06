#include <stdint.h>
#include <stddef.h>

#define CASIC_PREFIX {0xba,0xce}
#define CASIC_HDR 0xceba
#define CHECKSUM_SIZE 4

// CASIC Standard Interface Protocol header
struct csip_packet
{
  uint16_t header;
  uint16_t length;
  uint8_t msg_class;
  uint8_t msg_id;
  // payload
  // cehcksum
};

uint8_t* skip_header(uint8_t* data, size_t *len);
uint8_t* skip_to_next_pkt(uint8_t* data, size_t *len);
