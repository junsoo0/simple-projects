#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define REQUEST 0
#define RESPONSE 1
#define QUIT 2

#define ERROR 0
#define SUCCESS 1

typedef struct {
	int cmd; // 0: request, 1: response, 2: quit
	char addr[20]; // dotted-decimal address 저장(20 bytes)
	struct in_addr iaddr; // inet_aton() result 저장
	int result; // 0: Error, 1: Success
} PACKET;

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	int err_chk;
	PACKET send_packet, recv_packet;
	socklen_t clnt_addr_size;

	memset(&send_packet, 0, sizeof(send_packet));
	memset(&recv_packet, 0, sizeof(recv_packet));

	if(argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	printf("---------------------------\n");
	printf(" Address Conversion Server \n");
	printf("---------------------------\n");

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error!\n");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	err_chk = bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	if(err_chk == -1)
		error_handling("bind() error!\n"); 
	
	err_chk = listen(serv_sock, 5);
	if(err_chk == -1)
		error_handling("listen() error!\n");
	
	clnt_addr_size = sizeof(clnt_addr);  
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error!\n");  

/* 소켓 통신 시작 */

	while(1) {
		read(clnt_sock, &recv_packet, sizeof(recv_packet));

		if(recv_packet.cmd == QUIT) {
			printf("[Rx] QUIT message received\n");
			break;
		}

		printf("[Rx] Received Dotted-Decimal Address: %s\n", recv_packet.addr);

		send_packet.cmd = RESPONSE;
		strcpy(send_packet.addr, recv_packet.addr);

		err_chk = inet_aton(recv_packet.addr, &send_packet.iaddr);
		if(err_chk == 0) {
			send_packet.result = ERROR;
			write(clnt_sock, &send_packet, sizeof(send_packet));
			printf("[Tx] Address conversion fail: (%s)\n", send_packet.addr);
		}
		else {
			printf("inet_aton(%s) -> %#x\n", send_packet.addr, send_packet.iaddr.s_addr);

			send_packet.result = SUCCESS;
			write(clnt_sock, &send_packet, sizeof(send_packet));
			printf("[Tx] cmd: %d, iaddr: %#x, result: %d\n", send_packet.cmd, send_packet.iaddr.s_addr, send_packet.result);
		}
		
		puts("");
	}
	
	printf("Server socket close and exit\n");
	
/* 소켓 통신 끝 */

	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
