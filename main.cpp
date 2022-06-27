#include <iostream>
#include "include/uv.h"
#include "network/tcpserver.h"
#include "uvserver/uvserver.h"

int64_t counter = 0;
void wait_for_a_while(uv_idle_t *handle) {
	counter++;
	std::cout << counter << std::endl;
	if (counter >= 100)
		uv_idle_stop(handle);
}

int main1() {
	uv_loop_t* loop = uv_loop_new();
	

	std::cout << "main" << std::endl;

	uv_run(loop, UV_RUN_DEFAULT);
	return 0;
}

int main() {
	uv_idle_t idler;
	uv_idle_init(uv_default_loop(), &idler);
	uv_idle_start(&idler, wait_for_a_while);
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);

//	TcpServer server;
//	server.Init();
//
	UVServer server;
	server.Init();
}
