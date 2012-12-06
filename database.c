#include "database.h"

// parts taken from http://milky.manishsinha.net/2009/03/30/sqlite-with-c/

bool setup_database(char* databaseName){
	sqlite3 *db;
	FILE *file;
	int retVal;
	//int q_cnt = 1, q_size = 150, ind = 9;
	//char **queries = malloc(sizeof(char) * q_cnt * q_size);
	//sqlite3_stmt *stmt;

	if(file = fopen(databaseName, "r"))
	{
		fclose(file);
		return true;

	}
	else
	{
		retVal = sqlite3_open(databaseName, &db);
		if(retVal){
			printf("Database connection failed\n");
			return false;
		}
		printf("Database file just created, needs to be set up.\n");
		char create_hosttable[200]="CREATE TABLE IF NOT EXISTS host(hostName varchar(25) PRIMARY KEY, macAddress varchar(17) NOT NULL, ipAddress varchar(15) NOT NULL)";
		retVal=sqlite3_exec(db,create_hosttable,0,0,0);

		char create_queriestable[200]="CREATE TABLE IF NOT EXISTS dnsQuery(queryID INTEGER PRIMARY KEY AUTOINCREMENT, domainName varchar(25) NOT NULL, ipAddress varchar(15) NOT NULL)";
		retVal=sqlite3_exec(db,create_queriestable,0,0,0);

		char create_hostqueriestable[300]="CREATE TABLE IF NOT EXISTS hostQueriesDNS(queryID INTEGER, hostName varchar(25), domainName varchar(25), FOREIGN KEY(queryID) REFERENCES dnsQuery(queryID), FOREIGN KEY(hostName) REFERENCES host(hostName),  FOREIGN KEY(domainName) REFERENCES dnsQuery(domainName), PRIMARY KEY(queryID, hostName))";
		retVal=sqlite3_exec(db,create_hostqueriestable,0,0,0);

// THE GOAL
//	      	char create_packettable[400]="CREATE TABLE IF NOT EXISTS dnsPacket(packetID INTEGER PRIMARY KEY, sourceIP varchar(15), destinationIP varchar(15), destinationHost varchar(25), sourcePort INTEGER, destinationPort INTEGER, queryID INTEGER, questionCount INTEGER, answerCount INTEGER, authorityCount INTEGER, addlRecordCount INTEGER, qr INTEGER, queryResponse varchar(50), FOREIGN KEY(destinationHost) REFERENCES host(hostName))";

	char create_packettable[300]="CREATE TABLE IF NOT EXISTS dnsPacket(myKey INTEGER PRIMARY KEY, packetID TEXT, sourceIP TEXT, destinationIP TEXT, sourcePort TEXT, destinationPort TEXT, payLoad TEXT)";
		retVal=sqlite3_exec(db,create_packettable,0,0,0);
		return true;
	}
}

void insertDnsPacket(struct dnsHdr *d, struct iphdr *i, struct udphdr *u){//char pid[15], char sip[20], char dip[20], char sp[9], char dp[7], char pl[25]){

	struct sockaddr_in source,dest;
	memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = i->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = i->daddr;
    
    char *destination = (char *)malloc(16);
    strncpy(destination, inet_ntoa(dest.sin_addr), 16);
    char *src = (char *)malloc(16);
    strncpy(src, inet_ntoa(source.sin_addr), 16);

	sqlite3 *db;
	sqlite3_open("database.sqlite3",&db);
	char *insert = sqlite3_mprintf("INSERT INTO dnsPacket VALUES(NULL,'%d','%s','%s','%d','%d','%d');\n",d->dns_id,src,destination,u->source,u->dest,d->dns_qr);
	int retval;
	retval=sqlite3_exec(db,insert,0,0,0);
}