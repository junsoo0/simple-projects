#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

void error_handling(char* message);

int main(int argc, char* argv[]) {
	int src_fd, dst_fd;
	int rd_len, wr_len;
	int total_len = 0;
	int err_chk;
	char buf[BUF_SIZE];

	if (argc != 3)
		error_handling("[Error] mymove Usage: ./mymove src_file dest_file\n");

	src_fd = open(argv[1], O_RDONLY);
	if(src_fd == -1)
		error_handling("open() error!\n");

	dst_fd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);
	if(dst_fd == -1)
		error_handling("open() error!\n");

	while (rd_len = read(src_fd, buf, sizeof(buf))) {
		if(rd_len == -1) 
			error_handling("read() error!\n");

		wr_len = write(dst_fd, buf, rd_len);
		if(wr_len == -1)
			error_handling("write() error!\n");

		total_len += wr_len;
	}
	
	err_chk = close(src_fd);
	if(err_chk == -1)
		error_handling("close() error!\n");

	err_chk = close(dst_fd);
	if(err_chk == -1)
		error_handling("close() error!\n");

	err_chk = remove(argv[1]);
	if(err_chk == -1)
		error_handling("remove() error!\n");

	printf("move from %s to %s (bytes: %d) finished.\n", argv[1], argv[2], total_len);

	return 0;
}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);

	exit(1);
}
