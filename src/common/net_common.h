/*
 * Project: curve
 * File Created: Tuesday, 7th May 2019 11:32:51 am
 * Author: tongguangxun
 * Copyright (c)￼ 2018 netease
 */

#ifndef SRC_COMMON_NET_COMMON_H_
#define SRC_COMMON_NET_COMMON_H_

#include <stdlib.h>
#include <netinet/in.h>    // in_addr
#include <arpa/inet.h>     // inet_pton, inet_ntop
#include <glog/logging.h>
#include <string>

namespace curve {
namespace common {
class NetCommon {
 public:
    // addr形式为"ip:port"
    static bool CheckAddressValid(const std::string& addr) {
        size_t splitpos = addr.find(":");
        if (splitpos == -1) {
            LOG(ERROR) << "address invalid!";
            return false;
        }

        std::string ipstr = addr.substr(0, splitpos);
        uint32_t port = atol(addr.substr(splitpos + 1, addr.npos).c_str());

        in_addr ip;
        int rc = inet_pton(AF_INET, ipstr.c_str(), static_cast<void*>(&ip));
        if (rc <= 0) {
            LOG(ERROR) << "ip string invlid: " << ipstr.c_str();
            return false;
        }

        if (port <= 0 || port >= 65535) {
            LOG(ERROR) << "Invalid port provided: " << port;
            return false;
        }

        return true;
    }
};
}   // namespace common
}   // namespace curve

#endif  // SRC_COMMON_NET_COMMON_H_