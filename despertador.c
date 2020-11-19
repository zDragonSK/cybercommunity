/*  
         @ [ Nirvax ] @
       Criado por zDragonSK
    É um despertador bem básico

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define limp "clear"
#define music "parole Iron_Man_Alarm.mp3"

// estrutura de data & hora
typedef struct data_hora {
  int hor, min;
  char str_mes[15];
}dh1;

// Funções a ser usadas
void clear(void) { system(limp); } // limpar o terminal
void esperar(int h, int m); // processar os valores

// bloco principal
int main(void){
  int h, m;
  fprintf(stdout, "Hora para despertar hh:mm: ");
  fscanf(stdin, "%d:%d", &h, &m);
  fprintf(stdout, "Despertador foi ativado!\n");
  esperar(h, m);
  return 0;
}

// Processar os valores colocado pelo usuario e esperar pela hora
void esperar(int h, int m) {
  struct data_hora dt_hr;
  struct tm *data;
  time_t tempo;
  int despertou = 0;
  
  // loop para esperar a hora correta
  while (despertou != 1){
    
    tempo = time(NULL);
    data = localtime(&tempo);
    dt_hr.hor = data -> tm_hour;
    dt_hr.min = data -> tm_min;

    if((dt_hr.hor >= h) && (dt_hr.min >= m)) system(music);
    usleep(999999);
  }
}
