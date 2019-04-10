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




char escolha(char comando[])
{
    
    if(!strcmpi(comando, "quit"))
        return 0;
    else
	if(!strcmpi(comando, "touch"))
        return 1;
    else
	if(!strcmpi(comando, "ls"))
        return 2;
    else 
	if(!strcmpi(comando, "df"))
        return 3;
    else 
	if(!strcmpi(comando, "cd"))
        return 4;
    else 
	if(!strcmpi(comando, "bad"))
        return 5;
    else
    if(!strcmpi(comando, "mkdir"))
    	reuturn 6;
    else
        return -1;
}

int main()
{
    int num_blocos, dir_atual = 0, i, j, pos;
    char comando[30], sair = 0, aux_comando[30], tamanho[30];
    Stack pilha_diretorio; initStack(&pilha_diretorio);
    Queue blocos_livres;
    Bloco bloco[TF];
    Diretorio dir;
   

    printf("Digite a quantidade de blocos desejada: ");
    scanf("%d", &num_blocos);

    if(num_blocos < 1000)
    {
        num_blocos = 1000;
        printf("A quantidade minima é de 1000 blocos\n");
    }
	
	_sleep(2300);
	system("cls");
	initQueue(&blocos_livres, bloco, num_blocos);
    inicializaBlocos(bloco, num_blocos);

    do
    {
        printf("%s>", bloco[dir_atual].dir.nome);
        fflush(stdin);
        gets(comando);
        
        for(i = 0; comando[i] != ' ' && comando[i] != '\0'; i++)
            aux_comando[i] = comando[i];
        aux_comando[i++] = '\0';

        switch (escolha(aux_comando))
        {
            case 0:
                sair = 1;
            break;
            case 1:
            	j = 0;
                for(j = 0; comando[i] != ' '; i++)
                    aux_comando[j++] = comando[i];
                
                aux_comando[j] = '\0';
                
                for(j = 0, i++; comando[i] != '\0'; i++)
                    tamanho[j++] = comando[i];
                
                tamanho[j] = '\0';
                
                j = getBlocoLivre(blocos_livres); // J se torna a posição do bloco do inode;

                strcpy(bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl].nome, aux_comando);
                bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl++].pos = j;

                i = atoi(tamanho); // A prtir daqui i é o tamanho do arquivo

                bloco[j].tipo = 'I';
                bloco[j].ino = criaInode(i, "RWXRWXRWX");

                int l = 0;

                while(l < 5 && i >= 0) // Direto
                {
                    pos = getBlocoLivre(blocos_livres);

                    bloco[j].ino.pos[bloco[j].ino.tl++] = pos;
                    bloco[pos].tipo = 'A';
                    l++; i -= 10;
                }

                if(i >= 0)
                {
                    l = 0;
                    while(l < 5 && i >= 0) //Indireto simples
                    {
                        pos = getBlocoLivre(blocos_livres);

                        bloco[j].ino.pos[bloco[j].ino.is.pos[bloco[j].ino.pos[bloco[j].ino.is.tl++]]] = pos;
                        bloco[pos].tipo = 'A';
                        l++; i -= 10;
                    }
                    if(i >= 0)
                    {
                        l = 0;
                        while(l < 25 && i >= 0) //Indireto duplo
                        {
                            pos = getBlocoLivre(blocos_livres);

                            bloco[j].ino.pos[bloco[j].ino.is.pos[bloco[j].ino.pos[bloco[j].ino.is.tl++]]] = pos;
                            bloco[pos].tipo = 'A';
                            l++; i -= 10;
                        }

                        if(i >= 0)
                        {
                            l = 0;
                            while(l < 125 && i >= 0) //Indireto triplo
                            {
                                pos = getBlocoLivre(blocos_livres);

                                bloco[j].ino.pos[bloco[j].ino.is.pos[bloco[j].ino.pos[bloco[j].ino.is.tl++]]] = pos;
                                bloco[pos].tipo = 'A';
                                l++; i -= 10;
                            }
                        }
                    }
                }


            break;
            case 2:

            break;
            case 3:

            break;
            case 5:
                
                j = 0;
                for(; comando[i] != '\0'; i++)
                    tamanho[j++] = comando[i];

                tamanho[j] = '\0';

                i = atoi(tamanho);
                
                if(i == 0)
                    exit(-1);
                
                BadBlock(blocos_livres, i, bloco);
            break;
            case 6:
                
                j = 0;
                for(; comando[i] != '\0'; i++)
                    aux_comando[j++] = comando[i];

                aux_comando[j] = '\0';
                pos =  getBlocoLivre(blocos_livres);
                strcpy(bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl].nome, aux_comando);
                bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl++].pos = pos;

                bloco[pos].tipo = 'A';
                bloco[pos].dir = criaDiretorio(pos, aux_comando, dir_atual, 0);

            break;
            case -1:
            	printf("Command not found\n");
            default:
                break;
        }

    } while (!sair);
}
