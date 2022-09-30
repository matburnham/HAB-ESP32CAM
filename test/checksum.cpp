#include <Arduino.h>
#include <ArduinoUnitTests.h>
#include "checksum.h"

unittest(hex)
{
    assertEqual(hex(9), '9');
    assertEqual(hex(11), 'B');
}

unittest(crc16_ccitt)
{
  // unsigned int crc16_ccitt(uint8_t *packet, size_t len)

  // Test vectors from https://stackoverflow.com/questions/1918090/crc-test-vectors-for-crc16-ccitt
  unsigned char const std_data[] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };
  assertEqual(0x29b1, crc16_ccitt((uint8_t*) std_data, sizeof(std_data) / sizeof(std_data[0])));

  char packet1[] = "123456789";
  assertEqual(0x29b1, crc16_ccitt((uint8_t*) packet1, strlen(packet1)));

  char packet2[] = "12345670";
  assertEqual(0xB1E4, crc16_ccitt((uint8_t*) packet2, strlen(packet2)));

  char packet3[] = "5A261977";
  assertEqual(0x1AAD, crc16_ccitt((uint8_t*) packet3, strlen(packet3)));
}

unittest(append_checksum)
{
  char packet[20] = "123456789";
  char expected[] = "123456789*ABCD\n";
  size_t len = strlen(packet);

  append_checksum((uint8_t*) packet, &len, 0xABCD);

  assertEqual(expected, packet);
  assertEqual(strlen(expected)+1, len);
}

unittest_main()
