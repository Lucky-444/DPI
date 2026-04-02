#include <iostream>
#include <iomanip>
#include "capture_engine.h"
#include "packet_parser.h"

using namespace CaptureService;

// ============================================================================
// Main Function - Entry Point
// ============================================================================
int main()
{
         std::string filename = "data/test.pcap";

         CaptureEngine engine;

         // Initialize engine
         if (!engine.init(filename))
         {
                  return 1;
         }

         Packet pkt;
         int count = 0;

         std::cout << "\n📦 Reading Packets...\n\n";

         // Read packets one by one
         while (engine.getNextPacket(pkt))
         {
                  count++;

                  std::cout << "Packet #" << count << "\n";
                  std::cout << "Timestamp: " << pkt.timestamp << "\n";
                  std::cout << "Length: " << pkt.length << " bytes\n";

                  // Print first 16 bytes
                  std::cout << "Data (first 16 bytes): ";
                  for (size_t i = 0; i < std::min((size_t)16, pkt.data.size()); i++)
                  {
                           std::cout << std::hex << std::setw(2) << std::setfill('0')
                                     << (int)pkt.data[i] << " ";
                  }
                  std::cout << std::dec << "\n";

                  std::cout << "-----------------------------\n";

                  PacketParser::parse(pkt);
         }

         std::cout << "\n✅ Total Packets Read: " << count << "\n";

         engine.close();
         return 0;
}