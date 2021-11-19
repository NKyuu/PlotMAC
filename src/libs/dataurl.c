#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
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

        free(tofree);
        return arr[length - 1];
    } else return "";
}

void load(char *caminho_dos_dados, int *linhas, 
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

        if(j >= cols) j = 0; i++;
    }

    fclose(csv);

    *linhas = rows;
    *colunas = cols;
}

void carrega_dados(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[])
{
    struct stat sb;

    if(stat("downloads/", &sb) == -1)
    {
        mkdir("downloads/", 0700);
    }

    const char *name = get_name(caminho_dos_dados);
    char file[200] = "downloads/";
    strcat(file, name);

    FILE * fp; 

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    //Downloading the file
    curl = curl_easy_init();
    if(curl) {
        fp = fopen(file, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, caminho_dos_dados);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    
        fclose(fp);
        /* always cleanup */
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    //Reading the downloaded file as a local one.
    load(file, linhas, colunas, planilha, nomes_linhas);
}

char* print_info()
{
    char *exs[6] = {
        "http://www.ime.usp.br/~kon/tmp/BRICS_PIBPerCapita.csv",
        "https://www.ime.usp.br/~kon/tmp/BRICS_ExportacaoTecnologica.csv",
        "https://www.ime.usp.br/~kon/tmp/BRICS_ExpectativaDeVida.csv",
        "https://www.ime.usp.br/~kon/tmp/BRICS_MortalidadeInfantil.csv",
        "https://www.ime.usp.br/~kon/tmp/BRICS_EmissaoDeCO2PerCapita.csv",
        "https://www.ime.usp.br/~kon/tmp/BRICS_TaxaDeFertilidade.csv"
    };

    srand(time(NULL));
    return exs[rand() % 6];
}

void printi()
{
    printf("<path> is a URL to download the file\n");
}

/*
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

        /*
        *
        * carrega_dados("../../resources/BRICS_PIBPerCapita.csv", &linhas, &colunas, table, nomes);
        * printf("%s", nomes[0]);
        * 
        
        carrega_dados_url("https://www.ime.usp.br/~kon/tmp/BRICS_TaxaDeFertilidade.csv", &linhas, &colunas, table, nomes);
        printf("%s", nomes[0]);
        return 0;
    }
*/