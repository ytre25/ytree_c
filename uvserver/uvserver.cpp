#include "uvserver.h"
#include "/data/ytree_c/include/uv.h"
#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_PORT 7000

#define DEFAULT_BACKLOG 128
#include <iostream>
uv_loop_t *loop;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->len = suggested_size;
    buf->base = static_cast<char*>(malloc(suggested_size));
}

void echo_write(uv_write_t* req, int status) {
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free(req);
}

void read_cb(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf) {
	if(nread > 0) {
		fprintf(stdout, "recv:%s\n", buf->base);
		fflush(stdout);

	    uv_write_t* req = (uv_write_t*)malloc(sizeof(uv_write_t));
	    uv_buf_t uvBuf = uv_buf_init(buf->base, nread);
	    uv_write(req, client, &uvBuf, 1, echo_write);
	    return;

	} else if (nread < 0) {
		if(nread != UV_EOF) {
		fprintf(stderr, "Read err %s\n", uv_err_name(nread));
		} else {
			fprintf(stderr, "client disconnnet\n");
		}
	}

	if (buf->base != NULL) {
	    free(buf->base);   
	}
}

void on_new_connection(uv_stream_t *server, int status) {
	std::cout << "new accept" << std::endl;
	if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
		return;
    }

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));//为tcp client申请资源
	uv_tcp_init(loop, client);//初始化tcp client句柄

	// 判断accept是否成功
    if (uv_accept(server, (uv_stream_t *) client) == 0) {
        //从传入的stream中读取数据，read_cb会被多次调用，直到数据读完，或者主动调用uv_read_stop方法停止
		uv_read_start((uv_stream_t *) client, alloc_buffer, read_cb);

    } else {
        uv_close((uv_handle_t *) client, NULL);
    }
}

void UVServer::Init() {
	  loop = uv_default_loop();


	
	uv_tcp_t server;
	uv_tcp_init(loop, &server);

	
	struct sockaddr_in addr;
	uv_ip4_addr("127.0.0.1", DEFAULT_PORT, &addr);
	uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
	
	int r = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);
	if (r) {

	}

	 uv_run(loop, UV_RUN_DEFAULT);

}
