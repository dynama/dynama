/*
    Packet sniffer using libpcap library

    // Modified from http://www.binarytides.com/packet-sniffer-code-c-libpcap-linux-sockets/

*/
#include<pcap.h>
#include<stdio.h>
#include<stdlib.h> // for exit()
#include<string.h> //for memset
 
#include<sys/socket.h>
#include<arpa/inet.h> // for inet_ntoa()
#include<net/ethernet.h>
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
//#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
 
#include "parser.h" // provides the log file setup and the packet parser
#include "database.h" // provide the function to check to see if a database exists and set one up if not
 
//FILE *logfile;
//struct sockaddr_in source,dest;
//int tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j;
 
int main()
{
    pcap_if_t *alldevsp , *device;
    pcap_t *handle; //Handle of the device that shall be sniffed
    char* databaseName = "database.sqlite3";
 
    char errbuf[100] , *devname , devs[100][100];
    int count = 1 , n;
     
    //First get the list of available devices
    printf("Finding available devices ... ");
    if( pcap_findalldevs( &alldevsp , errbuf) )
    {
        printf("Error finding devices : %s" , errbuf);
        exit(1);
    }
    printf("Done");
     
    //Print the available devices
    printf("\nAvailable Devices are :\n");
    for(device = alldevsp ; device != NULL ; device = device->next)
    {
        printf("%d. %s - %s\n" , count , device->name , device->description);
        if(device->name != NULL)
        {
            strncpy(devs[count] , device->name, 16);
        }
        count++;
    }
     
    //Ask user which device to sniff
    printf("Enter the number of the device you want to sniff : ");
    scanf("%d" , &n);
    devname = devs[n];
     
    //Open the device for sniffing
    printf("Opening device %s for sniffing ... " , devname);
    handle = pcap_open_live(devname , 65536 , 1 , 0 , errbuf);
     
    if (handle == NULL)
    {
        fprintf(stderr, "Couldn't open device %s : %s\n" , devname , errbuf);
        exit(1);
    }
    printf("Done\n");
     
    setup_log();

    if(setup_database(databaseName)){
        printf("Database is setup.\n");
    }
    else {
        printf("No database file exists.\n");
    }
     

    //Put the device in sniff loop
    pcap_loop(handle , -1 , process_packet , NULL);
     
    return 0;  
}
