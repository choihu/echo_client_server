#include <stdio.h> // for perror
#include <string.h> // for memset
#include <unistd.h> // for close
#include <arpa/inet.h> // for htons
#include <netinet/in.h> // for sockaddr_in
#include <sys/socket.h> // for socket
#include <inttypes.h>
#include <mutex>
#include <thread>
using namespace std;

void str_to_uint16(char* str, uint16_t* ret);
void print_IP(uint8_t* ip);
void parse_IP(char* ip, uint8_t* out);