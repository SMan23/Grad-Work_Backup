#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define BOOL int
#define FALSE 0
#define TRUE 1

#define BUFSIZE   1024
#define MAX_NODES 10

enum MSG_TYPE{ERROR,DATA,ROUTE_REQ,ROUTE_REPLY};

/* 
  TO DO:  
      lots of stuff, including
      - store messages in a buffer in case there's an error
*/

void error(char *msg)
{
    perror(msg);
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
   char hop_seq[16*MAX_NODES];
   char *route_table[MAX_NODES][2];
   char *message_queue[MAX_NODES];
   int udpport = 9090;
   int tcpport = 5050;
   int broadcast = 1;
   fd_set read_fds, master;
   int sock, fdmax;
   int i,j, msg_type;

   for (i=0; i<MAX_NODES; ++i)
     for (j=0; j<2; ++j)
       strcpy(route_table[i][j],"/0");

   //Get socket
   udpsock=socket(AF_INET, SOCK_DGRAM, 0);
   if (udpsock < 0) error("Opening socket");

   if (setsockopt(udpsock, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof broadcast) == -1) 
   {
        error("setsockopt (SO_BROADCAST)");
        return 0;
   }

   //set up my udp address
   length = sizeof(my_udp_addr);
   bzero(&my_udp_addr,length);
   my_udp_addr.sin_family=AF_INET;
   my_udp_addr.sin_addr.s_addr=INADDR_ANY;
   my_udp_addr.sin_port=htons(udpport);

   //set up broadcast address
   bcast_addr.sin_family = AF_INET;
   bcast_hp = gethostbyname((char*)"10.255.255.255");
   if(bcast_hp==0) error("Unknown host");
   bcopy((char *)bcast_hp->h_addr, 
        (char *)&bcast_addr.sin_addr,
         bcast_hp->h_length);
   bcast_addr.sin_port = htons(udpport);

   //set up my tcp address
   tcpsock = socket(AF_INET,SOCK_STREAM,0);
   if(tcpsock < 0) error("ERROR: opening tcp socket");
   my_tcp_addr.sin_family = AF_INET;
   my_tcp_addr.sin_addr.s_addr = INADDR_ANY;
   my_tcp_addr.sin_port = htons(tcpport);

   sprintf(my_addr,"%s",(char *)inet_ntoa(from_udp_addr.sin_addr));

   //bind to udp socket
   if (bind(udpsock,(struct sockaddr *)&my_udp_addr,length)<0) 
       error("udp binding");

   //bind to tcp socket
   if (bind(tcpsock, (struct sockaddr*)&my_tcp_addr,length)<0)
       error("tcp binding");

   //listen on tcp socket
   listen(tcpsock,5);

   //Add socket to file descriptor set
   FD_ZERO(&read_fds);
   FD_ZERO(&master);
   FD_SET(0,&master);
   FD_SET(udpsock, &master);
   FD_SET(tcpsock, &master);
   fdmax = tcpsock;

   /*   printf("Broadcasting hello message\n");
  
	 n=sendto(udpsock,"hello",5 ,0,(struct sockaddr*)&bcast_addr,fromlen);
   if (n < 0) error("sendto"); */

   fromlen = sizeof(struct sockaddr_in);
   while (1) 
   {
      read_fds = master;
      printf("Enter something to send: \n");
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
	       //Route Request Received State
               n = recvfrom(udpsock,buf,BUFSIZE,0,(struct sockaddr *)&from_udp_addr,&fromlen);
               if (n < 0) error("recvfrom");
              
	       printf("Received datagram: %s\n", buf);
               printf("Add %s to neighbor table\n", (char *)inet_ntoa(from_udp_addr.sin_addr));

	       sscanf(buf,"%d %s %s %s", &msg_type, hop_seq, target, msg);

               if(msg_type == ROUTE_REQ)
               {
		  //ROUTE REQUEST STATE

                  if(target==my_addr)
		  {
                     //ROUTE REPLY SEND STATE
                  }
                  else
                  {
   		     //check if we have route
                     /*
		     if(route_found)
                     {
                     	//ROUTE REPLY SEND STATE
                     }
                     else
                     {
                        //ROUTE REPLY FORWARD STATE
                     }
                     */
                  }
	       }
               else
               {
		  //Unknown msg type
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

                printf("TCP message from %s: %s\n",(char*)inet_ntoa(from_tcp_addr.sin_addr),buf);

                sscanf(buf,"%d %[^\n]\n", &msg_type, buf);

                if(msg_type==DATA)
		{
		   //Data Received State
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

			//rotate hop sequence
			sprintf(hop_seq, "%s;%s",hops_left, next_hop);
			
                        //get new next hop
			sscanf(hop_seq, "%[^;^\n]", next_hop);
                        
                        //connect and send to next hop
                        sprintf(buf,"%d %s %s %s %s", DATA, hop_seq, target, originator, msg);

			tcp_hp = gethostbyname((char*)next_hop);
                	if(tcp_hp==0) error("Unknown host");
                	bcopy((char *)tcp_hp->h_addr, 
                      		(char *)&from_tcp_addr.sin_addr,
                       		tcp_hp->h_length);

                	/* Connect to the server */
                	if (connect(tcpsock, (struct sockaddr *)&from_tcp_addr, fromlen) == -1)
                	{
                  		//ERROR SEND STATE
                	}
                        else
			{
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
              sscanf(input,"%s %[^\n]\n",dest_ip,buf);

              // look through the route table and find the destination,
              // if destination is found, copy the route and message into the outBuf.
              route_found = FALSE;
              for (i=0; (i<MAX_NODES) && (!route_found); ++i)
              {
                if (strcmp(route_table[i][0],dest_ip)==0)
                {
                  strcpy(hop_seq, route_table[i][1]);
                  sprintf(outBuf,"%d %s %s %s %s",DATA, hop_seq, dest_ip, my_addr, buf); 
                  /* TO DO: store message in message_queue */
                  route_found = TRUE;              
                }
              }

              if (route_found) // send message
              {
                // get first hop
                sscanf(hop_seq,"%[^;^\n]",next_hop);

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
           
              } // if (route_found_
              else // could not find route, send a route request
              {
                //ROUTE REQUEST SEND state
                sprintf(outBuf,"%d %s %s %s",ROUTE_REQ,my_addr,dest_ip,buf);
                
	        n=sendto(udpsock,outBuf,BUFSIZE,0,(struct sockaddr*)&bcast_addr,fromlen);
                if (n < 0) error("sendto"); 
              }

            } // if (sock==0)
         }//end if FD_ISSET
      }//end for
   }//end while
}

