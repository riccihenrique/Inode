#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "structs.h"
#include "stack.h"
#include "queue.h"
#include "tadEstrutura.h"

int main()
{
    int num_blocos, dir_atual = 0;
    char comando[30], sair = 0;
    Stack pilha_diretorio; initStack(&pilha_diretorio);
    Queue blocos_livres;
    Bloco bloco[TF];
    Diretorio dir;
   

    printf("Digite a quantidade de blocos desejada: ");
    scanf("%d", &num_blocos);

    if(num_blocos < 1000)
    {
        num_blocos = 1000;
        printf("A quantidade minima é de 1000 blocos");
    }

	initQueue(&blocos_livres, bloco, num_blocos);
    inicializaBlocos(bloco, num_blocos);

    do
    {
        printf("%s", bloco[dir_atual].dir.nome);
        gets(comando);
    } while (!sair);
}
