
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define max 50
#define maxNome 60
#define maxSigla 10

typedef struct pessoa {
    char nome[maxNome];
    int idade;
} Pessoa;

typedef struct professor {
    Pessoa p;
    int codigo;
    char depto[maxSigla];
} Professor;

typedef struct aluno {
    Pessoa p;
    int matricula;
    int ano;
    char depto[maxSigla];
} Aluno;

typedef struct tg {
    int codigo;
    int autor;
    int orientador;
    char titulo[maxNome];
    int qtdeVotos;
} TG;

typedef struct eleitor {
    char cpf[15];
    bool votou;
    int codigoTG;
} Eleitor;


Professor docentes[max];
int qtdeDocentes;
Aluno formandos[max];
int qtdeFormandos;
TG listaTGs[max];
int qtdeTGs = 0;
Eleitor comissao[max];
int qtdeEleitores;