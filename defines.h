#ifndef _defines_h_
#define _defines_h_

#include <sys/socket.h>
#include "LL.h"
#include "uthash.h"

#define MAC_SIZE 6
#define IP_SIZE 4
#define HEADER_SIZE			4
#define BUFFER_SIZE 		2048
#define TYPE_DATA 			0xABCD
#define TYPE_LEAVE 			0xAB01
#define TYPE_QUIT 			0xAB12
#define TYPE_LINKSTATE 		0xABAC


//Structure holding mode of local machine, File Descriptors, and sock address
struct Config
{
	int port; //port to listen to
	//char *host 
	uint8_t ip[IP_SIZE]; // listen ip address
	char tapMac[7]; //mac address of tap
	uint8_t ethMac[MAC_SIZE]; //mac address of eth
	char *tap; //tap name
	int tapFD; //tap FD
	int linkPeriod;
	int linkTimeout;
	fd_set masterFDSET;
	fd_set readFDSET;
	int fdMax;
	LL *peersList; //list of peers
	int quitAfter;
	pthread_t listenTID;
	pthread_t privateTID;
	pthread_t publicTID; 
};
typedef struct Config Config;

struct Peer
{
	char *host; //hostname or ip; if host NULL, do not send any packets
	int port; //port to connect to
	char tapMac[7];
	char ethMac[7];
	//int mode;
	int sock; // active socket, NOTE* value of -1 means inactive
	//int tapFD;
	//int activeSock; //boolean to see if active connection
	struct sockaddr_in sockaddr;
};
typedef struct Peer Peer;

typedef struct Edge
{
	long long id;
	Peer *peer1;
	Peer *peer2;
} Edge;

struct Hash
{
	char mac[7]; //key
	int sock; //active socket
	UT_hash_handle hh; /* makes this structure hashable */
};

extern Config *config;
extern struct Hash ht;

#endif