/*
PortScan em C
*/
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "file.h"


void erro (char * msg)
{
  perror (msg);
  exit (1);
}
void uso (char * prog)
{
  printf ("[zHunter]: %s IP_ALVO\n", prog);
  exit (1);
}
void inicia_alvo (struct sockaddr_in * nome, int port, char * host)
{
  nome->sin_family = AF_INET;
  nome->sin_port = htons (port);
  nome->sin_addr.s_addr = inet_addr(host);
}
int main (int argc, char ** argv)
{
  rap("entrada");
  int sockfd, i, conex;
  struct sockaddr_in alvo;

  if (argc < 2) 	
    uso (*argv);
  for (i = 1; i < 65535; i++) {
    sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
      erro ("SOCKET");
    inicia_alvo (&alvo, i, argv[1]);
    conex = connect (sockfd, (struct sockaddr *)&alvo, sizeof alvo);
    if (conex == 0) { 
      printf ("porta %d aberta\n", i);
      close (conex);
    }
    close (sockfd);
  }
  return 0;
}
