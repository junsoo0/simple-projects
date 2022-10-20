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
	char buf[BUF_SIZE];

	if (argc != 3)
		error_handling("[Error] mymove Usage: ./mymove src_file dest_file\n");

	src_fd = open(argv[1], O_RDONLY);
	if(src_fd == -1)
		error_handling("File not found!\n");
	dst_fd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);

	while (rd_len = read(src_fd, buf, BUF_SIZE)) {
		wr_len = write(dst_fd, buf, rd_len);
		total_len += wr_len;
	}
	
	close(src_fd);
	close(dst_fd);
	remove(argv[1]);
	printf("move from %s to %s (bytes: %d) finished.\n", argv[1], argv[2], total_len);
	return 0;
}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
