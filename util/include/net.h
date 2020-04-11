#pragma once
#include <sys/socket.h>

namespace galois::net {

using socket_t = int;
using fd_t = int;
int listen_wrap(fd_t, int backlog);
int select_wrap(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, timeval* timeout);
int accept_wrap(fd_t, sockaddr* sa, socklen_t* addrlen);
int getpeername_wrap(fd_t, sockaddr* peeraddr, socklen_t* addrlen);
int setsockopt_wrap(fd_t, int level, int optname, const void* optval, socklen_t optlen);
int socket_wrap(int family, int type, int protocol);
int bind_wrap(fd_t, const sockaddr* myaddr, socklen_t addrlen);
int close_wrap(fd_t);

};