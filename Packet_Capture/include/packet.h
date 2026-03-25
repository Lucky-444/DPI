#include <bits/stdc++.h>

#ifndef PACKET_H
#define PACKET_H

namespace CaptureService
{
         // ============================================================================
         // Packet Structure
         // ============================================================================
         //
         // This represents a clean abstraction of a captured packet.
         // It is independent of PCAP format and can be used across services.
         //
         // timestamp  -> packet arrival time (microseconds)
         // length     -> size of packet
         // data       -> actual raw bytes of packet
         //
         // ============================================================================

         struct Packet
         {
                  uint64_t timestamp;        // timestamp in microseconds
                  uint32_t length;           // packet size
                  std::vector<uint8_t> data; // raw packet bytes
         };

}

#endif