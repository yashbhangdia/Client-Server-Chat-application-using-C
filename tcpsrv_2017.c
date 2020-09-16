#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

#define MAX 80

int main()
{ int listenfd, connfd;
  struct sockaddr_in srvinfo, cliinfo;
  int len;
  char buff[80];
  
  //Creation of Socket
  //int socket(int domain, int type, int protocol);

  if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  		perror("Socket Creation Failed\n");
  else
       printf("\n Socket Created Successfully\n");
       
  // Associating sockaddr_in info
  
   srvinfo.sin_family = AF_INET;
   srvinfo.sin_port =htons(5007);
   srvinfo.sin_addr.s_addr= inet_addr("127.0.0.1"); 
   
 // Registering socket at IP/Internet Layer 
  
   if(bind(listenfd, (struct sockaddr *)&srvinfo, sizeof(srvinfo))==-1)  
   perror("Binding Failed\n");
   else
       printf("\n Binding is Successful\n");
       
   listen(listenfd,4);
   len = sizeof(srvinfo);
   
   connfd = accept(listenfd, (struct sockaddr *)&cliinfo, &len);
   

   int n;
   while ( (n = recv(connfd, buff, 80,0)) > 0)  
      {
      
        printf("\nFrom CLIENT: %s",buff);
        
        printf("Enter Your Reply: ");
        bzero(buff,80);
        fgets(buff,80,stdin);

        if((strncmp(buff, "end", 4)) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
        
        printf("\nTo CLIENT: %s ",buff);
  
        /* Send message to the client */
        int in = send(connfd,buff,strlen(buff),0);
        if (in < 0) 
        {
       perror("\nServer Error: Writing to Client");
          return 0;
        }
    
        bzero(buff,80);
                    
      }
      close(connfd);

       
   close(listenfd);
   //close(connfd);
}
       
