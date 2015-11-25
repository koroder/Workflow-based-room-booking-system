#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>


#define DEFAULT_INTERVAL 5
#define DEFAULT_LOGFLAG 0
#define CLOCK 300
#define OFFICE_START 8
#define OFFICE_CLOSE 17

time_t time_start;
time_t time_present;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void dostuff (int sock)
{
   int n,finder,after_time=0;
   char buffer[50],temp[256]={"-"},finder1[50]={" "},c,off_start[3],off_end[3];
   
   
   time_t elapsed;
   
   time_present=time(NULL);
   elapsed=time_present-time_start;
   
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);
   //dependeing on buffer call function either to make a booking or cancel or check status 
   printf("strlen=%d\n",strlen(buffer));
   if(strlen(buffer) == 46)
   {
   	printf("call the booking function\n");
   	
   	off_start[0]=buffer[14];off_start[1]=buffer[15];off_start[2]='\0';
   	off_end[0]=buffer[18];off_end[1]=buffer[19];off_end[2]='\0';
   	
   	if((atoi(off_start) < OFFICE_START) || (atoi(off_end) > OFFICE_CLOSE) || (atoi(off_end) >= OFFICE_CLOSE && buffer[20]!='0'))
   		after_time=1;
   	if(after_time)	finder = -1;
   	else
   	{
   		processing(1,buffer,finder1);printf("finder1=%s\n",finder1);
   		finder = atoi(finder1);
   		printf("userid=%d\n",finder);
   	}
   	if(finder < 0)
   	{
   		buffer[0]='h';
   		buffer[1]='\0';
   	}
   	else
   		sprintf(buffer, "%d", finder);
   	printf("!!buffer=%s\n",buffer);n = write(sock,buffer,strlen(buffer));
   	if (n < 0) error("ERROR writing to socket");
   }
   else if(buffer[strlen(buffer)-1]=='c')
   {
   	printf("call the cancel function here\n");
   	buffer[strlen(buffer)-1]='\0';
   	processing(2,buffer,finder1);
   	n = write(sock,"REQUEST SUCCESSFULLY CANCELLED",50);
   	if (n < 0) error("ERROR writing to socket");
   }
   else if(buffer[strlen(buffer)-1]=='s')
   {
   	printf("call the status function here\n");
   	buffer[strlen(buffer)-1]='\0';
   	processing(3,buffer,finder1);//printf("\nfinder1=%s\n",finder1);
   	printf("status=%c finder1=%s\n",finder1[0],finder1);
   	/*if(finder == 110)//for n
   	{
   		buffer[0]='n';
   		buffer[1]='\0';
   	}
   	else if(finder == 99)//for c
   	{
   		buffer[0]='c';
   		buffer[1]='\0';
   	}*/
   	finder = strlen(finder1);
   	printf("elapsed=%ld \n",elapsed);
   	if(elapsed < CLOCK)
   	{
   		finder1[finder]='n';
   		finder1[finder+1]='\0';
   	}
   	else
   	{
   		printf("$$$ finder1=%s\n",finder1);
   		finder1[finder]='y';
   		finder1[finder+1]='\0';
   	}
   	printf("finder1=%s %d >>copying in buffer\n",finder1,strlen(finder1));
   	for(n=0;n<strlen(finder1);n++)
   	{
   		buffer[n]=finder1[n];
   		printf("buffer[%d]=%c finder1[%d]=%c\n",n,buffer[n],n,buffer[n]);
   	}
   	buffer[n]='\0';printf("buffer=%s\n",buffer);
   	n = write(sock,buffer,strlen(buffer));
   	if (n < 0) error("ERROR writing to socket");
   	printf("n=%d\n",n);
   }
   else if(buffer[strlen(buffer)-1]=='p')
   {
   	buffer[strlen(buffer)-1]='\0';
   	printf("call the admin approval reqid=%s\n",buffer);
   	processing(4,buffer,finder1);
   	n = write(sock,"REQUEST SUCCESSFULLY APPROVED",30);
   	if (n < 0) error("ERROR writing to socket");
   }
   else
   {
   	printf("do some other job\n");
   }
   
   //---------
   //n = write(sock,"I got your message",18);
   //if (n < 0) error("ERROR writing to socket");
}

int main(int argc, char **argv)
{
     static int ch, interval, logflag;
     pid_t   pid, sid;

     interval = DEFAULT_INTERVAL;
     logflag  = DEFAULT_LOGFLAG;

     
     //------------------------------server part------------------------------//
     int sockfd, newsockfd, portno, pid_ser;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     //----------------------------server part--------------------------------//
        
     while ((ch = getopt(argc, argv, "lp:")) != -1) {
           switch (ch) {
           case 'l':
                  logflag = 1;
                  break;
           case 'p':
                  interval = atoi(optarg);
                  break;
          }
     }

     pid = fork();

     if (pid < 0) {
            printf("forking unsuccessfull!\n");
            exit(EXIT_FAILURE);
     } else if (pid > 0) {
            exit(EXIT_SUCCESS);
     }

     umask(0);

     sid = setsid();

     if (sid < 0) {
             exit(EXIT_FAILURE);
     }

     if ((chdir("/home/abdul/Desktop/CSP_A4/anubhav")) < 0) {
             exit(EXIT_FAILURE);
     }

     if (logflag == 1)
             syslog (LOG_NOTICE, " started by User %d", getuid ());
        
        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        //close(STDOUT_FILENO);
        close(STDERR_FILENO);
	time_start=time(NULL);
      while (1) {
                newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, &clilen);
         	if (newsockfd < 0) 
             	error("ERROR on accept");
         	pid_ser = fork();
         	if (pid_ser < 0)
             	error("ERROR on fork");
         	if (pid_ser == 0)  {
             	close(sockfd);
             	dostuff(newsockfd);
             	exit(0);
         	}
         	else close(newsockfd);
                
       }

       exit(EXIT_SUCCESS);
}
 















