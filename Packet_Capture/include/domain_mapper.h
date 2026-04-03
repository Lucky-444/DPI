#ifndef DOMAIN_MAPPER_H
#define DOMAIN_MAPPER_H

#include <string>

namespace CaptureService
{

         class DomainMapper
         {
         public:
                  static std::string getService(const std::string &ip);
         };

}

#endif