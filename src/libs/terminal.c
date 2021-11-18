#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic.h"

#define MAXROWS 50
#define MAXCOLS 100

int *colunas = 100;
char* title;
char* x;
char* y;
char* col_names;


void define_titulo(char *titulo)
{
    title = titulo;
}

void define_rotulo_x(char *nome)
{
    x = nome;
}

void define_rotulo_y(char *nome)
{
    y = nome;
}

void define_nomes_linhas(char *nomes_linhas[])
{
    col_names = *nomes_linhas;
}

void desenha_grafico(int linhas, int colunas, float planilha[][colunas])
{
    //Alignment helpers
    int n = MAXCOLS/colunas;
    int m = MAXROWS/linhas;

    int length_name = sizeof(length_name)/sizeof(char);

    //Title printing
    for(int i = 0; i < MAXCOLS/2 - length_name; i++) printf(" ");
    printf("%s", title);
    printf("\n");
    printf("\n");

    //Graph plotting
    for(int j = MAXCOLS; j > 0; j--)
    {
        for(int i = MAXROWS; i > 0; i--)
        {
            if(i == MAXROWS)
            {
                
            } else {

            }
        }
    }
}

void terminal(char *title, char *x, char *y, char *url)
{

}