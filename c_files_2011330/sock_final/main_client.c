/*
// Suleyman Muhammad
// ECE 7248 - Computer Communication Networks
//
// C Program for Client Initiation
// usage : sock_client (TESTING usage: sock_client test)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>

#define MAX 100

typedef struct{
  char usr_nm[30];/* username */
  char real_name[30];
  char ip[30];    /* IP address */
} u_struct[MAX];

FILE *fd;

void sockerror(char *msg){/* SOCKET ERROR HANDLER */
  perror(msg);
  exit(0);
}/*sockerror*/


void print_menu(void){
  FILE *fd;
  int s;
  char menu[2048];/* Menu Text Buffer */

  /*PRINT MENU*/
  fd  = fopen("menu_client.txt","r");
  printf("\n");
  while(fscanf(fd,"%s", menu) != EOF){
    printf("%s", menu);
    printf("\n");
  }/*while*/

  s = fclose(fd);
}/*print_menu*/

void client_connect(int sockfdes, char *ip,  char *usr, int port){    
  struct sockaddr_in server_address;/*variables for socket file decriptor,*/ 
  struct hostent *server = 0;       /*port number, etc. */
  /////////////////////////////////////////////////////
  /*DEFINE USER IP*/
  server = gethostbyname(ip);

  if (server == NULL){
    fprintf(stderr,"ERROR, invalid host: %s \n", ip);
    exit(0);
  }//if
	
  memset((char *) &server_address, 0, sizeof(server_address));// Clear (Zero's) 
  server_address.sin_family = AF_INET;                        // serv_addr buffer
    
  bcopy((char *)server-> h_addr, (char *) &server_address.sin_addr.s_addr, server->h_length);
  server_address.sin_port = htons(port);

  if(connect(sockfdes,(struct sockaddr *) &server_address, sizeof(server_address)) < 0){
    printf("HOST IP %s", ip);
    sockerror("ERROR connecting");
  }//if

  else{printf("Connection Initiated with %s\n", usr);}
}//client_connect

void add_contact(u_struct user, int j){//ADD NEW CONTACT
  char buf[256];
  int u;
	
  memset(buf, 0, sizeof buf);
  printf("Input Real Name:\n");//REAL NAME
  u = scanf("%s", buf);
  strncpy(user[j].real_name, buf, 30);

  memset(buf, 0, sizeof buf);
  printf("Input User Name:\n");//USER NAME
  u = scanf("%s", buf);
  strncpy(user[j].usr_nm, buf, 30);

  memset(buf, 0, sizeof buf);
  printf("Input IP ADDRESS:\n");//IP ADDRESS
  u = scanf("%s", buf);
  strncpy(user[j].ip, buf, 30);

  fd = fopen("user_list.txt","at");
  if (!fd) fd = fopen("user_list.txt","wt");
  if (!fd){
	printf("can not open user_list.txt for writing.\n");
	exit(1);
  }//if
  else printf("file user_list.txt opened\n");//WRITE TO FILE

  fwrite(user[j].usr_nm, sizeof(char), strlen(user[j].usr_nm), fd);
  fwrite(" ", sizeof(char), 1, fd);
  fwrite(user[j].real_name, sizeof(char), strlen(user[j].real_name), fd);
  fwrite(" ", sizeof(char), 1, fd);
  fwrite(user[j].ip, sizeof(char), strlen(user[j].ip), fd);
  fwrite("\r\n", sizeof(char), 2, fd);
  printf("file updated!!!\n");

  exit(0);
}//add_contact

int main(int argc, char *argv[]){
  //////////////////////////////////////////////////////////////////////////////
  /*OPEN MENU FILE*/
  FILE *fd, *send_file;	
  
  int sockfdes, r, s, u, user_num, select = 0, established = 0; 
  const int port_1 = 2323;
  const int port_2 = 3232;
  char  buf[256], file[2048], *message;
  
  u_struct user;
  char usr_nm[30], real_name[30], ip[30];
  int i = 0, j; 


  if (argc > 2){
    fprintf(stderr,"usage: %s OR %s test\n", argv[0], argv[0]);
    exit(0);
  }//if

  memset(file, 0, sizeof file - 1);
  /////////////////////////////////////////////////////////////////////////////
  /*DEFINE USERS*/

  fd = fopen("user_list.txt","r");
  while(fscanf(fd,"%s %s %s", usr_nm, real_name, ip)!= EOF){
    strncpy(user[i].usr_nm, usr_nm, sizeof usr_nm);
    strncpy(user[i].real_name, real_name, sizeof real_name);
    strncpy(user[i].ip, ip, sizeof ip);
    ++i;
  }//while

  u = fclose(fd);
  if(u < 0) printf("ERROR, unable to close file");

  printf("\nwho would you like to connect to?\n");

  for(j=0; j < i; ++j){//DISPLAY USERS
    printf("%d.%s FULL NAME: %s", j+1, user[j].usr_nm, user[j].real_name);
    printf("\n");
  }//DISPLAY USERS
  j = j+1;
  printf("input corresponding user number\n or press %d to ADD a contact\n", j);
  
  //user select
  u = scanf("%d", &user_num);
  if(user_num == j) add_contact(user, j);
  user_num = user_num-1;

  //////////////////////////////////////////////////////
  /*OPEN SOCKET*/
  sockfdes = socket(AF_INET, SOCK_STREAM, 0);// Create Socket using IPv4
  if (sockfdes < 0)                          // protocol(AF_INET) and streaming
    sockerror("ERROR opening socket");       // data transfer(SOCK_STREAM=>TCP)

  ///////////////////////////////////////////////////////////////////////////
  /*TESTING PURPOSES*/
  if(argc == 2){//CONNECT TO SOCKET
    if(user_num == 1) client_connect(sockfdes, user[user_num].ip, user[user_num].usr_nm,port_1);
    if(user_num == 2) client_connect(sockfdes, user[user_num].ip, user[user_num].usr_nm, port_2);
  }//if
  else client_connect(sockfdes, user[user_num].ip, user[user_num].usr_nm, port_1);

  print_menu();
  int k = 1;
  while(k){
    u = scanf("%d", &select);
    if(select == 1){//INSTANT MESSAGING
      //////////////////////////////////////////////////////////
      /*CONNECT*/
      s = send(sockfdes, "GREETINGS\n", 9, 0);
      while(1){

	////////////////////////////////////////////////////////// 
        /*WRITE MESSAGE*/   
	if(established == 0){
	  memset(buf, 0,sizeof buf);//clear buffer
          r = recv(sockfdes,buf,255,0);
          if(r < 0) sockerror("ERROR, read failed");
          printf("\nSERVER:\n%s\n",buf);
          ++ established;
	}//if
	else{
          memset(buf,0, 255);// clear buffer
          printf("Enter Message:\n ");
          message = fgets(buf, 255, stdin);// get message input:
          s = send(sockfdes, buf, 255,0);
          if(s < 0) sockerror("ERROR, write failed");
          //////////////////////////////////////////////////////////
        }//else

      }//while
    }//INSTANT MESSAGING

    if(select == 2){//FILE TRANSFER
      printf("wait for confirmation\n");

      memset(buf, 0, 255);
      r = recv(sockfdes, buf, 255, 0);
      if(r < 0) sockerror("Error, File Transfer Denied");

      printf("SERVER:\n%s\n", buf);
      printf("input file name\n");
      memset(buf, 0, 255);
      u = scanf("%s",buf);
      
      s = send(sockfdes, buf, 255, 0);
      if(s < 0) sockerror("ERROR, write failed");

      send_file = fopen(buf,"r");

      while(fgets(file, 80, send_file) != NULL){
        s = send(sockfdes, file, 80, 0);
	if(s < 0) sockerror("ERROR, write failed");
	memset(file, 0, sizeof file - 1);
      }//while	
      s = send(sockfdes,"\0",2,0);
      if(s < 0) sockerror("ERROR, write failed");
     
      s = fclose(send_file);
      if(s < 0) printf("ERROR, unable to close file");
      printf("TO COMPLETE TYPE 4 THEN ENTER\n");
    }//FILE TRANSFER

    if(select == 3){//PRINT MENU
      print_menu();
    }//PRINT MENU

    if(select == 4){//EXIT
      k = 0;
    }//EXIT
    else select = 0;
  }//while 

  close(sockfdes);
  return 0;
}//main
