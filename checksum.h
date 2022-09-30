#include <stddef.h>
#include <stdint.h>

char hex(uint8_t index);
//unsigned int crc16_ccitt(uint8_t *packet, size_t len);
//void append_checksum(uint8_t *packet, size_t *len, unsigned int crc);
uint16_t crc16_ccitt(uint8_t *packet, size_t len);
void append_checksum(uint8_t *packet, size_t *len, uint16_t crc);