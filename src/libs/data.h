#if !defined(DATA_UNDEFINED)
#define DATA_UNDEFINED

#define MAXROWS 1000
#define MAXCOLS 1000

void carrega_dados(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[]);
void carrega_dados_url(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[]);


#endif // DATA_UNDEFINED
