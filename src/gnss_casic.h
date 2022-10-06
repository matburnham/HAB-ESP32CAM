#include <stdint.h>

void gnss_load_eph();

// Internal - needed to expose for unit testing
uint8_t* skip_header(uint8_t* data, int *len);
uint8_t* skip_to_next_pkt(uint8_t* data, int *len);