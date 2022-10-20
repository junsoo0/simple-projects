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

#define BUF_SIZE 20

typedef struct {
	int cmd; // 0: request, 1: response, 2: quit
	char addr[20]; // dotted-decimal address 저장(20 bytes)
	struct in_addr iaddr; // inet_aton() result 저장
	int result; // 0: Error, 1: Success
} PACKET;

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	int err_chk;
	PACKET send_packet, recv_packet;
	char buf[BUF_SIZE];

	memset(&send_packet, 0, sizeof(send_packet));
	memset(&recv_packet, 0, sizeof(recv_packet));

	if(argc != 3) {
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error!\n");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	err_chk = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(err_chk == -1) 
		error_handling("connect() error!\n");

/* 소켓 통신 시작 */

	while(1) {
		printf("Input dotted-decimal address: ");
		scanf("%s", buf);

		if(strcasecmp(buf, "quit") == 0) {
			send_packet.cmd = QUIT;
			write(sock, &send_packet, sizeof(send_packet));
			printf("[Tx] cmd: 2(QUIT)\n");
			break;
		}

		send_packet.cmd = REQUEST;
		strcpy(send_packet.addr, buf);
		write(sock, &send_packet, sizeof(send_packet));
		printf("[Tx] cmd: %d, addr: %s\n", send_packet.cmd, send_packet.addr);

		read(sock, &recv_packet, sizeof(recv_packet));
		if(recv_packet.result == ERROR)
			printf("[Rx] cmd: %d, Address conversion fail! (result: %d)\n", recv_packet.cmd, recv_packet.result);
		else 
			printf("[Rx] cmd: %d, Address conversion: %#x (result: %d)\n", recv_packet.cmd, recv_packet.iaddr.s_addr, recv_packet.result);

		puts("");
	}

	printf("Client socket close and exit\n");

/* 소켓 통신 끝 */

	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
