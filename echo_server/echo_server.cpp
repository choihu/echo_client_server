#include "echo_server.h"

void str_to_uint16(char* str, uint16_t* ret) {
    char *end;
    intmax_t val = strtoimax(str, &end, 10);
    *ret = (uint16_t) val;
    return;
}

void connection(int fd, bool broadcast) {
	while (true) {
                const static int BUFSIZE = 1024;
                char buf[BUFSIZE];
                ssize_t received = recv(fd, buf, BUFSIZE - 1, 0);
                if (received == 0 || received == -1) {
                       perror("recv failed");
                       break;
                }
                buf[received] = '\0';
		printf("Client #%d msg: %s\n", fd, buf);
		if(broadcast) {
			bool flg = false;
			for(vector<int>::iterator it = childfd.begin(); it != childfd.end(); it++) {
				ssize_t sent = send(*it, buf, strlen(buf), 0);
				if (sent == 0) {
					perror("broadcast failed");
					flg = true;
					break;
				}
			}
			if(flg) break;
		}
		else {
	                ssize_t sent = send(fd, buf, strlen(buf), 0);
        	        if (sent == 0) {
                	        perror("send failed");
                      		break;
			}
                }
        }
	for(vector<int>::iterator it = childfd.begin(); it != childfd.end();) {
		if(*it == fd) {
			printf("Client #%d disconnected\n", *it);
			m.lock();
			childfd.erase(it);
			m.unlock();
		}
		else 
			it++;
	}
	return;
}
