#include "checksum.h"

/*
 * Int to Hex
 * 
 * Parameters:
 *  - index  integer value to convert
 *
 * Returns single hex character representing integer
 */
char hex(uint8_t index)
{
  char HexTable[] = "0123456789ABCDEF";
  return HexTable[index];
}

/*
 * CRC 16 CCITT
 * 
 * Parameters:
 * - packet  Data packet
 * - len     Length of packet
 * 
 * Returns CRC-16-CCITT checksum
 */
uint16_t crc16_ccitt(uint8_t *packet, size_t len)
{
  uint16_t crc = 0xffff;           // Seed
  for (int i = 2; i < len; i++){   
      crc ^= (((unsigned int)packet[i]) << 8);
      for (uint8_t j=0; j<8; j++) {
          if (crc & 0x8000)
              crc = (crc << 1) ^ 0x1021; // xPolynomial
          else
              crc <<= 1;
      }
  }
  return crc;
}

/*
 * Append checksum to packet
 * 
 * Parameters:
 * - packet  Data packet
 * - len     Length of packet
 * - crc     CRC value to append
 * 
 * Note: This function assumes sufficient space within the packet
 */
void append_checksum(uint8_t *packet, size_t *len, uint16_t crc)
{
  packet[(*len)++] = '*';
  packet[(*len)++] = hex((crc >> 12) & 15);
  packet[(*len)++] = hex((crc >> 8) & 15);
  packet[(*len)++] = hex((crc >> 4) & 15);
  packet[(*len)++] = hex(crc & 15);
  packet[(*len)++] = '\n';
  packet[(*len)++] = '\0';
}
