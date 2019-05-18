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
    if(!strcmpi(comando, "exit"))
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
    	return 6;
    else
    if(!strcmpi(comando, "vi"))
    	return 7;
    else
        return -1;
}

int split(char comando[], char destino[], int ini)
{
	int i, j = 0;
	for(i = ini; comando[i] != ' ' && comando[i] != '\0'; i++)
            destino[j++] = comando[i];
    destino[j] = '\0';
    i++;
        
    return i;
}

int splitCaminho(char entrada[], char saida[], int ini)
{
    int i, j = 0;
	for(i = ini; entrada[i] != '/' && entrada[i] != '\0'; i++)
            saida[j++] = entrada[i];
    saida[j] = '\0';
    i++;
        
    return i;
}

int andaCaminho(char entrada[], Bloco bloco[], int dir)
{
	int i = 0, tl = 0;
	char entradas[30][30];
    dir = strstr(entrada, "/");
    
	if(dir <= 0)
        return -1;

	tl = 0;
	while(i < strlen(entrada)) // Cria a matriz com os diretorios
		i = splitCaminho(entrada,  entradas[tl++], i);
		
    i = 0;
	while(i < tl && dir != -1)
        dir = buscaDiretorio(bloco, entradas[i++], dir);

    return dir;
}

int main()
{
    int num_blocos, dir_atual = 0, i, j, pos, k, l, m, aux_tam;
    char comando[30], sair = 0, aux_comando[30], tamanho[30], ok, mais_blocos;
    Stack pilha_diretorio; initStack(&pilha_diretorio);
    Queue blocos_livres;
    Bloco bloco[TF];
    Diretorio dir;
    
    printf("Digite a quantidade de blocos desejada: ");
    scanf("%d", &num_blocos);
	
	system("cls");
	initQueue(&blocos_livres, bloco, num_blocos);
    inicializaBlocos(bloco, num_blocos);

    do
    {
        printf("%s>", bloco[dir_atual].dir.nome);
        fflush(stdin);
        gets(comando);
        
        i = split(comando, aux_comando, 0);

        switch (escolha(aux_comando))
        {
            case 0: //quit
                sair = 1;
            break;
            case 1: // touch
            	
            	i = split(comando, aux_comando, i);
                
                i = split(comando, tamanho, i);
                
                j = getBlocoLivre(&blocos_livres); // J se torna a posição do bloco do inode;

                strcpy(bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl].nome, aux_comando);
                bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl++].pos = j;

                i = atoi(tamanho); // A prtir daqui i é o tamanho do arquivo
				aux_tam = 0;
                do
                {
                    bloco[j].tipo = 'I';
                    bloco[j].ino = criaInode(i, "RWXRWXRWX");                    
                    
                    l = 0;

                    while(l < 5 && i >= 0) // Direto
                    {
                        pos = getBlocoLivre(&blocos_livres);

                        bloco[j].ino.pos[bloco[j].ino.tl++] = pos;
                        bloco[pos].tipo = 'A';
                        l++; i -= 10;
                    }
                    if(i >= 0)
                    {
                        l = 0;
                        while(l < 5 && i >= 0) //Indireto simples
                        {
                            pos = getBlocoLivre(&blocos_livres);

                            bloco[j].ino.pos[bloco[j].ino.is.pos[bloco[j].ino.pos[bloco[j].ino.is.tl++]]] = pos;
                            bloco[pos].tipo = 'A';
                            l++; i -= 10;
                        }
                        if(i >= 0)
                        {
                            l = 0;
                            while(l < 25 && i >= 0) //Indireto duplo
                            {
                                pos = getBlocoLivre(&blocos_livres);

                                bloco[j].ino.pos[bloco[j].ino.id.pos[bloco[j].ino.pos[bloco[j].ino.id.tl++]]] = pos;
                                bloco[pos].tipo = 'A';
                                l++; i -= 10;
                            }
                            if(i >= 0)
                            {
                                l = 0;
                                while(l < 124 && i >= 0) //Indireto triplo
                                {
                                    pos = getBlocoLivre(&blocos_livres);

                                    bloco[j].ino.pos[bloco[j].ino.it.pos[bloco[j].ino.pos[bloco[j].ino.it.tl++]]] = pos;
                                    bloco[pos].tipo = 'A';
                                    l++; i -= 10;
                                }

                                if(i - 10 >= 0)
                                {
                                    j = getBlocoLivre(&blocos_livres);
                                    bloco[j].ino.pos[bloco[j].ino.is.pos[bloco[j].ino.pos[bloco[j].ino.is.tl++]]] = j;
                                }
                            }
                        }
                    }    
                }while(i >= 0);

            break;
            case 2:
				i = split(comando, aux_comando, i);
				
				
				i = 0;
				
				while(i < bloco[dir_atual].dir.tl)
				{
					printf("%s ", bloco[dir_atual].dir.itens[i].nome);
					if(!strcmpi(aux_comando, ""))
					{
						
					}
					printf("\n");
					i++;
				}
            break;
            case 3:

            break;
            case 4: // cd
            	i = split(comando, aux_comando, i);
            	
                pos = andaCaminho(aux_comando, bloco, dir_atual);
                if(pos == -1)
                {
                	pos = buscaDiretorio(bloco, aux_comando, dir_atual);
                	if(pos == -1)
                		printf("Entrada invalida\n");
                	else
                		dir_atual = pos;
				}
                else 
				if(pos == -2)
                    pos = dir_atual;
                else 
                	dir_atual = pos;
            	
            break;
            case 5: //bad
                
                i = split(comando, tamanho, i);

                i = atoi(tamanho);
                
                if(i == 10)
                    exit(-1);
                
                BadBlock(&blocos_livres, i, bloco);
            break;
            case 6: // mkdir
                
                i = split(comando, aux_comando, i);

                if(buscaDiretorio(bloco, aux_comando, dir_atual) == -1)
                {
                    pos =  getBlocoLivre(&blocos_livres);
                    int npos = getBlocoLivre(&blocos_livres);
                    if(bloco[dir_atual].dir.tl == 9)
                    {
                        strcpy(bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl].nome, "");
                        bloco[dir_atual].dir.itens[bloco[dir_atual].dir.tl++].pos = npos;
                        
                        bloco[npos].tipo = 'A';
                        bloco[npos].dir = criaDiretorio(npos, "", dir_atual);
                    }
                    else
                        npos = dir_atual;

                    strcpy(bloco[npos].dir.itens[bloco[npos].dir.tl].nome, aux_comando);
                    bloco[npos].dir.itens[bloco[npos].dir.tl++].pos = pos;

                    bloco[pos].tipo = 'A';
                    bloco[pos].dir = criaDiretorio(pos, aux_comando, dir_atual);      
                }
                else
                    printf("Diretorio ja existente\n");
            break;
            case 7: // vi
            	i = split(comando, aux_comando, i);
            	
            	for(j = 0; j < bloco[dir_atual].dir.tl; j++)
            	{
            		if(!strcmpi(bloco[dir_atual].dir.itens[j].nome, aux_comando))
            		{
                        aux_tam = 0;
            			ok = 1;
            			pos = bloco[dir_atual].dir.itens[j].pos;
                        do // Caso haja mais blocos do que o inode pode arnazebar
                        {
            			    l = 0;
                            while(l < bloco[pos].ino.tl && ok)
                            {
                                if(bloco[bloco[pos].ino.pos[l]].tipo != 'B')
                                    l++;
                                else
                                {
                                    printf("Arquivo corrompido\n");
                                    ok = 0;
                                }
                            }
                            aux_tam += l; //Auxilia pra saber se o arquivo tem outro inode
                            if(ok)
                            {
                                l = 0;
                                while(l < bloco[pos].ino.is.tl && ok)
                                {							
                                    if(bloco[bloco[pos].ino.is.pos[l]].tipo != 'B')
                                        l++;
                                    else
                                    {
                                        printf("Arquivo corrompido\n");
                                        ok = 0;
                                    }
                                }
                                aux_tam += l;
                                if(ok)
                                {
                                    l = 0;
                                    while(l < bloco[pos].ino.id.tl && ok)
                                    {							
                                        if(bloco[bloco[pos].ino.id.pos[l]].tipo != 'B')
                                            l++;
                                        else
                                        {
                                            printf("Arquivo corrompido\n");
                                            ok = 0;
                                        }
                                    }
                                    aux_tam += l;
                                    if(ok)
                                    {
                                        l = 0;
                                        while(l < bloco[pos].ino.it.tl - 1 && ok)
                                        {							
                                            if(bloco[bloco[pos].ino.it.pos[l]].tipo != 'B')
                                                l++;
                                            else
                                            {
                                                printf("Arquivo corrompido\n");
                                                ok = 0;
                                            }
                                        }
                                        aux_tam += l;
                                        if(ok)
                                        {
                                            if(bloco[bloco[pos].ino.it.pos[l]].tipo == 'B')
                                            {
                                                printf("Arquivo corrompido\n");
                                                ok = 0;
                                            }
                                            else if(aux_tam + 1 < bloco[pos].ino.tamanho)
                                                pos = bloco[pos].ino.it.pos[bloco[pos].ino.it.tl];
                                            else
                                                pos = -1;
                                        }
                                    }
                                }
                            }
                        } while (ok && pos != -1);

						if(ok)
							printf("Arquivo visualizado\n");
            			break;
            		}
            	}
        		if(j == bloco[dir_atual].dir.tl)
                    printf("Arquivo inexistente\n");
            break;
            case -1:
            	printf("Command not found\n");
            default:
                break;
        }

    } while (!sair);
}
