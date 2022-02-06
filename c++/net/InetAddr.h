#ifndef _NET_INETADDR_
#define _NET_INETADDR_
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace net {
const struct sockaddr* sockaddr_cast(const struct sockaddr_in6* addr);

class InetAddr {
 public:
  explicit InetAddr(u_int16_t port = 0, bool loopbackOnly = false,
                    bool ipv6 = false);
};

}  // namespace net

#endif
