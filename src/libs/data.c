#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

//Loop through a string to find how many substrings can be found with '/' as delimiter
int get_length(char *url)
{
    char* token;
    char* string;
    char* tofree;
    int i = 0;

    string = strdup(url);

    if (string != NULL) 
    {
        tofree = string;

        while((token = strsep(&string, "/")) != NULL)
        {
            i++;
        }

        free(tofree);

        return i;
    } else return 0;
}

//Loop through a string, splitting and return the last one with '/' as delimiter
const char* get_name(char *url)
{
    char* token;
    char* string;
    char* tofree;

    string = strdup(url);

    if (string != NULL) 
    {
        int length = get_length(url);
        int i = 0;
        char* arr[length];
        tofree = string;

        while((token = strsep(&string, "/")) != NULL)
        {
            arr[i] = token;
            i++;
        }

        return arr[length - 1];

        free(tofree);
    } else return "";
}

void carrega_dados(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[])
{
    FILE * csv;
    csv = fopen(caminho_dos_dados, "r");

    //Checking if the file is there
    if(csv == NULL)
    {
        perror("Error opening the file");
        return;
    }

    int rows = 0; //Rows number
    int cols = 0; //Columns number
    int chr = getc(csv);

    while(chr != EOF)
    {
        if((chr == 44) && (rows == 0)){
            cols++;
        }
        if(chr == '\n'){
            rows++;
        }
        chr = getc(csv);
    }

    cols++;
    rewind(csv);

    float **table = (float **)planilha;
    //float table[rows][cols]; //Table that is being read
    //char *names[rows]; //Name of the columns
    int i = 0;
    char line[2048];

    while(fgets(line, sizeof(line), csv))
    {
        char *token;
        char *cp;
        
        cp = strdup(line);

        int j = 0;

        while((token = strsep(&cp, ",")) != NULL)
        {     
            if(j == 0)
            {
                char *copy;
                copy = strdup(token);

                nomes_linhas[i] = copy;
            } else table[i][j] = atof(token);
            //printf("%s  %d  %d\n", token, i, j);
            j++;
        }

        //if(i >= rows) i = 0;
        if(j >= cols) j = 0; i++;
    }

    fclose(csv);

    *linhas = rows;
    *colunas = cols;
}

void carrega_dados_url(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[])
{
    struct stat sb;

    if(stat("tmp/", &sb) == -1)
    {
        mkdir("tmp/", 0700);
    }

    char *name = get_name(caminho_dos_dados);
    char file[200] = "tmp/";
    strcat(file, name);

    FILE * fp; 

    CURL *curl;
    CURLcode res;
    //Downloading the file
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(file, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, caminho_dos_dados);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
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
    //carrega_dados(file, linhas, colunas, planilha, nomes_linhas);
}

main()
{
    int linhas;
    int colunas;
    float **table;

    table = malloc(1000 * sizeof(*table));

    for(int i = 0; i < 1000; i++)
    {
        table[i] = malloc(1000 * sizeof(*table[i]));
    }

    char *nomes[1000];

    /*carrega_dados("../../resources/BRICS_PIBPerCapita.csv", &linhas, &colunas, table, nomes);
    printf("%s", nomes[0]);*/
    carrega_dados_url("http://www.ime.usp.br/~kon/tmp/BRICS_TaxaDeFertilidade.csv", &linhas, &colunas, table, nomes);

    return 0;
}