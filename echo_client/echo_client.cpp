#include "echo_client.h"

void str_to_uint16(char* str, uint16_t* ret) {
    char *end;
    intmax_t val = strtoimax(str, &end, 10);
    *ret = (uint16_t) val;
    return;
}

void print_IP(uint8_t* ip) {
  printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  return;
}

void parse_IP(char* ip, uint8_t* out) {
  out[0] = (uint8_t)atoi(strtok(ip, "."));
  for(int i = 1; i < 4; i++) {
    out[i] = (uint8_t)atoi(strtok(NULL, "."));
  }
  return;
}

void send_msg(int sockfd) {
	while(true) {
		const static int BUFSIZE = 1024;
                char buf[BUFSIZE];
                scanf("%s", buf);
                if (strcmp(buf, "quit") == 0) break;

                ssize_t sent = send(sockfd, buf, strlen(buf), 0);
                if (sent == 0) {
                        perror("send failed");
                        break;
                }
	}
	return;
}

void recv_msg(int sockfd) {
	while(true) {
		const static int BUFSIZE = 1024;
                char buf[BUFSIZE];
		
		ssize_t received = recv(sockfd, buf, BUFSIZE - 1, 0);
                if (received == 0 || received == -1) {
                        perror("recv failed");
                        break;
                }
                buf[received] = '\0';
                printf("recv msg: %s\n", buf);
	}
	return;
}

