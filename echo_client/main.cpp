#include "echo_client.h"

void usage() {
	printf("systax: echo_client <host> <port>\n");
	printf("example: echo_client 127.0.0.1 1234\n");
	return;
}

int main(int argc, char* argv[]) {
	if(argc != 3) {
		usage();
		return -1;
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket failed");
		return -1;
	}

	uint8_t tmp_ip[4];
	uint16_t port;
	parse_IP(argv[1], tmp_ip);
	str_to_uint16(argv[2], &port);
	printf("Connect to ");
	print_IP(tmp_ip);
	printf(":%d\n", port);
	uint32_t* ip_addr = (uint32_t*)&tmp_ip;
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = *ip_addr;
	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

	int res = connect(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(struct sockaddr));
	if (res == -1) {
		perror("connect failed");
		return -1;
	}
	printf("connected\n");

	thread t1(send_msg, sockfd);
	thread t2(recv_msg, sockfd);

	t1.detach();
	t2.join();

	close(sockfd);
}
