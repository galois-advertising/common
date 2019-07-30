int _accept(int sockfd, struct sockaddr *sa, socklen_t * addrlen)
{
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
            ul_writelog(UL_LOG_WARNING, "accept(%d) call failed.error[%d] info is %s.", sockfd,
                        errno, strerror(errno));
            return -1;
        }
    }

    if (ul_ipaccess_grant == NULL || ul_ipaccess_grant[0] == 0) {
        return (connfd);
    }

    struct sockaddr_in peeraddr;
    struct sockaddr_in localaddr;
    socklen_t adrlen = sizeof(struct sockaddr_in);

    char ip_net[INET_ADDRSTRLEN];
    memset(ip_net, 0, INET_ADDRSTRLEN);

    int peer = 0;
    peer = ul_getpeername(connfd, (struct sockaddr *) &peeraddr, &adrlen);
    if (peer < 0) {
        close(connfd);
        return -1;
    }

    adrlen = sizeof(struct sockaddr_in);
    ul_getsockname(connfd, (struct sockaddr *) &localaddr, &adrlen);

    struct in_addr in_val;
    in_val.s_addr = peeraddr.sin_addr.s_addr;
    inet_ntop(AF_INET, &in_val, ip_net, INET_ADDRSTRLEN);

    if (ip_net[0] != 0) {
        if (is_ip_allowed(ip_net, ul_ipaccess_grant) == 0) {
            goto close_connect;
        }
    } else {
        goto close_connect;
    }

    return (connfd);

  close_connect:
    close(connfd);
    ul_writelog(UL_LOG_WARNING,
                "When server listened on port %d a client from ip %s try to connect.",
                ntohs(localaddr.sin_port), ip_net);
    return -1;

}
