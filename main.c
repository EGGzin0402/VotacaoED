
#include <stdio.h>
#include <stdlib.h>
#include "votacao.c"

void main(){
    
    lerArquivoProfessor(docentes);
    lerArquivoAluno(formandos);
    lerArquivoTG(listaTGs);
    lerArquivoEleitores(comissao);
    
    Menu1();

}

