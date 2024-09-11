#include "estruturas.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool verificarAluno(int matricula, char dpto[]) {
    for (int i = 0; i < max; i++) {
        if (formandos[i].matricula == matricula && strcmp(formandos[i].depto, dpto) == 0) {
            return true;
        }else if(formandos[i].matricula == matricula && strcmp(formandos[i].depto, dpto) != 0) {
            printf("Aluno encontrado, mas o curso está errado: %s é de %s mas está como %s", formandos[i].p.nome, formandos[i].depto, dpto);
            return false;
        }
    }
    printf("Aluno não encontrado\n");
    return false;
}

bool verificarProfessor(int codigo) {
    for (int i = 0; i < max; i++) {
        if (docentes[i].codigo == codigo) {
            return true;
        }
    }
    printf("Professor não encontrado\n");
    return false;
}

bool validarCPF(char cpf[]) {

    int dig1 = 0, dig2 = 0;

    if (strlen(cpf) != 14) {
        printf("Tamanho incorreto\n");
        return false;
    }

    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-')
    {
        printf("Pontuação incorreta\n");
        return false;
    }

    for(int i = 0; i < 14; i++){
        if(i == 3 || i == 7 || i == 11){
            continue;
        }
        if(!isdigit(cpf[i])){
            printf("Caracteres inválidos\n");
            return false;
        }
    }

    for (int i = 0, j = 10; i < 12; i++) {
        if (i == 3 || i == 7 || i == 11) {
            continue;
        }
        dig1 += (cpf[i] - '0') * j;
        j--;
    }

    dig1 = 11 - (dig1 % 11);

    if (dig1 >= 10) {
        dig1 = 0;
    }

    for (int i = 0, j = 11; i < 13; i++) {
        if (i == 3 || i == 7 || i == 11) {
            continue;
        }
        dig2 += (cpf[i] - '0') * j;
        j--;
    }

    dig2 = 11 - (dig2 % 11);

    if (dig2 >= 10) {
        dig2 = 0;
    }

    if (dig1 == cpf[12] - '0' && dig2 == cpf[13] - '0') {
        return true;
    }else{
        return false;
    }
    
}


void lerArquivoProfessor(Professor professores[]) {

    int numProfessores;

    FILE *arquivo;
    arquivo = fopen("professor.txt", "r");

    fscanf(arquivo, "%d", &numProfessores);
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);
    for (int i = 0; i < numProfessores; i++) {
        fgets(buffer, sizeof(buffer), arquivo);
        sscanf(buffer, "%d %s %d %[^\n]",
            &professores[i].codigo,
            professores[i].depto,
            &professores[i].p.idade,
            professores[i].p.nome);
    }

    fclose(arquivo);

    // printf("Professores lidos:\n");
    // for (int i = 0; i < numProfessores; i++) {
    //     printf("%s %d %d %s\n", 
    //         professores[i].p.nome, 
    //         professores[i].p.idade, 
    //         professores[i].codigo, 
    //         professores[i].depto);
    // }

}

void lerArquivoAluno(Aluno alunos[]) {

    int numAlunos;

    FILE *arquivo;
    arquivo = fopen("aluno.txt", "r");

    fscanf(arquivo, "%d", &numAlunos);
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);
    for (int i = 0; i < numAlunos; i++) {
        fgets(buffer, sizeof(buffer), arquivo);
        sscanf(buffer, "%d %d %s %d %[^\n]",
            &alunos[i].matricula,
            &alunos[i].ano,
            alunos[i].depto,
            &alunos[i].p.idade,
            alunos[i].p.nome);
    }

    fclose(arquivo);

    // printf("Alunos lidos:\n");
    // for (int i = 0; i < numAlunos; i++) {
    //     printf("%s %d %d %d %s\n", 
    //         alunos[i].p.nome, 
    //         alunos[i].p.idade, 
    //         alunos[i].ano, 
    //         alunos[i].matricula, 
    //         alunos[i].depto);
    // }

}

void lerArquivoTG(TG tgs[]) {

    char *arquivos[] = {"AMS", "ADS", "DSM", "CEX", "EMP", "LOG", "POL"};

    int numArquivos = sizeof(arquivos) / sizeof(arquivos[0]);

    FILE *arquivo;
    
    char buffer[256];

    for (int j = 0; j < numArquivos; j++) {
        char nomeArquivo[256];
        strcpy(nomeArquivo, "PI_");
        strcat(nomeArquivo, arquivos[j]);
        strcat(nomeArquivo, ".txt");
        arquivo = fopen(nomeArquivo, "r");

        int numArqTGs;

        fscanf(arquivo, "%d", &numArqTGs);
        fgets(buffer, sizeof(buffer), arquivo);
        for (int i = 0; i < numArqTGs; i++) {
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "%d %d %d %[^\n]",
                &tgs[qtdeTGs].codigo,
                &tgs[qtdeTGs].autor,
                &tgs[qtdeTGs].orientador,
                tgs[qtdeTGs].titulo);

            tgs[qtdeTGs].qtdeVotos = 0;

            if (!verificarAluno(tgs[qtdeTGs].autor, arquivos[j])) {
                printf("Erro no arquivo %s\n", nomeArquivo);
                exit(1);
            }
            if (!verificarProfessor(tgs[qtdeTGs].orientador)){
                printf("Erro no arquivo %s\n", nomeArquivo);
                exit(1);
            }
            
            
            
            qtdeTGs++;
        }

        fclose(arquivo);

    }

    // printf("TGs lidos:\n");
    // for (int i = 0; i < qtdeTGs; i++) {
    //     printf("%d %d %d %d %s\n", 
    //         tgs[i].codigo, 
    //         tgs[i].autor, 
    //         tgs[i].orientador, 
    //         tgs[i].qtdeVotos, 
    //         tgs[i].titulo);
    // }

}

void lerArquivoEleitores(Eleitor eleitores[]) {

    int numEleitores;

    FILE *arquivo;
    arquivo = fopen("comissao.txt", "r");

    fscanf(arquivo, "%d", &numEleitores);
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);
    for (int i = 0; i < numEleitores; i++) {
        fgets(buffer, sizeof(buffer), arquivo);
        sscanf(buffer, "%s",
            eleitores[i].cpf);
        eleitores[i].votou = false;
        eleitores[i].codigoTG = 0;

        if (!validarCPF(eleitores[i].cpf)) {
            printf("CPF %s inválido\n", eleitores[i].cpf);
            exit(1);
        }
    }

    fclose(arquivo);

    // printf("Eleitores lidos:\n");
    // for (int i = 0; i < numEleitores; i++) {
    //     printf("%s %d %d\n", 
    //         eleitores[i].cpf, 
    //         eleitores[i].votou, 
    //         eleitores[i].codigoTG);
    // }

}


