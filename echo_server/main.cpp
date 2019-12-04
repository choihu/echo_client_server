#include "echo_server.h"

vector<int> childfd;
mutex m;

void usage() {
	printf("syntax: echo_server <port> [-b]\n");
	printf("example: echo_server 1234 [-b]\n");
	printf("option [-b]: send message to every clients after receive message\n");
	return;
}

int main(int argc, char* argv[]) {
	bool broadcast = false;
	if(argc < 2 && argc > 3) {
		usage();
		return -1;
	}
	if(argc == 3) {
		if(!strcmp(argv[2], "-b")) {
			broadcast = true;
		}
		else {
			usage();
			return -1;
		}
	}
		
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket failed");
		return -1;
	}

	uint16_t port;
	str_to_uint16(argv[1], &port);

	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &optval , sizeof(int));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

	int res = bind(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(struct sockaddr));
	if (res == -1) {
		perror("bind failed");
		return -1;
	}

	res = listen(sockfd, 2);
	if (res == -1) {
		perror("listen failed");
		return -1;
	}

	while (true) {
		struct sockaddr_in addr;
		socklen_t clientlen = sizeof(sockaddr);
		int child = accept(sockfd, reinterpret_cast<struct sockaddr*>(&addr), &clientlen);

		m.lock();	
		childfd.push_back(child);
		m.unlock();

		if (child < 0) {
			perror("ERROR on accept");
			break;
		}
		printf("Client #%d connected\n", child);
		
		if(child > 0) {
			thread t(connection, child, broadcast);
			t.detach();
		}
	}

	close(sockfd);
}
