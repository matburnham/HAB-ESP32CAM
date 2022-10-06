#define _GNU_SOURCE // required for memmem
#include <string.h>

#include "gnss_casic_util.h"

static uint8_t marker[] = CASIC_PREFIX;

/* Skip text header (find first CASIC 0xbace instruction)
 *
 * Parameters:
 *  - data - pointer to data
 *  - *len - length of buffer, will be updated with new remaining length
 * 
 * Returns pointer to first CASIC packet
 */
uint8_t* skip_header(uint8_t* data, size_t *len) {
    uint8_t* pos = (uint8_t*) memmem(data, *len, marker, sizeof(marker));
    (*len) -= pos-data;
    return pos;
}

/* Skip to next packet based on the length of the current one
 *
 * Parameters:
 *  - data - pointer to data, which should begin with a valid packet
 *  - *len - length of buffer, will be updated with new remaining length
 * 
 * Returns poninter to next CASIC packet
 */
uint8_t* skip_to_next_pkt(uint8_t* data, size_t *len) {
  struct csip_packet* pkt = (struct csip_packet*) data;
  int pktlen = sizeof(struct csip_packet) + pkt->length + CHECKSUM_SIZE;
  data += pktlen;
  (*len) -= pktlen;
  return data;
}