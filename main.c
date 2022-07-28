#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

int main(void){
  int opcao;
  celula tab[10][20];// matriz de struct com cada celula armazendando as informações
  menu(tab);              
  return 0;
}
