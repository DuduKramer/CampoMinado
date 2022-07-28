#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"
//função inicia o jogo zerando todas as celulas 
//tanto as de bomba, quanto as de ao redor e as que estao abertas
void iniciar(celula tab[10][20]){
  for(int i=0; i<10; i++){
    for(int j=0; j<20; j++){
      tab[i][j].around = 0;
      tab[i][j].open = 0;
      tab[i][j].has_bomb = 0;
    }
  }
}
//função que sorteia aleatoriamente a posição das bombas
void bombas(celula tab[10][20]){
  srand(time(0));
  for (int i = 0; i < 40; i++) {
    int linha = rand() % 10;
    int coluna = rand() % 20;
    if (tab[linha][coluna].has_bomb == 0) {
      tab[linha][coluna].has_bomb = 1;
    } else {
      i--;
    }
  }
}
//função que verifica se a posição está dentro do tabuleiro
int ValidarCoordenada(int l, int c){
  if(l>=0 && l<=10 && c>=0 && c<=20){
    return 1;
  }else{
    return 0; 
  }
}
//função que alimenta as posições ao redor das bombas enumerando a quantidade ao redor
void BombsAround(celula tab[10][20]){
  for(int i=0; i<10; i++){
    for(int j=0; j<20; j++){
      if(tab[i-1][j].has_bomb == 1 && ValidarCoordenada(i-1,j) == 1){
        tab[i][j].around += 1;  
      }if(tab[i-1][j+1].has_bomb == 1 && ValidarCoordenada(i-1,j+1) == 1){
        tab[i][j].around += 1;  
      }if(tab[i][j+1].has_bomb == 1 && ValidarCoordenada(i,j+1) == 1){
        tab[i][j].around += 1;  
      }if(tab[i+1][j+1].has_bomb == 1 && ValidarCoordenada(i+1,j+1) == 1){
        tab[i][j].around += 1;  
      }if(tab[i+1][j].has_bomb == 1 && ValidarCoordenada(i+1,j) == 1){
        tab[i][j].around += 1;  
      }if(tab[i+1][j-1].has_bomb == 1 && ValidarCoordenada(i+1,j-1) == 1){
        tab[i][j].around += 1;  
      }if(tab[i][j-1].has_bomb == 1 && ValidarCoordenada(i,j-1) == 1){
        tab[i][j].around += 1;  
      }if(tab[i-1][j-1].has_bomb == 1 && ValidarCoordenada(i-1,j-1) == 1){
        tab[i][j].around += 1;  
      }
    }
  }
}
//função com os principais cabeçalhos do jogo
void cabecalho(int n){
  if(n == 1){
    printf("\t\t\t\t\t************************************************\n");
    printf("\t\t\t\t\t************************************************\n");
    printf("\t\t\t\t\t*****************CAMPO MINADO*******************\n");
    printf("\t\t\t\t\t************************************************\n");
    printf("\t\t\t\t\t************************************************\n");
  }else if(n == 2){
    printf("\t\t\t\t\t************************************************\n");
    printf("\t\t\t\t\t*******************MODO AUTO********************\n");
    printf("\t\t\t\t\t************************************************\n");
  }else if(n == 3){
    printf("\t\t\t\t\t************************************************\n");
    printf("\t\t\t\t\t*******************CAMPANHA*********************\n");
    printf("\t\t\t\t\t************************************************\n");
  }else if(n == 4){
    printf("\n\t\t\t******************************GAME OVER!******************************\n");
  }else if(n == 5){
    printf("\n\t\t\t****************************** VITORIA! ******************************\n");
  }
}
//função com a abertura das celulas e laço caso a posição seja um zero
void abrir(int l, int c, celula tabuleiro[10][20]){
  //laço que abre oito posições e se tiver uma vazia continua abrindo se abrir um numero para
  if(ValidarCoordenada(l,c) == 1 && tabuleiro[l][c].open == 0){
      tabuleiro[l][c].open = 1;
        if(tabuleiro[l][c].around == 0 && tabuleiro[l][c].has_bomb == 0){
        //recursiva para abrir aos arredores 
        abrir(l-1,c-1,tabuleiro);//superior esquerda
        abrir(l-1,c,tabuleiro);//superior
        abrir(l-1,c+1,tabuleiro);//superior direita
        abrir(l,c-1,tabuleiro);//esquerda
        abrir(l+1,c+1,tabuleiro);//inferior direita
        abrir(l,c+1,tabuleiro);//direita
        abrir(l+1,c-1,tabuleiro);//inferior esquerda
        abrir(l+1,c,tabuleiro);//inferior

      }
  }
}
//função que dá uma possivel dica quando solicitada
void dica(celula tab[10][20]){
  int flag = 0;
  for(int i=0; i<10; i++){
    for(int j=0; j<20; j++){
      if(tab[i][j].open == 1 && tab[i][j].around >= 1 && flag == 0){
        if(ValidarCoordenada(i,j+2) == 1 && tab[i][j+2].open == 0){
          printf("Tente a jogada %d %d\n", i, j+2);
          flag = 1;
        }else if(ValidarCoordenada(i,j-2) == 1 && tab[i][j-2].open == 0){
          printf("Tente a jogada %d %d\n", i, j-2);
          flag = 1;
        }else if(ValidarCoordenada(i+2,j) == 1 && tab[i+2][j].open == 0){
          printf("Tente a jogada %d %d\n", i+2, j);
          flag = 1;
        }else if(ValidarCoordenada(i-2,j) == 1 && tab[i-2][j].open == 0){
          printf("Tente a jogada %d %d\n", i-2, j);
          flag = 1;
        }else if(ValidarCoordenada(i-2,j+1) == 1 && tab[i-2][j+1].open == 0){
          printf("Tente a jogada %d %d\n", i-2, j+1);
          flag = 1;
        }else if(ValidarCoordenada(i-2,j-1) == 1 && tab[i-2][j-1].open == 0){
          printf("Tente a jogada %d %d\n", i-2, j-1);
          flag = 1;
        }else if(ValidarCoordenada(i+2,j+1) == 1 && tab[i+2][j+1].open == 0){
          printf("Tente a jogada %d %d\n", i+2, j+1);
          flag = 1;
        }else if(ValidarCoordenada(i+2,j-1) == 1 && tab[i+2][j-1].open == 0){
          printf("Tente a jogada %d %d\n", i+2, j-1);
          flag = 1;
        }
      }
    }
  }
}
//função de impressão do tabuleiro
void tabuleiro(celula mat[10][20]) {
  printf("\n\t");
  for (int i = 0; i < 20; i++) {
    if (i == 0) {
      printf("    %d", i);
    } else if (i < 10) {
      printf("   %d", i);
    } else {
      printf("  %d", i);
    }
  }
  printf("\n\t  "
         "---------------------------------------------------------------------"
         "------------\n");
  for (int i = 0; i < 10; i++) {
    printf("\t%d | ", i);
    for (int j = 0; j < 20; j++) {
      if(mat[i][j].open == 1){
        if(mat[i][j].has_bomb == 1){
          printf("* | ");
        }else{
          if(mat[i][j].around == 0){
            printf("/ | ", mat[i][j].around);
          }else{
            printf("%d | ", mat[i][j].around);
          } 
        }
      }else{
        printf("  | ");
      }
    }
    printf(" ");
    printf("\n\t  "
           "-------------------------------------------------------------------"
           "--------------\n");
  }
  printf("\n\n");
}
//função que imprime o tabuleiro em caso de game over 
void tabuleirofinal(celula mat[10][20]) {
  printf("\n\t");
  for (int i = 0; i < 20; i++) {
    if (i == 0) {
      printf("    %d", i);
    } else if (i < 10) {
      printf("   %d", i);
    } else {
      printf("  %d", i);
    }
  }
  printf("\n\t  "
         "---------------------------------------------------------------------"
         "------------\n");
  for (int i = 0; i < 10; i++) {
    printf("\t%d | ", i);
    for (int j = 0; j < 20; j++) {
      if(mat[i][j].open == 1 || mat[i][j].has_bomb == 1){
        if(mat[i][j].has_bomb == 1){
          printf("* | ");
        }else{
          if(mat[i][j].around == 0){
            printf("/ | ", mat[i][j].around);
          }else{
            printf("%d | ", mat[i][j].around);
          } 
        }
      }else{
        printf("  | ");
      }
    }
    printf(" ");
    printf("\n\t  "
           "-------------------------------------------------------------------"
           "--------------\n");
  }
  printf("\n\n");
}
//função que verifica a quantidade de celulas ja abertas
int jaabertas(celula tab[10][20]){
  //A função percorre o tabuleiro contando quantas celulas já estão abertas
  int cont = 0; 
  for(int i=0; i<10; i++){
    for(int j=0; j<20; j++){
      if(tab[i][j].open == 0){
        cont++;
      }
    }  
  }
  return cont;
}
//função que delimita as jogadas do modo campanha 
void jogadas(celula tab[10][20]){
  
  time_t inicia = time(NULL), fim; 
  long final;
  int flag = 0;
  int escolha, linha, coluna, bomba = 0;
  while(bomba == 0){
    cabecalho(3);
    tabuleiro(tab);
    if(flag == 1){
      system("tput reset");
      cabecalho(3);
      tabuleiro(tab);
      fim = time(NULL);
      final = fim - inicia; 
      printf("\n");
      printf("Tempo de Jogo: %ld segundos!\n\n", final);
      flag = 0; 
    }
    printf("O que você deseja fazer: \n");
    printf("  1.Inserir sua jogada.\n");
    printf("  2.Saber o tempo de jogo.\n");
    printf("  3.Uma dica.\n");
    scanf("%d", &escolha);
    if(escolha == 1){
        system("tput reset");
        cabecalho(3);
        tabuleiro(tab);
        printf("Insira suas jogadas: ");
        scanf("%d %d", &linha, &coluna);
        abrir(linha,coluna,tab);
        system("tput reset");
      if(tab[linha][coluna].has_bomb == 1){
        system("tput reset");
        cabecalho(3);
        tabuleirofinal(tab);
        cabecalho(4);
        bomba = 1;
      }else if(jaabertas(tab) == 160){
        system("tput reset");
        cabecalho(3);
        tabuleirofinal(tab);
        cabecalho(5);
        bomba = 1;
      }
    }else if(escolha == 2){
      flag = 1;
    }else if(escolha == 3){
      system("tput reset");
      dica(tab);
      printf("\n");
    }else{
      system("tput reset");
      printf("Escolha invalida.\n\n");
      tabuleiro(tab);
    }
  }
}
void ia(celula tab[10][20]){
  //função para não abrir em bomba na primeira jogada
  while(tab[4][9].has_bomb != 0 && tab[4][9].around != 0){
    iniciar(tab);
    bombas(tab);
    BombsAround(tab);
  }
  //primeira jogada sempre no meio do tabuleiro
  if(tab[4][9].has_bomb == 0){
    abrir(4,9,tab);
    system("tput reset");
    cabecalho(2);
    tabuleiro(tab); 
    printf("\n\t\t\t\t\t\t\t\t\t Jogada 4 9 \n");
    sleep(1);
  }
  //i e j para o laço, bomba para marcar quando aparecer uma bomba
  int i, j, bomba = 0, flag;
  //tentativa de função para abrir em um laço as casas "seguras"
  while(bomba == 0 || jaabertas(tab) == 160){ 
    flag = 0;
        i = rand() % 10;
        j = rand() % 10;
        if(tab[i][j].open == 0 && bomba == 0){
          abrir(i, j, tab);
          system("tput reset");
          cabecalho(2);
          tabuleiro(tab); 
          printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i, j);
          sleep(2);
          if(tab[i][j].has_bomb == 1){
            bomba = 1;
          }
        }else if (bomba == 0){
          if(tab[i][j].open == 1 && tab[i][j].around >= 1){
             if(ValidarCoordenada(i,j+2) == 1 && tab[i][j+2].open == 0 && bomba == 0){
               if(tab[i][j+2].around == 0){
                 abrir(i, j+2, tab);
               }
                system("tput reset");
                cabecalho(2);
                tabuleiro(tab); 
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i, j+2);
                sleep(2);
                flag = 1;
                if(tab[i][j+2].has_bomb == 1){
                  bomba = 1;
                }
            }else if(ValidarCoordenada(i,j-2) == 1 && tab[i][j-2].open == 0 && bomba == 0){
                if(tab[i][j-2].around == 0){
                 abrir(i, j-2, tab);
               }
                system("tput reset");
                cabecalho(2);
                tabuleiro(tab); 
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i, j-2);
                sleep(2);
                flag = 1;
                if(tab[i][j-2].has_bomb == 1){
                  bomba = 1;
                }
            }else if(ValidarCoordenada(i+2,j) == 1 && tab[i+2][j].open == 0 && bomba == 0){
               if(tab[i+2][j].around == 0){
                 abrir(i+2, j, tab);
               }
                system("tput reset");
                cabecalho(2);
                tabuleiro(tab); 
                printf("\n\t\t\tJogada %d %d\n", i, j);
                flag = 1;
                if(tab[i+2][j].has_bomb == 1){
                  bomba = 1;
                }
            }else if(ValidarCoordenada(i-2,j) == 1 && tab[i-2][j].open == 0 && bomba == 0){
                if(tab[i-2][j].around == 0){
                  abrir(i-2, j, tab);
                }
                system("tput reset");
                tabuleiro(tab); 
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i-1, j);
                sleep(2);
                flag = 1;
                if(tab[i-2][j].has_bomb == 1){
                  bomba = 1; 
                } 
            }else if(ValidarCoordenada(i-2,j+1) == 1 && tab[i-2][j+1].open == 0 && bomba == 0){
                if(tab[i-2][j+1].around == 0){
                  abrir(i-2, j+1, tab);
                }
                abrir(i-2, j+1, tab);
                system("tput reset");
                cabecalho(2);
                tabuleiro(tab); 
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i, j);
                flag = 1;
                if(tab[i-2][j+1].has_bomb == 1){
                  bomba = 1;
                }
            }else if(ValidarCoordenada(i-2,j-1) == 1 && tab[i-2][j-1].open == 0 && bomba == 0){
                if(tab[i-2][j-1].around == 0){
                  abrir(i-2, j-1, tab);
                }
                system("tput reset");
                tabuleiro(tab); 
                cabecalho(2);
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i-2, j-1);
                sleep(2);
                flag = 1;
                if(tab[i-2][j-1].has_bomb == 1){
                  bomba = 1;
                }
            }else if(ValidarCoordenada(i+2,j+1) == 1 && tab[i+2][j+1].open == 0 && bomba == 0){
                if(tab[i+2][j+1].around == 0){
                  abrir(i+2, j+1, tab);
                }
                system("tput reset");
                tabuleiro(tab); 
                cabecalho(2);                
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i+2, j+1);
                sleep(2);
                flag = 1;
                if(tab[i+2][j+1].has_bomb == 1){
                  bomba = 1;
                }
            }else if(ValidarCoordenada(i+2,j-1) == 1 && tab[i+2][j-1].open == 0 && bomba == 0){
                if(tab[i+2][j-1].around == 0){
                  abrir(i+2, j-1, tab);
                }
                system("tput reset");
                cabecalho(2);
                tabuleiro(tab); 
                printf("\n\t\t\t\t\t\t\t\t\t Jogada %d %d\n", i+2, j-1);
                sleep(2);
                flag = 1;
               if(tab[i+2][j-1].has_bomb == 1){
                  bomba = 1;
                }
        }          
      }
    }
    if(bomba == 1){
      system("tput reset");
      cabecalho(2);
      tabuleirofinal(tab);
      printf("\n");
      printf("\t\t\t\t******************** GAME OVER ********************");
      sleep(3);
      break;
    }
  }
}
//função de menu do jogo
void menu(celula tab[10][20]){
  time_t inicio, final, iniciobombastico, finalbombastico; //calcular o tempo total de jogo
  long tempofinal, finalbomba;
  system("tput reset");
  
  int n;
  cabecalho(1);
  printf("\n");
  printf("1. Modo Automatico\n");
  printf("2. Campanha\n");
  printf("\n");
  printf("Selecione o modo de jogo: ");           
  scanf("%d", &n);
  printf("\n");
  system("tput reset");
  if (n == 1){
    iniciobombastico = time(NULL);
    iniciar(tab);
    bombas(tab);
    BombsAround(tab);
    tabuleiro(tab);
    ia(tab);
    finalbombastico = time(NULL);
    printf("\n");
    finalbomba = finalbombastico - iniciobombastico; 
    printf("\n");
    printf("\t\t\t\t\t  O tempo total de jogo foi de %ld segundos\n", finalbomba);
    sleep(3);
    return menu(tab); 
  }else if (n == 2){
    inicio = time(NULL);
    iniciar(tab);
    bombas(tab);
    BombsAround(tab);
    jogadas(tab);
    final = time(NULL);
    tempofinal = final - inicio; 
    printf("\n");
    printf("\t\t\t\t\tO tempo total de jogo foi de %ld segundos\n", tempofinal);
    sleep(3);
    return menu(tab); 
  } else {
    printf("\n");
    printf("Seleção invalida!\n");
    printf("\n");
    return menu(tab); 
  }
}
