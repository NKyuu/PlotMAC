#include <stdio.h>
#include <stdlib.h>
#include "libs/graphic.h"
#include "libs/data.h"

int main(int argc, char const *argv[])
{
    /*
    if(argc != 5)
    {
        printf("Error: number of arguments is not valid.\n");
        printf("%s title xlabel ylabel <path>", argv[0]);
        printi();
        printf("Example: %s Graphic X Y %s\n", argv[0], print_info());
        return 0;
    }

    char* title = argv[1];
    char* xlabel = argv[2];
    char* ylabel = argv[3];
    char* path = argv[4];*/

    int linhas;
    int colunas;
    float **table;

    table = malloc(1000 * sizeof(*table));

    for(int i = 0; i < 1000; i++)
    {
        table[i] = malloc(1000 * sizeof(*table[i]));
    }
    
    char *nomes[1000];

    carrega_dados("resources/BRICS_PIBPerCapita.csv", &linhas, &colunas, table, nomes);

    plot("teste", "x", "y", nomes, linhas, colunas, table);

    return 0;
}
