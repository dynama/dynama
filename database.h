#include<stdbool.h>
#include<netinet/ip.h>
#include<stdio.h>
#include<sqlite3.h>
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
#include "dnsstructs.h"
#ifndef DATABASE_H_GUARD
#define DATABASE_H_GUARD

bool setup_database(char* databaseName);

void insertDnsPacket(struct dnsHdr *d, struct iphdr *i, struct udphdr *u);

#endif