#include "domain_mapper.h"

namespace CaptureService
{

         std::string DomainMapper::getService(const std::string &ip)
         {
                  if (ip.find("142.250") == 0)
                           return "Google";

                  if (ip.find("157.240") == 0)
                           return "Meta (Facebook/Instagram)";

                  if (ip == "8.8.8.8")
                           return "DNS (Google DNS)";

                  if (ip.find("104.16") == 0)
                           return "Cloudflare";

                  return "Unknown";
         }

}