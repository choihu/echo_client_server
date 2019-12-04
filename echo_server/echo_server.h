#include <stdio.h> // for perror
#include <string.h> // for memset
#include <unistd.h> // for close
#include <arpa/inet.h> // for htons
#include <netinet/in.h> // for sockaddr_in
#include <sys/socket.h> // for socket
#include <inttypes.h>
#include <string>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

extern vector<int> childfd;
extern mutex m;

void str_to_uint16(char* str, uint16_t* ret);
void connection(int fd, bool broadcast);

