#ifndef _UNICAST_SERVER_
#define _UNICAST_SERVER_

int tcp_ser(int port, int sockfd);

void error(const char *msg);
void cur_time();


#endif
