/*
// Suleyman Muhammad
// ECE 7248 - Computer Communication Networks
//
// C Program for Server Initiation
// usage : sock_server (TESTING usage: sock_server port #)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


void print_menu(void){
  FILE *fd;
  int s;
  char menu[2048];
  //////////////////////////////////////////////////////////////////////////////
  /*PRINT MENU*/
  fd  = fopen("menu_server.txt","r");
  printf("\n");
  while(fscanf(fd,"%s", menu) != EOF){
	printf("%s", menu);
    printf("\n");
  }//while
  s = fclose(fd);
}//print_menu

void sockerror(char *msg){//prints ERROR message to terminal when 
  perror(msg);            	//input error or socket error occurs
  exit(1);
}//sockerror

int server_connect(int sockfdes, int portnum){
  int client_len, newsockfdes;
  struct sockaddr_in server_address, client_address;
	
  memset((char *) &server_address,0, sizeof(server_address));//Clear Server 
                                                             //Address Buffer
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(portnum);
  //////////////////////////////////////////////////////////////////////////////
  /*BIND TO SOCKET*/
  if(bind(sockfdes, (struct sockaddr *) & server_address,
     sizeof(server_address)) < 0)                                    
    sockerror("ERROR, while binding!!!");

  printf("listening for connection\n");
  listen(sockfdes,10);//listen for attempted connections
  client_len = sizeof(client_address);
  newsockfdes = accept(sockfdes, (struct sockaddr *) &client_address,
                       (socklen_t *) &client_len);
  if (newsockfdes < 0) 
      sockerror("ERROR, during accept!!!");
  else
      printf("Connection Initiated!!! \n");

  return newsockfdes;
}//server_connect

int main(int argc, char *argv[]){
  //variables for socket file descriptor, port number, client length, etc.
  int sockfdes, newsockfdes, portnum, select = 0;
  int r, s, c, pid, i = 0;  
  const int port_1 = 2323;

  char buf[256], file[2048], confirm[1];
  char initial_message[2048] = "READY FOR INSTANT MESSAGING";
  FILE *fd;

  if(argc > 2){
    fprintf(stderr,"usage: %s OR %s Port #: 2323 or 3232 for testing\n",\
            argv[0], argv[0]);
    exit(1);
  }//if

  /*ESTABLISH SOCKET*/
  sockfdes = socket(AF_INET, SOCK_STREAM, 0);// IPv4 & TCP

  if (sockfdes < 0) sockerror("ERROR, while opening socket!!!");

  if (argc == 1){//PORT HARD CODED WHEN NOT TESTING
    newsockfdes = server_connect(sockfdes, port_1);
  }//if
  else{
    portnum = atoi(argv[1]);//TESING PURPOUSES
    newsockfdes = server_connect(sockfdes, portnum);
  }//else

 

  //////////////////////////////////////////////////////////////////////////////
  /*PRINT MENU*/
  print_menu();
  int u = 1, established = 0;
  while(u){//SERVER SOCKET
    ////////////////////////////////////////////////////////////////////////////
    /*MENU SELECT*/
    c = scanf("%d", &select);	  
    if(select == 1){//INSTANT MESSAGING
      /*FORK CHILD*/
      pid = fork();
      if(pid < 0) sockerror("ERROR, during fork!!!");
      
      if(pid == 0){//CHILD PROCESS
        close(sockfdes); 
        while(1){

	  if(established == 0){
            s = send(newsockfdes, initial_message, sizeof initial_message, 0);
	    if(s < 0) sockerror ("ERROR, write failed!!!");
	    ++ established;
	  }//if
          else{
   	    memset(buf, 0, 255);//Clear Buffer
            /*READ*/
   	    r = recv(newsockfdes,buf,255,0);
            if (r < 0){
              print_menu();
              sockerror("ERROR, read failed!!!");
            }//if

            printf("\nINCOMING MESSAGE:\n %s",buf);
            //////////////////////////////////////////////////////////////   
	  }//else

        }//while
      }//CHILD PROCESS
      else{//PARENT PROCESS
        c = close(newsockfdes);
	if(c < 0) sockerror ("ERROR, unable to close socket!!!");
      }//PARENT PROCESS
    }//INSTANT MESSAGING

    else if(select == 2){//FILE TRANSFER
      ////////////////////////////////////////////////////////////////////////
      /*FORK CHILD*/
      printf("File Transfer Imminent, continue? [y/n]\n");
      c = scanf("%s",confirm);
      pid = fork();

      if(pid < 0) sockerror("ERROR, during fork!!!");
      if(pid == 0){//CHILD PROCESS
        close(sockfdes);

        if(strcmp(confirm,"y")==0){
	  s = send(newsockfdes, "READY FOR FILE TRANSFER\n", 23, 0);
          if (s < 0) sockerror("ERROR, send failed!!!");

	  memset(file,0,2047);
          r = recv(newsockfdes, file, 255, 0);
          if (r < 0) sockerror("ERROR, read failed!!!");
          memset(buf, 0, 255);
          fd = fopen(file,"at");
	  if (!fd) fd = fopen(file,"wt");
	  if (!fd){
            printf("can not open %s for writing.\n", file);
	  }//if
	  else printf("file %s created\n", file);

	  while(u){
	    memset(file, 0, sizeof file - 1);
	    r = recv(newsockfdes, file, 80,0);

            if (r < 0) sockerror("ERROR, read failed!!!");
	    fwrite(file, sizeof(char), strlen(file),  fd);

	    ++i;
	    u = r;
	  }//while

	  print_menu();
	  c = fclose(fd);

	  if(c < 0) printf("ERROR, unable to close file\n");
	  c = close(newsockfdes);
	  if(c < 0) sockerror("ERROR, unable to close socket\n");  
	  exit(0);
	}//if
	else{
	  s = send(newsockfdes, "\0", 2, 0);
	  if(s < 0) sockerror("ERROR, send failed!!!");  
	}//else

      }//CHILD PROCESS

      else{//PARENT PROCESS
        c = close(newsockfdes);
        if(c < 0) printf("ERROR, unable to cloose file\n");
        select = 0;
      }//PARENT PROCESS

    }//FILE TRANSFER

    else if(select == 3){//PRINT MENU
		print_menu ();
    }//PRINT MENU
    else select = 0;

  }//SERVER SOCKET

  c = close(sockfdes);
  if(c < 0) sockerror ("ERROR, unable to close socket!!!");
  
  return 0;
}//main
