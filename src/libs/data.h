#if !defined(DATA_UNDEFINED)
#define DATA_UNDEFINED

#define MAXROWS 1000
#define MAXCOLS 1000

/*
 * Function to load a CSV from a local path (param caminho_dos_dados).
 * It returns the lines number, columns number, the table and the column names 
 * from the respective pointers: linhas, colunas, planilha, nomes_linhas
 */

void carrega_dados(char *caminho_dos_dados, int *linhas, 
                        int *colunas, void *planilha, char *nomes_linhas[]);
char* print_info();
void printi();


#endif // DATA_UNDEFINED
