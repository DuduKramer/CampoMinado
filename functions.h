#ifndef function
#define function

typedef struct {
  int has_bomb; // possui bomba = 1, não possui bomba = 0;
  int open;     // celula aberta = 1; celula fechada = 0;
  int around;   // bombas vizinhas maximo 8;
} celula;

void iniciar(celula tab[10][20]);
  
void bombas(celula tab[10][20]);
  
int ValidarCoordenada(int l, int c);
  
void BombsAround(celula tab[10][20]); 

void cabecalho(int n);

void abrir(int l, int c, celula tabuleiro[10][20]);
   
void dica(celula tab[10][20]);
 
void tabuleiro(celula mat[10][20]);

void tabuleirofinal(celula mat[10][20]);

int jaabertas(celula tab[10][20]);
 
void jogadas(celula tab[10][20]);
 
void ia(celula tab[10][20]);

void menu(celula tab[10][20]);
  
#endif