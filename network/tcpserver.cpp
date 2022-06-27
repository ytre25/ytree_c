#include "tcpserver.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>

void TcpServer::Init() {
	auto socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1) {
	//	painc("socket init");
//		exit(-1);
	}

	
	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(struct sockaddr_in));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi("7000"));
	inet_aton("127.0.0.1", &s_addr.sin_addr);
	bind(socketFd, (struct sockaddr*)&s_addr, sizeof(struct sockaddr_in));

	listen(socketFd, 10);


		struct sockaddr_in c_addr;
		memset(&c_addr, 0, sizeof(struct sockaddr_in));

		int c_fd;
	while(1) {
		socklen_t client = sizeof(struct sockaddr_in);
		c_fd = accept(socketFd, (struct sockaddr*)&c_addr, &client);
		std::cout << "ins" << std::endl;


	}

}


