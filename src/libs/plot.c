#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "graphic.h"

int *colunas = 1000;
char* title = "";
char* x = "";
char* y = "";
char** col_names;

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
    col_names = nomes_linhas;
}

// char* cmd_title()
// {
//     char cmd[200] = "set title\"";
//     strcat(cmd, title);
//     strcat(cmd, "\"");
//     return cmd;
// }

// char* cmd_xlabel()
// {
//     char cmd[200] = "set xlabel\"";
//     strcat(cmd, x);
//     strcat(cmd, "\"");
//     return cmd;
// }

// char* cmd_ylabel()
// {
//     char cmd[200] = "set ylabel\"";
//     strcat(cmd, y);
//     strcat(cmd, "\"");
//     return cmd;
// }

// char* cmd_output()
// {
//     char cmd[200] = "set output\"";
//     strcat(cmd, title);
//     strcat(cmd, ".png\"");
//     return cmd;
// }

// char* cmd_plot()
// {
//     char cmd[200] = "plot \"tmp/";
//     strcat(cmd, title);
//     strcat(cmd, ".tmp\"");
//     return cmd;
// }

// const char** cmds()
// {
//     int t = sizeof(col_names)/sizeof(col_names[0]);
//     char *gnucmds[7+t];
//     gnucmds[0] = "set style data lines";
//     gnucmds[1] = "set term postscript color";

//     char cmd_title[200] = "set title\"";
//     strcat(cmd_title, title);
//     strcat(cmd_title, "\"");

//     gnucmds[2] = cmd_title;

//     char cmd_xlabel[200] = "set xlabel\"";
//     strcat(cmd_xlabel, x);
//     strcat(cmd_xlabel, "\"");

//     gnucmds[3] = cmd_xlabel;

//     char cmd_ylabel[200] = "set ylabel\"";
//     strcat(cmd_ylabel, y);
//     strcat(cmd_ylabel, "\"");

//     gnucmds[4] = cmd_ylabel;

//     char cmd_output[200] = "set output\"";
//     strcat(cmd_output, title);
//     strcat(cmd_output, ".png\"");

//     gnucmds[5] = cmd_output;

//     char cmd_plot[200] = "plot \"tmp/";
//     strcat(cmd_plot, title);
//     strcat(cmd_plot, ".tmp\"");

//     for(int i = 0; i < t; i++)
//     {
//         char cmd_line[200] = "set label ";
//         char str[20];
//         itoa(i+1, str, 10);
//         strcat(cmd_line, str);
//         strcat(cmd_line, " \'");
//         strcat(cmd_line, col_names[i]);
//         strcat(cmd_line, "\'");
//         gnucmds[6+i] = cmd_line;
//     }

//     gnucmds[7+t-1] = cmd_plot;

//     return gnucmds;
// }

void desenha_grafico(int linhas, int colunas, float planilha[][colunas])
{
    FILE * fp;

    int t = colunas;
    char *gnucmds[11+t];
    gnucmds[0] = "set style data linespoints";
    gnucmds[1] = "set term postscript color";

    char cmd_title[200] = "set title \'";
    strcat(cmd_title, title);
    strcat(cmd_title, "\'");

    gnucmds[2] = cmd_title;

    char cmd_xlabel[200] = "set xlabel \'";
    strcat(cmd_xlabel, x);
    strcat(cmd_xlabel, "\'");

    gnucmds[3] = cmd_xlabel;

    char cmd_ylabel[200] = "set ylabel \'";
    strcat(cmd_ylabel, y);
    strcat(cmd_ylabel, "\'");

    gnucmds[4] = cmd_ylabel;

    gnucmds[5] = "set datafile separator whitespace";

    for(int i = 0; i < t-1; i++)
    {
        char cmd_line[200] = "set label ";
        char str[20];
        sprintf(str, "%d", i+1);
        strcat(cmd_line, str);
        strcat(cmd_line, " \'");
        strcat(cmd_line, col_names[i]);
        strcat(cmd_line, "\'");
        gnucmds[6+i] = strdup(cmd_line);
    }

    gnucmds[6+t] = "set terminal png";

    char cmd_output[200] = "set output \'";
    strcat(cmd_output, title);
    strcat(cmd_output, ".png\'");

    gnucmds[7+t] = cmd_output;

    char cmd_plot[500] = "plot \'tmp/";
    strcat(cmd_plot, title);
    strcat(cmd_plot, ".dat\'");

    for(int i = 0; i < t-1; i++)
    {
        printf("%d\n", i);
        strcat(cmd_plot, " u 1:");
        char str[50];
        sprintf(str, "%d", i+2);
        strcat(cmd_plot, str);
        strcat(cmd_plot, " w lp t \'");
        strcat(cmd_plot, col_names[i]);
        strcat(cmd_plot, "\'");

        if(i+1 < t-1) 
        {
            strcat(cmd_plot, ",");
            strcat(cmd_plot, " \'tmp/");
            strcat(cmd_plot, title);
            strcat(cmd_plot, ".dat\'");
        }
    }

    gnucmds[8+t] = "set xrange [0:6]";
    gnucmds[9+t] = cmd_plot;
    gnucmds[10+t] = "set output";

    struct stat sb;

    if(stat("tmp/", &sb) == -1)
    {
        mkdir("tmp/", 0700);
    }

    char file[200] = "tmp/";
    strcat(file, title);
    strcat(file, ".dat");


    fp = fopen(file, "wb");

    for(int j = 0; j < colunas; j++)
    {
        for(int i = 0; i < linhas; i++)
        {
            fprintf(fp, "%f ", planilha[i][j]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
    FILE * gnupipe;
    char gnu[100] = "tmp/";
    strcat(gnu, title);
    strcat(gnu, ".plt");

    gnupipe = fopen(gnu, "wb");

    for(int i = 0; i < 11+t; i++)
        fprintf(gnupipe, "%s\n", gnucmds[i]);

    fclose(gnupipe);
}

void gnuplot(char *title, char *xlabel, char *ylabel, char *lines_names[], int rows, int cols, void *table)
{
    float **ftable = (float **)table;
    define_titulo(title);
    define_rotulo_x(xlabel);
    define_rotulo_y(ylabel);
    define_nomes_linhas(lines_names);
    desenha_grafico(rows, cols, ftable);

    char gnu[100] = "tmp/";
    strcat(gnu, title);
    strcat(gnu, ".plt");

    char *args[] = {"gnuplot", gnu, NULL};

    printf("%s", gnu);
    
    errno = 0;
    if (execvp(*args, args) == -1) 
    {
        if (errno == EACCES)
            printf("[ERROR] permission is denied for a file\n");
        else
            perror("execvp");
    }
}

int main()
{
    char* lines_names[] = {"a", "b"};
    float table[][2] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    gnuplot("teste", "x", "y", lines_names, 5, 2, table);

    return 0;
}