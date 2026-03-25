#ifndef CAPTURE_ENGINE_H
#define CAPTURE_ENGINE_H

#include "packet.h"
#include "pcap_reader.h"
#include <string>

namespace CaptureService
{
         // ============================================================================
         // CaptureEngine
         // ============================================================================
         //
         // This class acts as a wrapper over PcapReader.
         // It converts low-level RawPacket → high-level Packet.
         //
         // Responsibilities:
         // - Open PCAP file
         // - Read packets one by one
         // - Convert into service-level Packet struct
         //
         // ============================================================================

         class CaptureEngine
         {
         public:
                  // Initialize capture engine with file
                  bool init(const std::string &filename);

                  // Get next packet
                  bool getNextPacket(Packet &pkt);

                  // Close file
                  void close();

         private:
                  PacketAnalyzer::PcapReader reader_; // low-level reader
         };

}

#endif