#include <unity.h>
#include <stdint.h>
#include <stddef.h>

#include "gnss_casic_util.h"

#include "casic_sample_def.c"

//void setUp(void) {}
//void tearDown(void) {}

void test_skip_header_should_return_first_packet()
{
  size_t len = sizeof(casic_sample);
  TEST_ASSERT_EQUAL_UINT16(casic_sample_len, len);
  uint8_t *first_packet = skip_header(casic_sample, &len);
  TEST_ASSERT_EQUAL_HEX8(0xba, first_packet[0]);
  TEST_ASSERT_EQUAL_HEX8(0xce, first_packet[1]);
  TEST_ASSERT_EQUAL_UINT16(2598, len);

  struct csip_packet* pkt = (struct csip_packet*) first_packet;
  TEST_ASSERT_EQUAL_HEX16(CASIC_HDR, pkt->header);
}

void test_skip_to_next_pkt_should_return_next_packet()
{
  size_t len = sizeof(casic_sample);
  uint8_t *first_packet = skip_header(casic_sample, &len);
  uint8_t *next_packet = skip_to_next_pkt(first_packet, &len);
  TEST_ASSERT_EQUAL_HEX8(0xba, next_packet[0]);
  TEST_ASSERT_EQUAL_HEX8(0xce, next_packet[1]);
  //TEST_ASSERT_NOT_EQUAL_PTR(first_packet,next_packet);
  TEST_ASSERT_EQUAL_UINT16(2516, len);
}

void test_skip_to_next_pkt_should_iterate_all_packets()
{
  size_t len = sizeof(casic_sample);
  uint8_t *pkt = skip_header(casic_sample, &len);
  size_t i = 0;
  while(len) {
    i++;
    //TEST_MESSAGE((char*)pkt);
    //printf("%d, %d %02x%02x%02x%02x\n", (int) i, (int) len, pkt[0],pkt[1],pkt[2],pkt[3]);
    pkt = skip_to_next_pkt(pkt, &len);
  }
  TEST_ASSERT_EQUAL_UINT16(33, i);
}

/*int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_skip_header_should_return_first_packet);
  RUN_TEST(test_skip_to_next_pkt_should_return_next_packet);
  RUN_TEST(test_skip_to_next_pkt_should_iterate_all_packets);
  return UNITY_END();
}*/