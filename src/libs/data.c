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

    //Checking if the file is there
    if(csv == NULL)
    {
        perror("Error opening the file");
        return;
    }

    char line[200];

    int i = 0; //Rows number
    int cols; //Columns number
    float table[MAXROWS][MAXCOLS] = {{}}; //Table that is being read
    char* names[] = {}; //Name of the columns

    while(fgets(line, sizeof(line), csv))
    {
        char *token;

        int j = 0;
        for (token = strtok(line, ","); token != NULL; token = strtok(NULL, ","))
        {
            if(i == 0)
            {
                names[j] = token;
            } else table[i][j++] = atof(token);
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

void carrega_dados_url(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[])
{
    CURL *curl;
    CURLcode res;

    char file[100] = "\\tmp\\file.csv";

    FILE *fp;
 
    //Downloading the file
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, caminho_dos_dados);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        fp = fopen(file,"wb");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_cleanup(curl);
        fclose(fp);
    
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    //Reading the downloaded file as a local one.
    carrega_dados(file, linhas, colunas, planilha, nomes_linhas);
}