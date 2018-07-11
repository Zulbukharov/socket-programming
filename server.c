// simple server using sockets

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int ac, char **av)
{
	int sockfd, newsockfd, portno, clilen, n;
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;

	if (ac != 2)
		error("Usage: [name][port number]");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Error opening socket");
	bzero((char*)&serv_addr, sizeof(serv_addr));
	portno = atoi(av[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if ((bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
		error("Error on binding");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	if ((newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen)) < 0)
		error("Error on accept");
	bzero(buffer, 256);
	if ((n = read(newsockfd, buffer, 255)) < 0)
		error("Error reading from socket");
	printf("[%s]\n", buffer);
	if ((n = write(newsockfd, "[ok]", strlen("[ok]"))) < 0)
		error("Error writing to socket");
	return (0);
}
