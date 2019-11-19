    #include <time.h>
    #include <netdb.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <signal.h> 
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <arpa/inet.h>
    #include <sys/errno.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    
    #include "unicast_client.h"
 
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
  
//tcp client
void tcp_cli(char* ip,int  port, int sockfd){
     int  newsockfd;

    //int sockfd;
    int portno, n,numbytes;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //char buffer[256];
    portno = port;

    //TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(ip);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }


    //Initial connect to port
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);



    //connect to server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");


    return sockfd;

   // printf("Please enter the message: ");


    //Receive msg from server
    /*while(1){
	    //fgets(buffer,sizeof(buffer)-1, stdin);
	    printf("input msg:");
	    fgets(buffer, sizeof(buffer)-1, stdin);
	    printf("input msg is = %s\n",buffer);
            numbytes = write(sockfd, buffer, sizeof(buffer));
	    memset(buffer,0,strlen(buffer)+1);
	    printf("read msg = %s\n",buffer);
            if(strlen(buffer)!=0){
            	    numbytes = read(sockfd, buffer, sizeof(buffer));
		    printf("result msg = %s\n",buffer);
		    memset(buffer,0,strlen(buffer)+1);
		    //break;
	    }
    }
    close(sockfd);
    close(newsockfd);*/
}

