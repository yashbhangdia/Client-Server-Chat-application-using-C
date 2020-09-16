#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

#define MAX 80

int main()
{ int clifd;
  struct sockaddr_in clientinfo;
  char rbuff[80];

  if((clifd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  		perror("Socket Creation Failed\n");
  else
       printf("\n Socket Created Successfully\n");
       
  
   clientinfo.sin_family = AF_INET;
   clientinfo.sin_port =htons(5007);
   clientinfo.sin_addr.s_addr= inet_addr("127.0.0.1"); 
   
   if(bind(clifd, (struct sockaddr *)&clientinfo, sizeof(clientinfo))==-1)  
   perror("Binding Failed\n");
   else
       printf("\n Binding is Successful\n");
       
   if(connect(clifd, (struct sockaddr *)&clientinfo, sizeof(clientinfo))==-1)
        perror("Connect Failed\n");
   else
       printf("\n Connect Successful\n");

   while(1)
	{
			printf("Enter Your Message: ");
    		bzero(rbuff,80);
    		fgets(rbuff,80,stdin);

    		if ((strncmp(rbuff, "end", 4)) == 0) { 
	            printf("Client Exit...\n"); 
	            break; 
        	} 
    		
		    printf("\nTo SERVER: %s ",rbuff);
	
		/* Send message to the server */
    		int in = send(clifd,rbuff,strlen(rbuff),0);
		    if (in < 0) 
		    {
			 perror("\nClient Error: Writing to Server");
		    	return 0;
		    }
		    
		/* Now read server response */
		    bzero(rbuff,80);
		    in = recv(clifd,rbuff,80,0);
		    if (in < 0) 
		    {
			 perror("\nClient Error: Reading from Server");
			return 0;
		    }
		    printf("\nFrom SERVER: %s ",rbuff);
	}
         
  close(clifd);
}
       
