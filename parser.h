#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

void setup_log();

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);

#endif