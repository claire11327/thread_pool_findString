    #include <time.h>
    #include <netdb.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <signal.h> 
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>
    #include <sys/stat.h>
    #include <arpa/inet.h>
    #include <sys/errno.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>

    #include "thpool.h"
    #include "find_str.h"
    #include "unicast_server.h"
     
    #define SERV_PORT 5134
     
    #define MAXNAME 1024
    #define BUFSIZE 10
    #define SERV_PORT 5134
    #define MAXDATA   1024

     
    extern int errno;
    
    void error(const char *msg)
    { 
        perror(msg);
        exit(1);
    }
    //get current time 
    void cur_time ()
    {
      time_t rawtime;
      struct tm * timeinfo;
     
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      printf ( "%s\n", asctime (timeinfo) );
     
    }
    
int tcp_ser(int port, int newsockfd)//, char *buffer)
{
     int sockfd, portno,numbytes;
//     int newsockfd;
     socklen_t clilen;
     int total_send = 0;                      /* count now sent data */
//     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     struct stat filestat;		      /* file statw */
     FILE *fp;				      /* file pointer */	

     //TCP socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");


     //Initial,bind to port
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = port;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     
     
     //binding
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");


     //start listening
     listen(sockfd,5);


     //Connect  
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,&clilen);
     printf("fd = %d\n",newsockfd);
     if (newsockfd < 0)
          error("ERROR on accept");
     return newsockfd;




}

