
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.c"

//Protótipos
void Menu1();
void Menu2();
bool verificarCPF(char cpf[]);
bool verificarTG(int codigo);
void votar(char cpf[], int codigoTG);
void suspenderVotacao();
void concluirVotacao();
void continuarVotacao();


bool verificarCPF(char cpf[]) {

    if(!validarCPF(cpf)){
        printf("CPF inválido\n");
        return false;
    }

    for (int i = 0; i < max; i++) {
        if (strcmp(comissao[i].cpf, cpf) == 0 && comissao[i].votou == true) {
            printf("Eleitor %s já votou\n", cpf);
            return false;
        }else if(strcmp(comissao[i].cpf, cpf) == 0 && comissao[i].votou == false){
            return true;
        }
    }

    printf("CPF não encontrado \n");
    return false;
}

bool verificarTG(int codigo) {
    for (int i = 0; i < max; i++) {
        if (listaTGs[i].codigo == codigo) {
            return true;
        }
    }
    printf("TG não encontrado\n");
    return false;
}

void votar(char cpf[], int codigoTG) {
    for (int i = 0; i < max; i++) {
        if (strcmp(comissao[i].cpf, cpf) == 0) {
            comissao[i].votou = true;
            comissao[i].codigoTG = codigoTG;
        }
    }
    for (int j = 0; j < max; j++) {
        if (listaTGs[j].codigo == codigoTG) {
            listaTGs[j].qtdeVotos++;
            printf("Voto computado\n");
        }
    }
    
    qtdeEleitores++;

}

void suspenderVotacao() {
    FILE *file = fopen("parcial.txt", "w");

    fprintf(file, "%d\n", qtdeEleitores);
    for (int i = 0; i < max; i++) {
        if (comissao[i].votou) {
            fprintf(file, "%s %d\n", comissao[i].cpf, comissao[i].codigoTG);
        }
    }

    fclose(file);
    printf("Votação suspensa. Dados salvos em parcial.txt\n");
    exit(0);
}

void concluirVotacao() {
    FILE *file = fopen("resultado.txt", "w");

    int maior = 0;
    int vencedor = -1;
    
    for(int i = 0; i < qtdeTGs; i++){
        if(listaTGs[i].qtdeVotos > maior){
            maior = listaTGs[i].qtdeVotos;
        }
    }

    
    

    fprintf(file, "PIs vencedores:\n");
    for(int i = 0; i < qtdeTGs; i++){
        if(listaTGs[i].qtdeVotos == maior){
            int aluno;

            for (int j = 0; j < max; j++){
                if (formandos[j].matricula == listaTGs[i].autor){
                    aluno = j;
                    break;
                }
            }
            
            int orientador;

            for (int j = 0; j < max; j++){
                if (docentes[j].codigo == listaTGs[i].orientador){
                    orientador = j;
                    break;
                }
            }

            fprintf(file,"\nCódigo: %d\n", listaTGs[i].codigo);
            fprintf(file,"Título: %s\n", listaTGs[i].titulo);
            fprintf(file,"Aluno: %s\n", formandos[aluno].p.nome);
            fprintf(file,"Curso aluno: %s\n", formandos[aluno].depto);
            fprintf(file,"Orientador: %s\n", docentes[orientador].p.nome);
            fprintf(file,"Curso orientador: %s\n", docentes[orientador].depto);
            fprintf(file,"Votos: %d\n", listaTGs[i].qtdeVotos);

        }
    }
    

    fprintf(file, "\nEleitores presentes:\n");
    for (int i = 0; i < max; i++) {
        if (comissao[i].votou) {
            fprintf(file, "%s\n", comissao[i].cpf);
        }
    }

    fprintf(file, "\nEleitores ausentes:\n");
    for (int i = 0; i < max; i++) {
        if (!comissao[i].votou) {
            fprintf(file, "%s\n", comissao[i].cpf);
        }
    }

    fclose(file);
    printf("Votação concluída. Resultado salvo em resultado.txt\n");
    exit(0);
}

void continuarVotacao() {
    FILE *file = fopen("parcial.txt", "r");
    if (file == NULL) {
        printf("Arquivo parcial.txt não encontrado\n");
        Menu1();
    }

    int aux;

    fscanf(file, "%d", &aux);

    printf("Quantidade de Eleitores: %d\n", aux);
    
    char buffer[256];

    char cpf[15];
    int codTG;

    fgets(buffer, sizeof(buffer), file);
    
    for (int i = 0; i < aux; i++) {
        fgets(buffer, sizeof(buffer), file);
        
        sscanf(buffer, "%s %d", cpf, &codTG);

        for (int j = 0; j < max; j++){
            if(strcmp(comissao[j].cpf, cpf) == 0){
                votar(cpf, codTG);
            }
        }
    }

    fclose(file);

    qtdeEleitores = aux;

    printf("Votação continuada\n");
    Menu2();
}

void Menu2(){
    char opcao2;
    printf("MENU2:\n");
        printf("a) Entrar com voto\n");
        printf("b) Suspender votação\n");
        printf("c) Concluir votação\n");
        printf("Digite a opção: ");

        scanf(" %c", &opcao2);

        while (opcao2 != 'a' && opcao2 != 'A' && opcao2 != 'b' && opcao2 != 'B' && opcao2 != 'c' && opcao2 != 'C'){
            printf("Opção inválida\n");
            printf("Digite a opção: ");
            scanf(" %c", &opcao2);
        }

        if (opcao2 == 'a' || opcao2 == 'A'){
            printf("Digite o CPF do eleitor: ");
            char cpf[15];
            scanf("%s", cpf);

            while (!verificarCPF(cpf)){
                printf("Digite o CPF do eleitor: ");
                scanf("%s", cpf);
            }

            printf("Digite o código do TG: ");
            int codigoTG;
            scanf("%d", &codigoTG);

            while (!verificarTG(codigoTG)){
                printf("Digite o código do TG: ");
                scanf("%d", &codigoTG);
            }
            
            votar(cpf, codigoTG);

            Menu2();

        }

        if (opcao2 == 'b' || opcao2 == 'B'){
            suspenderVotacao();
        }
        
        if (opcao2 == 'c' || opcao2 == 'C'){
            concluirVotacao();
        }
}

void Menu1(){
    char opcao;

    printf("MENU1:\n");
    printf("a) Iniciar nova votação\n");
    printf("b) Continuar votação gravada\n");
    printf("Digite a opção: ");

    scanf("%c", &opcao);

    while (opcao != 'a' && opcao != 'A' && opcao != 'b' && opcao != 'B'){
        printf("Opção inválida\n");
        printf("Digite a opção: ");
        scanf("%c", &opcao);
    }

    if(opcao == 'a' || opcao == 'A'){
        
        Menu2();

    }else if(opcao == 'b' || opcao == 'B'){
        continuarVotacao();
    }
}
