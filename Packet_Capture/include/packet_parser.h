#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <cstdint>
#include <string>
#include <array>
#include "pcap_reader.h"
#include <packet.h>

namespace CaptureService
{

    struct EthernetHeader
    {
        uint8_t dest[6];
        uint8_t src[6];
        uint16_t type;
    };

    struct IPv4Header
    {
        uint8_t version_ihl;
        uint8_t tos;
        uint16_t total_length;
        uint16_t id;
        uint16_t flags_fragment;
        uint8_t ttl;
        uint8_t protocol;
        uint16_t checksum;
        uint32_t src_ip;
        uint32_t dst_ip;
    };

    struct TCPHeader
    {
        uint16_t src_port;
        uint16_t dst_port;
    };

    struct UDPHeader
    {
        uint16_t src_port;
        uint16_t dst_port;
    };
    struct ParsedPacket
    {
        bool has_ip = false;

        std::string src_ip;
        std::string dest_ip;

        uint16_t src_port = 0;
        uint16_t dest_port = 0;

        std::string protocol;
    };

    class PacketParser
    {
    public:
    static void parse(const Packet &pkt);
    static bool parsed(const Packet &pkt, ParsedPacket &out);
    };

}

#endif