#include "capture_engine.h"
#include <iostream>

using namespace CaptureService;

// ============================================================================
// Initialize Capture Engine
// ============================================================================
bool CaptureEngine::init(const std::string &filename)
{
         if (!reader_.open(filename))
         {
                  std::cerr << "[ERROR] Failed to open PCAP file: " << filename << "\n";
                  return false;
         }

         std::cout << "[INFO] PCAP file opened: " << filename << "\n";
         return true;
}

// ============================================================================
// Read Next Packet
// ============================================================================
bool CaptureEngine::getNextPacket(Packet &pkt)
{
         PacketAnalyzer::RawPacket raw;

         // Read raw packet from file
         if (!reader_.readNextPacket(raw))
         {
                  return false; // no more packets
         }

         // Convert RawPacket → Packet
         pkt.timestamp = (uint64_t)raw.header.ts_sec * 1000000ULL + raw.header.ts_usec;
         pkt.length = raw.header.incl_len;
         pkt.data = raw.data;

         return true;
}

// ============================================================================
// Close Reader
// ============================================================================
void CaptureEngine::close()
{
         reader_.close();
}