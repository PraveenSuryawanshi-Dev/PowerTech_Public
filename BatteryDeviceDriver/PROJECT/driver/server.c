/**
NAME : PRAVEEN SURESH SURYAWANSHI  ( 453 ) && PRIYANKA   BORKAR (410)

SERVER PROGRAM  server.c
*/

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
//#include"my_battery_file_reader.h"
#include<pthread.h>
#define MAX 2000
#define PORT 5000
#define SA struct sockaddr
#define PATH "bat_info.txt"




 int sockfd, len, connfd , file_fd;
 struct sockaddr_in servaddr, cli;
  char read_buffer[100],write_buffer[00] , fileBuffer[100];
  int no_of_bytes;
 
  

/* c wrapper function for closing connection fd*/
void close_connection_fd()
{
 if(close(connfd)==-1)
 {
 	printf ("powerTech $:FAIL TO CLOSE CONNECTION FILE DESCRIPTORS\n"); // on error returns -1
    exit(0);
 }
 printf ("powerTech $:CONNECTION FILE DESCRIPTOR CLOSED SUCCESSFULLY !!\n"); 
 
}





/* c wrapper function for closing socked fd*/
void close_sock_fd()
{
  if(close(sockfd)==-1)
 {
 	printf ("powerTech $:FAIL TO CLOSE SOCKET FILE DESCRIPTORS\n"); // on error returns -1;
    exit(0);
 }
 printf ("powerTech $:SOCKET FILE DESCRIPTOR CLOSED SUCCESSFULLY !!\n");

}



/* c wrapper function for socket : creating socket for communication*/
 void Socket()
 {
  //get_information_of_battery();
 
   file_fd=open(PATH,O_RDONLY);
   if(file_fd==-1)
  {
  printf("powerTech $:ERROR : CANT OPEN BAT_INFO FILE\n");
  return;
  }
  printf("powerTech $:FILE OPENED SUCCESSFULLY\n");

  bzero (&servaddr, sizeof (servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
  servaddr.sin_port = htons (PORT);
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0); //on success returns socked file descriptor
    if (sockfd < 0)
      {
	printf ("powerTech $:SOCKET CREATION FAILES\n");  //on error returns -1;
	exit (0);
      }
	printf ("powerTech $:SOCKET CREATED SUCCESSFULLY\n");
      
 }







/* c wrapper function for bond : binding port and server address for communication*/
void Bind()
{
    if ((bind (sockfd, (SA *) & servaddr, sizeof (servaddr))) == -1) // on error return -1
      {
	printf ("powerTech $:SOCKET BINDING FAILES\n");
    close_sock_fd();
	exit (0);
      }
      printf ("powerTech $:SOCKET BINDED SUCCESSFULLY\n");
}





/* c wrapper function for listen : listening for incoming connections */
void Listen()
{
 
    if ((listen (sockfd, 100)) != 0) //on error returns -1
      {
	printf ("powerTech $:SOCKET LISTENING FAILES\n");
    close_sock_fd();
	exit (0);
      }
      printf ("powerTech $:SERVER LISTENNING...\n");

}





/* c wrapper function for accept : accepts the connections and perform read and write*/
void Accept()
{
    len = sizeof (cli);
    connfd = accept (sockfd, (SA *) & cli, &len); // on success returns connection fd;
    if (connfd < 0)
      {
	printf ("powerTech $:SEVER ACCEPT FAILES\n"); //on failure return -1
    close_sock_fd();
	exit (0);
      }
    else
      {
	printf ("powerTech $:SERVER ACCEPTED CLIENT\n");
      }
}




void Display()
{
 printf("\npowerTech $:SENT PACKET : %s ",fileBuffer);
}





void Read()
 {


  bzero(&fileBuffer,sizeof(fileBuffer));
   
  int endtooffset =lseek(file_fd,0,SEEK_END);
  int startoffset = lseek(file_fd,0,SEEK_SET);



  no_of_bytes=read(file_fd,fileBuffer,endtooffset);
  if(no_of_bytes>0)
  {
  printf("\npowerTech $:[ NUMBER OF BYTES READED : %d ]",no_of_bytes);
  Display();
  }
}




 void Write()
{
  write(connfd,fileBuffer,sizeof(fileBuffer));

}







void
communication_write_to_client()
{

  while(1)
{  
  bzero(&fileBuffer,sizeof(fileBuffer));
  Read();
  Write();
  sleep(5);
   
}

}







int Server()
{
  Socket();
  Bind();
  Listen();
  Accept();
  //Task_to_do();
/*CREATING THREADING FOR WRITE TO CLIENT*/
  communication_write_to_client();
  
  
return 1;
}

int main()
{
Server();
return 1;
}



 


