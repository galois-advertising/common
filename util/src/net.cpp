#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <arpa/inet.h>  
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "net.h"
#include "log.h"

namespace galois::net {

int close_wrap(fd_t fd) {
    return close(fd);
}

int listen_wrap(fd_t sockfd, int backlog) {
    int val = listen(sockfd, backlog);
    if (val == -1) {
        FATAL("[galois_net] listen(%d,%d) call failed.error[%d] info is %s.", sockfd,
            backlog, errno, strerror(errno));
    }
    return val;
}

int setsockopt_wrap(fd_t sockfd, int level, int optname, 
    const void *optval, socklen_t optlen) {
    int val = setsockopt(sockfd, level, optname, optval, optlen);
    if (val == -1) {
        FATAL("[galois_net] setsockopt(%d,%d,%d) call failed.error[%d] info is %s.",
                    sockfd, level, optname, errno, strerror(errno));
    }
    return val;
}

int socket_wrap(int family, int type, int protocol) {
    int val = socket(family, type, protocol);
    if (val == -1) {
        FATAL("[galois_net] socket(%d,%d,%d) call failed.error[%d] info is %s.",
                    family, type, protocol, errno, strerror(errno));
    }
    return val;
}

int bind_wrap(fd_t sockfd, const sockaddr* myaddr, socklen_t addrlen) {
    int val = bind(sockfd, myaddr, addrlen);
    if (val == -1) {
        FATAL("[galois_net] bind(%d,<%d,%d,%u>,%d) call failed.error[%d] info is %s.",
            sockfd, reinterpret_cast<const sockaddr_in*>(myaddr)->sin_family,
            reinterpret_cast<const sockaddr_in*>(myaddr)->sin_port,
            reinterpret_cast<const sockaddr_in*>(myaddr)->sin_addr.s_addr, addrlen, errno,
            strerror(errno));
    }
    return val;
}


int select_wrap(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, 
    struct timeval * timeout) {
    int val;
again:
    val = select(nfds, readfds, writefds, exceptfds, timeout);
    if (val < 0) {
        if (errno == EINTR) {
            goto again;
        }
        FATAL("[galois_net] select() call error.error[%d] info is %s", errno,
                    strerror(errno));
    }
    if (val == 0) {
        errno = ETIMEDOUT;
    }
    return val;
}

int accept_wrap(fd_t sockfd, struct sockaddr *sa, socklen_t * addrlen) {
    int connfd = 0;
again:
    connfd = accept(sockfd, sa, addrlen);
    if (connfd < 0) {
#ifdef  EPROTO
        if (errno == EPROTO || errno == ECONNABORTED) {
#else
        if (errno == ECONNABORTED) {
#endif
            goto again;
        } else {
            FATAL("[galois_net] accept(%d) call failed.error[%d] info is %s.", sockfd,
                        errno, strerror(errno));
            return -1;
        }
    }
    return connfd;
}

int getpeername_wrap(fd_t sockfd, struct sockaddr *peeraddr, socklen_t * addrlen) {
    int val = getpeername(sockfd, peeraddr, addrlen);
    if (val == -1) {
        FATAL("[galois_net] getpeername(%d) call failed.error[%d] info is %s.\n",
            sockfd, errno, strerror(errno));
    }
    return val;
}
}