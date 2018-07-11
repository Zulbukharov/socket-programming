#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int ac, char **av)
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];

	if (ac != 4)
		error("Usage: [name][server name][port number][message]");
	portno = atoi(av[2]);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Error opening socket");
	if (!(server = gethostbyname(av[1])))
		error("Error: [No host such name]");
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if ((connect(sockfd, &serv_addr, sizeof(serv_addr))) < 0)
		error("Error: [Connection Failed]");
	if ((n = write(sockfd, av[3], strlen(av[3]))) < 0)
		error("Error: [Write to socket]");
	bzero(buffer, 256);
	if ((n = read(sockfd, buffer, 255)) < 0)
		error("Error: [Read from socket failed]");
	printf("[%s]\n", buffer);
	return (0);
}
