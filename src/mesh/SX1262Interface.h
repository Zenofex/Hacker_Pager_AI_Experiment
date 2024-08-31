#if RADIOLIB_EXCLUDE_SX126X != 1
#pragma once

#include "SX126xInterface.h"
#ifdef EXPLOITEERS_PAGER
#include "modules/exploiteers_pager/packetcapture/packet_capture.h"
#endif

/**
 * Our adapter for SX1262 radios
 */
class SX1262Interface : public SX126xInterface<SX1262>
{
#ifdef EXPLOITEERS_PAGER
    // For accessing the radio, bypassing Meshtastic.
    friend class pager::PacketCapture;
#endif

  public:
    SX1262Interface(LockingArduinoHal *hal, RADIOLIB_PIN_TYPE cs, RADIOLIB_PIN_TYPE irq, RADIOLIB_PIN_TYPE rst,
                    RADIOLIB_PIN_TYPE busy);
};
#endif