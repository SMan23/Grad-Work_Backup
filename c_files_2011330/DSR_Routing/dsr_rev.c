#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BOOL int
#define FALSE 0
#define TRUE 1
#define DEBUG 1

#define BUFSIZE   1024
#define MAX_NODES 10
#define MAX_REQUESTS 25

enum MSG_TYPE{ERROR,DATA,ROUTE_REQ,ROUTE_REPLY};

struct Request 
{
    char pairing[32];
    int expiration;
};

struct RouteTable
{
    char target[15];
    char route[16*MAX_NODES];
};

/* 
  TO DO:  
      lots of stuff, including
      route reply received
      Gather information on route request received and route reply received
      handle errors properly
      clean up code
*/

void error(char *msg)
{
    perror(msg);
}


void addRoute(struct RouteTable routeTable[], char target[], char route[])
{
   int i;
   BOOL targetFound = FALSE;
   //Search for existing target
   for(i=0; i<MAX_NODES; i++)
   {
      if(strcmp(routeTable[i].target, target)==0)
      {
         sprintf(routeTable[i].route,"%s",route);
         targetFound = TRUE;
         break;
      }
   }
   
   if(!targetFound)
   {
      //Find first empty spot
      for(i=0; i<MAX_NODES; i++)
      {
	 if(strcmp(routeTable[i].target,"")==0)
         {
	    sprintf(routeTable[i].target,"%s", target);
            sprintf(routeTable[i].route,"%s", route);
            return;
         }
      }
   }

}

void getRoute(struct RouteTable routeTable[], char target[], char route[])
{
   int i;
   sprintf(route, "");

   //Search route table
   for(i=0; i<MAX_NODES; i++)
   {
      if(strcmp(routeTable[i].target,target)==0)
      {
         sprintf(route,"%s",routeTable[i].route);
      }
   }
}

void clearRequests(struct Request requests[])
{
   time_t now = time(NULL);
   int i;
   for(i=0;i<MAX_REQUESTS;i++)
   {
      if(strcmp(requests[i].pairing, "empty")!=0)
      {
         if(requests[i].expiration < (int)now)
         {
	    sprintf(requests[i].pairing,"empty");
         }
      }
   }
}

void reverseRoute(char route[], char revRoute[])
{
  char* pch;
  char node[256];

  pch = strtok(route,";");
  
  while(pch!=NULL)
  {  
     //printf("pch = %s\n", pch);
     sprintf(node, "%s", pch);
     //printf("node = %s\n", node);
     
     strcat(node, ";");
     strcat(node, revRoute);
     strcpy(revRoute, node);
     
     //printf("revRoute = %s\n", revRoute);
     pch = strtok(NULL, ";");
  }
}

void addRequest(struct Request requests[], char pairing[])
{
   time_t now = time(NULL);
   int i;

   for(i=0; i<MAX_REQUESTS; i++)
   {
      if(strcmp(requests[i].pairing,"empty")==0)
      {
	 sprintf(requests[i].pairing,"%s", pairing);
         requests[i].expiration = (int)now+5;
         break;
      }
   }
}

BOOL checkRequest(struct Request requests[], char pairing[])
{
   int i;
   BOOL result = FALSE;

   for(i=0;i<MAX_REQUESTS;i++)
   {
      if(strcmp(requests[i].pairing, pairing)==0)
      {
	 result = TRUE;
         break;
      }
   }
}

int main(int argc, char *argv[])
{
   BOOL route_found;
   int udpsock, length, fromlen, n;
   struct sockaddr_in my_udp_addr;
   struct sockaddr_in from_udp_addr;
   struct sockaddr_in bcast_addr;
   struct sockaddr_in my_tcp_addr;
   struct sockaddr_in from_tcp_addr;
   int tcpsock, newtcpsock;
   struct hostent *tcp_hp;
   struct hostent *bcast_hp;
   char buf[BUFSIZE],outBuf[BUFSIZE];
   char input[256], msg[1024];
   char dest_ip[15],next_hop[15], my_addr[15];
   char target[15], originator[15], hops_left[16*MAX_NODES];
   char hop_seq[16*MAX_NODES], rev_route[16*MAX_NODES];
   int udpport = 9090;
   int tcpport = 5050;
   int broadcast = 1;
   fd_set read_fds, master;
   int sock, fdmax;
   int i,j, msg_type;
   struct Request requests[MAX_REQUESTS];
   struct RouteTable route_table[MAX_NODES-1];
   char pairing[32], reoute_reply[16*MAX_NODES];
   char route[16*MAX_NODES],  route_reply[16*MAX_NODES];
   char new_hop[15], new_hop_seq[16*MAX_NODES];

   if(DEBUG) printf("Initializing Request Table\n");
   for(i=0; i<MAX_REQUESTS; i++)
   {
       sprintf(requests[i].pairing, "empty"); 
   }

   if(DEBUG) printf("Initializing Route Table\n");
   for (i=0; i<MAX_NODES; ++i)
   {
      sprintf(route_table[i].target,"");
      sprintf(route_table[i].route,"");
   }

   //Get socket
   if(DEBUG) printf("Getting UDP socket\n");
   udpsock=socket(AF_INET, SOCK_DGRAM, 0);
   if (udpsock < 0) error("Opening socket");

   if(DEBUG) printf("Setting UDP socket options\n");
   if (setsockopt(udpsock, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof broadcast) == -1) 
   {
        error("setsockopt (SO_BROADCAST)");
        return 0;
   }

   //set up my udp address
   if(DEBUG) printf("Setting up my UDP address\n");
   length = sizeof(my_udp_addr);
   bzero(&my_udp_addr,length);
   my_udp_addr.sin_family=AF_INET;
   my_udp_addr.sin_addr.s_addr=INADDR_ANY;
   my_udp_addr.sin_port=htons(udpport);

   //set up broadcast address
   if(DEBUG) printf("Setting up UDP broadcast address\n");
   bcast_addr.sin_family = AF_INET;
   bcast_hp = gethostbyname((char*)"10.255.255.255");
   if(bcast_hp==0) error("Unknown host");
   bcopy((char *)bcast_hp->h_addr, 
        (char *)&bcast_addr.sin_addr,
         bcast_hp->h_length);
   bcast_addr.sin_port = htons(udpport);

   //set up my tcp address
   if(DEBUG) printf("Setting up my TCP address\n");
   tcpsock = socket(AF_INET,SOCK_STREAM,0);
   if(tcpsock < 0) error("ERROR: opening tcp socket");
   my_tcp_addr.sin_family = AF_INET;
   my_tcp_addr.sin_addr.s_addr = INADDR_ANY;
   my_tcp_addr.sin_port = htons(tcpport);

   sprintf(my_addr,"%s",(char *)inet_ntoa(from_udp_addr.sin_addr));

   //bind to udp socket
   if(DEBUG) printf("Binding UDP socket\n");
   if (bind(udpsock,(struct sockaddr *)&my_udp_addr,length)<0) 
       error("udp binding");

   //bind to tcp socket
   if(DEBUG) printf("Binding TCP socket\n");
   if (bind(tcpsock, (struct sockaddr*)&my_tcp_addr,length)<0)
       error("tcp binding");

   //listen on tcp socket
   if(DEBUG) printf("Listening on TCP socket\n");
   listen(tcpsock,5);

   //Add socket to file descriptor set
   if(DEBUG) printf("Adding sockets to FD set\n");
   FD_ZERO(&read_fds);
   FD_ZERO(&master);
   FD_SET(0,&master);
   FD_SET(udpsock, &master);
   FD_SET(tcpsock, &master);
   fdmax = tcpsock;

   /*
     printf("Broadcasting hello message\n");
     n=sendto(udpsock,"hello",5 ,0,(struct sockaddr*)&bcast_addr,fromlen);
     if (n < 0) error("sendto"); 
   */

   fromlen = sizeof(struct sockaddr_in);
   if(DEBUG) printf("Entering Wait State\n");
   while (1) 
   {
      read_fds = master;
      printf("Enter message to send: \n");
      if(select(fdmax+1, &read_fds, NULL, NULL, NULL)==-1)
      {
         perror("select");
      } 
        
      for(sock = 0; sock <= fdmax; sock++)
      {
         if(FD_ISSET(sock, &read_fds)) //new message on file descriptor
         {
	    //UDP Message received
            if(sock==udpsock)
            {
	       if(DEBUG) printf("UDP messge received\n");
               n = recvfrom(udpsock,buf,BUFSIZE,0,(struct sockaddr *)&from_udp_addr,&fromlen);
               if (n < 0) error("recvfrom");
              
	       if(DEBUG) printf("Received UDP packet: %s\n", buf);

	       sscanf(buf,"%d %s %s %s", &msg_type, hop_seq, target, msg);

               //get reverse route
               if(DEBUG) printf("Reversing\n");
               reverseRoute(hop_seq, rev_route);

	       /*
		  TO DO:
			Get as much information out of packet as possible
			Take reversed route and get route back to originator
			Remove last node until there are none to get all 
			intermediate hops.                         
               */

               if(msg_type == ROUTE_REQ)
               {
		  //ROUTE REQUEST RECEIVED STATE
                  if(DEBUG) printf("Entering Route Request Received State\n");

                  //get pairing
                  sscanf(hop_seq,"%[^;]",originator);
                  sprintf(pairing,"%s;%s",originator,target);
                   
                  if(checkRequest(requests,pairing)||(strcmp(originator,my_addr)==0))
                  {
                     //ignore packet. we have already processed this request
                     if(DEBUG) printf("Request already processed\n");
                  }
                  else if(target==my_addr)
		  {
                     //ROUTE REPLY SEND STATE
                     if(DEBUG) printf("I am target. Entering Route Reply Send State\n");
                     sprintf(route_reply, "%s;%s", hop_seq, my_addr);
                     sscanf(route_reply, "%[^;];%[^\n]", originator, route_reply);

                     sprintf(outBuf, "%d %s %s", ROUTE_REPLY, route_reply, rev_route);
                     sscanf(rev_route,"%[^;\n]", next_hop);

                     tcp_hp = gethostbyname((char*)next_hop);
                     if(tcp_hp==0) error("Unknown host");
                	bcopy((char *)tcp_hp->h_addr, 
                        (char *)&from_tcp_addr.sin_addr,
                        tcp_hp->h_length);

                     /* Connect to the server */
                     if(DEBUG) printf("Connecting to TCP server\n");
                     if (connect(tcpsock, (struct sockaddr *)&from_tcp_addr, fromlen) == -1)
                     {
                  	//error
                     }
                     if(DEBUG) printf("Sending TCP message: %s\n", outBuf);
                     write(tcpsock, outBuf, BUFSIZE);
                  }
                  else 
                  {
   		     //check if we have route
		     getRoute(route_table, target, route);
                   
                     if(strcmp(route,"")!=0) //we have route
                     {
                     	//ROUTE REPLY SEND STATE
                        if(DEBUG) printf("I have route. Entering Route Reply Send State\n");
                        sprintf(route_reply, "%s;%s;%s",hop_seq,my_addr,route);
                        sscanf(route_reply,"%[^;];%[^\n]", originator, route_reply);

                        sprintf(outBuf, "%d %s %s",ROUTE_REPLY, route_reply, rev_route);

                        //Send reply to originator
                        sscanf(rev_route, "%[^;]", next_hop);

                        tcp_hp = gethostbyname((char*)next_hop);
                	if(tcp_hp==0) error("Unknown host");
                	   bcopy((char *)tcp_hp->h_addr, 
                           (char *)&from_tcp_addr.sin_addr,
                           tcp_hp->h_length);

                	/* Connect to the server */
                        if(DEBUG) printf("Connecting to TCP server\n");
                	if (connect(tcpsock, (struct sockaddr *)&from_tcp_addr, fromlen) == -1)
                	{
                  	  //error
                        }
                        if(DEBUG) printf("Sending TCP message: %s\n", outBuf);
                	write(tcpsock, outBuf, BUFSIZE);  
                        
                     }
                     else //we do not have route
                     {
                        //ROUTE REPLY FORWARD STATE
                        if(DEBUG) printf("No route found. Entering Route Reply Forward State\n");
                        //append my address to current hop sequence
                        sprintf(new_hop_seq,"%s;%s", hop_seq, my_addr);

                        //Broadcast route request
                        sprintf(outBuf, "%d %s %s %s", ROUTE_REQ, new_hop_seq, target, msg);

                        if(DEBUG) printf("Broadcasting packet: %s\n", outBuf);
                        n=sendto(udpsock,outBuf,BUFSIZE,0,(struct sockaddr*)&bcast_addr,fromlen);
                        if (n < 0) error("sendto"); 
                     }
                     
                  }
	       }
               else
               {
		  //Unknown msg type
                  if(DEBUG) printf("Unknown message type\n");
               }

              
            } // if (sock==udpsock)

            //TCP Message received
            if(sock==tcpsock)
            {
                // TCP Message can be either DATA, ERROR, or ROUTE REPLY
                //handle tcp message
                
                newtcpsock = accept(tcpsock, (struct sockaddr*)&from_tcp_addr,&fromlen);
                if(newtcpsock<0) error("ERROR: accepting connection");
                n = read(newtcpsock,buf,BUFSIZE);
                if(n<0) error("ERROR: reading from tcp socket"); 

                if(DEBUG)printf("TCP message from %s: %s\n",(char*)inet_ntoa(from_tcp_addr.sin_addr),buf);

                sscanf(buf,"%d %[^\n]\n", &msg_type, buf);

                if(msg_type==DATA)
		{
		   //Data Received State
		   if(DEBUG) printf("Entering Data Received State\n");
		   sscanf(buf, "%s %s %s %[^\n]\n", hop_seq,target, originator, msg);
                   sscanf(hop_seq, "%[^;];%[^\n]\n",next_hop,hops_left);
                   
 		   //Check if we are target
		   if(my_addr == target)
                   {
			//Display messge
			printf("Message from %s: %s\n", originator, msg);
                   }
		   else
		   {
 			//Data Forward state
                        if(DEBUG) printf("Entering Data Forward State\n");
			//rotate hop sequence
			sprintf(hop_seq, "%s;%s",hops_left, next_hop);
			
                        //get new next hop
			sscanf(hop_seq, "%[^;^\n]", next_hop);
                        
                        //connect and send to next hop
                        sprintf(outBuf,"%d %s %s %s %s", DATA, hop_seq, target, originator, msg);

			tcp_hp = gethostbyname((char*)next_hop);
                	if(tcp_hp==0) error("Unknown host");
                	bcopy((char *)tcp_hp->h_addr, 
                      		(char *)&from_tcp_addr.sin_addr,
                       		tcp_hp->h_length);

                	/* Connect to the server */
                        if(DEBUG) printf("Establishing TCP connection with %s\n", next_hop);
                	if (connect(tcpsock, (struct sockaddr *)&from_tcp_addr, fromlen) == -1)
                	{
                  		//ERROR SEND STATE
                	}
                        else
			{
                           if(DEBUG) printf("Sending TCP message: %s\n", outBuf);
                	   write(tcpsock, outBuf, BUFSIZE);
			} 
                   }//end else
		}//msg_typ==DATA
		else if(msg_type==ROUTE_REPLY)
		{
		   //Route Reply Received State
		}
		else if(msg_type==ERROR)
		{
		   //Error Received State
		}
		else
		{
		   error("ERROR: Unknown Message Type");
		} 
                
            }//sock==tcpsock 

            //Send Data
            if(sock==0)
            {
              strcpy(buf,"/0");
              bzero(input, 256);
              fgets(input, 255, stdin);
              sscanf(input,"%s %[^\n]\n",target,buf);

              // look through the route table and find the destination,
              // if destination is found, copy the route and message into the outBuf.

              getRoute(route_table, target, hop_seq);

              if (strcmp(hop_seq,"")!=0) //we have route
              {
                // get first hop
                sscanf(hop_seq,"%[^;^\n]",next_hop);

                //construct message
                sprintf(outBuf,"%d %s %s %s %s",DATA, hop_seq, target, my_addr, buf);

                tcp_hp = gethostbyname((char*)next_hop);
                if(tcp_hp==0) error("Unknown host");
                bcopy((char *)tcp_hp->h_addr, 
                      (char *)&from_tcp_addr.sin_addr,
                       tcp_hp->h_length);

                /* Connect to the server */
                if (connect(tcpsock, (struct sockaddr *)&from_tcp_addr, fromlen) == -1)
                {
                  //error
                }

                write(tcpsock, outBuf, BUFSIZE);                    
              
                // rather than closing here, we will allow the receiver to terminate
                // the connection.                             
           
              } // if (route_found)
              else // could not find route, send a route request
              {
                //ROUTE REQUEST SEND state
                sprintf(outBuf,"%d %s %s %s",ROUTE_REQ,my_addr,target,buf);
                
	        n=sendto(udpsock,outBuf,BUFSIZE,0,(struct sockaddr*)&bcast_addr,fromlen);
                if (n < 0) error("sendto"); 
              }

            } // if (sock==0)
         }//end if FD_ISSET
      }//end for
   }//end while
}

