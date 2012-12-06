#ifndef DNSSTRUCTS_H_GUARD
#define DNSSTRUCTS_H_GUARD

#include <stdio.h>
#include <stdint.h>
#include <netinet/ip_icmp.h>
#ifdef WIN32
  #include <winsock.h>
  #include <winsock2.h>
#else
  #include<sys/socket.h>
#endif

// struct tcpHdr {
//   uint16_t source;
//   uint16_t dest;
//   uint32_t seq;
//   uint32_t ack_seq;  
// #if __BYTE_ORDER == __LITTLE_ENDIAN
//   uint16_t res1:4;
//   uint16_t doff:4;
//   uint16_t fin:1;
//   uint16_t syn:1;
//   uint16_t rst:1;
//   uint16_t psh:1;
//   uint16_t ack:1;
//   uint16_t urg:1;
//   uint16_t res2:2;
// #elif __BYTE_ORDER == __BIG_ENDIAN
//   uint16_t doff:4;
//   uint16_t res1:4;
//   uint16_t res2:2;
//   uint16_t urg:1;
//   uint16_t ack:1;
//   uint16_t psh:1;
//   uint16_t rst:1;
//   uint16_t syn:1;
//   uint16_t fin:1;
// #endif
//   uint16_t window;  
//   uint16_t check;
//   uint16_t urg_ptr;
// } __attribute__ ((packed));

// struct ipHdr {
// #if __BYTE_ORDER == __LITTLE_ENDIAN  
//   uint8_t ip_hl:4; /* both fields are 4 bits */
//   uint8_t ip_v:4;
// #elif __BYTE_ORDER == __BIG_ENDIAN
//   uint8_t ip_v:4;
//   uint8_t ip_hl:4;
// #endif
//   uint8_t        ip_tos;
//   uint16_t       ip_len;
//   uint16_t       ip_id;
//   uint16_t       ip_off;
//   uint8_t        ip_ttl;
//   uint8_t        ip_p;
//   uint16_t       ip_sum;
//   uint32_t ip_src;
//   uint32_t ip_dst;
// } __attribute__ ((packed));

struct dnsHdr{
 uint16_t			dns_id;
 uint8_t      dns_rd:1;
 uint8_t      dns_tc:1;
 uint8_t      dns_aa:1;
 uint8_t			dns_opcode:4;
 uint8_t      dns_qr:1;
 uint8_t      dns_rcode:4;
 uint8_t      dns_z:1; 
 uint8_t      dns_unused1:1;
 uint8_t      dns_unused2:1;
 uint8_t			dns_ra:1;
 uint16_t			dns_qdcount;
 uint16_t			dns_ancount;
 uint16_t			dns_nscount;
 uint16_t			dns_arcount;
}  __attribute__ ((packed));

struct udphdr
{
  u_int16_t source;
  u_int16_t dest;
  u_int16_t len;
  u_int16_t check;
} __attribute__ ((packed));

#endif