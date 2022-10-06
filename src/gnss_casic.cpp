#include "gnss_casic.h"
#include "gnss_casic_util.h"

#include "serialdebug.h"
#include "sdcard.h"
#include <stdlib.h>
#include <Base64.h>


#define CASIC_FILE "/casic.base64"
#define AGPS_BUFFER_SIZE 4096     // Maximum expected size of AGPS data

/* Load CASIC cold-start ephemeris/AGPSS* data from the SD card.
 * 
 * Note: one needs to manually grab recent data from
 * https://www.espruino.com/agps/casic.base64 and place it on the SD card prior
 * to flight. I'm sure how long the data will last, it could be 1 day, it could
 * be 3 days.
 * 
 * Note: this is for CASIC devices (e.g. ATGM336H) only
 */
void gnss_load_eph()
{
  // I'm not convinced this is 'AGPS', rather it is ephemeris data?
  
  // Code based upon https://github.com/espruino/BangleApps/blob/master/apps/assistedgps/custom.html
  
  TRACE("gnss_load_eph");
  
  // TODO: this wpould be more testable if broken up
  // b64data <- SD
  // data <- b64
  // packet <- data ***** this is testable if pulled out into a function
  // send
  // ACK

  size_t b64len = 0;
  char* b64data = (char *)malloc(AGPS_BUFFER_SIZE);
  uint8_t* data = (uint8_t *)malloc(AGPS_BUFFER_SIZE);

  // Read data from SD card / casic.base64 file
  if(b64len = readFile(CASIC_FILE, b64data, AGPS_BUFFER_SIZE)) {

    // Decode base64 to raw binary
    size_t len = Base64.decodedLength(b64data, b64len);
    Base64.decode((char *) data, b64data, b64len);
    //TRACE(len);
    free(b64data);

    skip_header(data, &len);

    uint8_t* pos = data;

    int i = 0;
    while(len) {
      struct csip_packet* pkt = (struct csip_packet*) pos;
      if(pkt->header != CASIC_HDR) {
        TRACEF("Invalid header %x", pkt->header);
        break;
      }

      TRACEF("Packet %x %p %x", i, pkt);

      // TODO: send packet to GNSS
      // TODO: wait for ACK

      pos = skip_to_next_pkt(pos, &len);
      i++;
    }

    /*while(pkt) {
      if(pkt->header != CASIC_HDR) {
        TRACE("Invalid header" + pkt->header);
        break;
      }
      int pktlen = pkt->length + 4; // including checksum

      TRACEF("Packet %x %p %x", i, pkt, pktlen);

      pos += pkt->length;
      len -= pktlen;

      i++;
    }*/
  } else {
    TRACE("Failed to open CASIC file");
  }

  free(data);
}

/* INFO

Read up on power saving from https://forum.espruino.com/conversations/371360/?offset=50
Suggestion GGA only? "$PCAS03,1,0,0,0,0,0,0,0,0,0,0,0*..."



https://docs.google.com/document/d/e/2PACX-1vQaEH6gbVeQds5AOQ7c2dJoNef1o6vCL4SeDRDB9YNtRzI1MKUYzDqS9clEdwL_RdI9TpjErreM-wiM/pub

https://github.com/geary/AnyTone-D868UV/issues/61

https://members.optuszoo.com.au/jason.reilly1/868mods.htm#FasterGPS
http://members.optuszoo.com.au/jason.reilly1/868mods.htm?fbclid=IwAR3We8hIt20lFBOhBdOoGneDnTRfB2PTQAMff1Tsupw06QlFLPlOnOnBRLE#FasterGPS

*/

//https://espruino.microco.sm/api/v1/files/68b597874e0a617692ebebc6a878032f76b34272.pdf