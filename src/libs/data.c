#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void carrega_dados(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[])
{
    FILE *csv;
    csv = fopen(caminho_dos_dados, "r");

    if(csv == NULL)
    {
        perror("Error opening the file");
        return;
    }

    char line[200];

    int i = 0;
    int cols;
    float table[MAXROWS][MAXCOLS] = {{}};
    char *names[] = {};


    while(fgets(line, sizeof(line), csv))
    {
        char *token;

        int j = 0;
        for (token = strtok(line, ","); token != NULL; token = strtok(NULL, ","))
        {
            if(i == 0)
            {
                names[j] = token;
            }

            table[i][j++] = atof(token);
        }
        i++;

        cols = j;

    }

    fclose(csv);

    linhas = &i;
    colunas = &cols;
    planilha = &table;
    nomes_linhas = names;

}