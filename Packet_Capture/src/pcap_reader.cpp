#include "pcap_reader.h"
#include <iostream>

using namespace PacketAnalyzer;

// Destructor
PcapReader::~PcapReader()
{
         close();
}

// ============================================================================
// Open PCAP File
// ============================================================================
bool PcapReader::open(const std::string &filename)
{
         file_.open(filename, std::ios::binary);

         if (!file_.is_open())
         {
                  std::cerr << "[ERROR] Cannot open file: " << filename << "\n";
                  return false;
         }

         // Read global header
         file_.read(reinterpret_cast<char *>(&global_header_), sizeof(global_header_));

         if (!file_)
         {
                  std::cerr << "[ERROR] Failed to read global header\n";
                  return false;
         }

         // Check endianness
         if (global_header_.magic_number == 0xd4c3b2a1)
         {
                  needs_byte_swap_ = true;
         }

         return true;
}

// ============================================================================
// Close File
// ============================================================================
void PcapReader::close()
{
         if (file_.is_open())
         {
                  file_.close();
         }
}

// ============================================================================
// Read Next Packet
// ============================================================================
bool PcapReader::readNextPacket(RawPacket &packet)
{
         if (!file_.is_open())
                  return false;

         PcapPacketHeader header;

         // Read packet header
         if (!file_.read(reinterpret_cast<char *>(&header), sizeof(header)))
         {
                  return false; // EOF
         }

         packet.header = header;

         // Allocate memory for packet data
         packet.data.resize(header.incl_len);

         // Read actual packet bytes
         if (!file_.read(reinterpret_cast<char *>(packet.data.data()), header.incl_len))
         {
                  return false;
         }

         return true;
}

// Byte swap helpers
uint16_t PcapReader::maybeSwap16(uint16_t value)
{
         return needs_byte_swap_ ? (value >> 8) | (value << 8) : value;
}

uint32_t PcapReader::maybeSwap32(uint32_t value)
{
         if (!needs_byte_swap_)
                  return value;

         return ((value >> 24) & 0xff) |
                ((value >> 8) & 0xff00) |
                ((value << 8) & 0xff0000) |
                ((value << 24) & 0xff000000);
}