using namespace std;
#include <iostream>
#include<stdio.h>
#include <conio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define NOMESARQDIR 16
#define ITENSDIR

#include"tadPilha.h"
#include"tadLista.h"
#include"tadEstrutura.h"

void verificaArquivo(Bloco b, Bloco blocos_disco[], char nome_arq[], bool *flag, int *posb)
{
    int pos, i;
    while(b.tipo != 'L' && b.tipo != 'B' && !(*flag))
    {
        if(b.tipo == 'D')
        {
            pos = b.ino.posi[0];
            b = blocos_disco[pos];
            verificaArquivo(b, blocos_disco, nome_arq, &(*flag), &(*posb));
        }
        else
            if(b.tipo == 'I' || b.tipo == 'A')
            {
                i = 0;
                while(i < b.dir.tl && !(*flag))
                {
                    if(stricmp(b.dir.itens[i].nomeitem, nome_arq) == 0)
                    {
                        (*posb) = b.dir.itens[i].posi;
                        (*flag) = true;
                    }
                    i++;
                }
                break;
            }
            else
                break;
    }
}

char findInstruction(char *inst)
{
    char aux[10];
    int i,j;
    aux[0] = '\0';

    for(i=0,j=0; i<strlen(inst) && inst[i]!=' '; i++)
        aux[j++] = tolower(inst[i]);
    aux[j] = '\0';
    if(i < strlen(inst))
        i++;
    for(j=0; j<strlen(inst); j++,i++)
        inst[j]=inst[i];
    inst[j] = '\0';
    if(!strcmp("chmod",aux))
        return 1;
    else if(!strcmp("vi",aux))
        return 2;
    else if(!strcmp("ls",aux))
        return 3;
    else if(!strcmp("mkdir",aux))
        return 4;
    else if(!strcmp("rmdir",aux))
        return 5;
    else if(!strcmp("rm",aux))
        return 6;
    else if(!strcmp("cd",aux))
        return 7;
    else if(!strcmp("link",aux))
        return 8;
    else if(!strcmp("unlink",aux))
        return 9;
    else if(!strcmp("bad",aux))
        return 10;
    else if(!strcmp("touch",aux))
        return 11;
    else if(!strcmp("df",aux))
        return 12;
    else if(!strcmp("quit",aux))
        return 13;
    else
        return 0;
}

int buscaDiretorio(Bloco *blocos_disco, Diretorio dir, char nomedir[])
{
    int i=0;
    char achou = 0;
    while(i<dir.tl && !achou)
    {
        if(!strcmp(dir.itens[i].nomeitem,nomedir))
        {
            if(blocos_disco[dir.itens[i].posi].tipo == 'D')
                achou = 1;
        }
        i++;
    }
    if(achou)
        return i;
    return -1;
}

int contaBlocosOcupados(Diretorio raiz, Bloco blocos_disco[], int j)
{
    int qtd=j, posi, p1, k=0;
    bool achou=false;
    for(int i = 0; i < raiz.tl; i++)
    {
        p1 = raiz.itens[i].posi;
        if(blocos_disco[p1].tipo != 'L' && blocos_disco[p1].tipo != 'B')
        {
            if(blocos_disco[p1].tipo == 'D')
            {
                j+=2;
                posi = blocos_disco[p1].ino.posi[0];
                qtd = contaBlocosOcupados(blocos_disco[posi].dir, blocos_disco, j);
            }
            else
                if(blocos_disco[p1].tipo == 'I')
                {
                   qtd++;
                   achou = false;
                    for(k = 0; k < blocos_disco[p1].ino.tl && blocos_disco[blocos_disco[p1].ino.posi[k]].tipo != 'B' && !achou; k++)
                    {
                        if(blocos_disco[blocos_disco[p1].ino.posi[k]].tipo == 'A')
                            qtd++;
                        else
                            if(blocos_disco[blocos_disco[p1].ino.posi[k]].tipo == 'L')
                            {
                                qtd++;
                                achou = true;
                            }
                    }

                    if(!achou && k == blocos_disco[p1].ino.tl)
                    {
                        achou = false;
                        for(k = 0; k < blocos_disco[p1].ino.is.tl && blocos_disco[blocos_disco[p1].ino.is.posi[k]].tipo != 'B' && !achou; k++)
                        {
                            if(blocos_disco[blocos_disco[p1].ino.is.posi[k]].tipo == 'A')
                                qtd++;
                            else
                                if(blocos_disco[blocos_disco[p1].ino.is.posi[k]].tipo == 'L')
                                {
                                    qtd++;
                                    achou = true;
                                }
                        }

                        if(!achou && k == blocos_disco[p1].ino.is.tl)
                        {
                            achou = false;
                            for(k = 0; k < blocos_disco[p1].ino.id.tl && blocos_disco[blocos_disco[p1].ino.id.posi[k]].tipo != 'B' && !achou; k++)
                            {
                                if(blocos_disco[blocos_disco[p1].ino.id.posi[k]].tipo == 'A')
                                    qtd++;
                                else
                                    if(blocos_disco[blocos_disco[p1].ino.id.posi[k]].tipo == 'L') // blocos_disco[].tipo
                                    {
                                        qtd++;
                                        achou = true;
                                    }
                            }

                            if(!achou && k == blocos_disco[p1].ino.id.tl)
                            {
                                achou = false;
                                for(k = 0; k < blocos_disco[p1].ino.it.tl && blocos_disco[blocos_disco[p1].ino.it.posi[k]].tipo != 'B' && !achou; k++)
                                {
                                    if(blocos_disco[blocos_disco[p1].ino.it.posi[k]].tipo == 'A')
                                        qtd++;
                                    else
                                        if(blocos_disco[blocos_disco[p1].ino.it.posi[k]].tipo == 'L')
                                        {
                                            qtd++;
                                            achou = true;
                                        }
                                }
                            }

                        }
                    }

                }
        }
    }
    return qtd;
}

int buscaArquivo(Bloco *blocos_disco, Diretorio dir, char nomearq[])
{
    int i=0;
    char achou = 0;
    while(i<dir.tl && !achou)
    {
        if(!strcmp(dir.itens[i].nomeitem,nomearq))
        {
            if(blocos_disco[dir.itens[i].posi].tipo == 'I')
                achou = 1;
        }
        i++;
    }
    if(achou)
        return i;
    return -1;
}

void remanejaItensDir(Diretorio dir, int pos)
{
    while(pos < 9)
    {
        strcpy(dir.itens[pos].nomeitem,dir.itens[pos+1].nomeitem);
        dir.itens[pos].posi = dir.itens[pos+1].posi;
    }
}

int numeroBlocosLivres(Bloco blocos_disco[], int n_blocos)
{
    int i,j;
    for(i = 0,j = 0; i < n_blocos; i++)
        if(blocos_disco[i].tipo == 'F')
            j++;
}

int main()
{
    Diretorio raiz;
    strcpy(raiz.nome, "/raiz");
    raiz.tl=0;



    int n_blocos = 1000,tl=0, i, j, tam_bloco = 10, k;
    char num_blocos[2], caracter, navegacao[1000], comando[30],res,sair=0;
    bool exit, stop;
    printf("Numero de blocos desejados para a simulacao:");
    fflush(stdin);
    gets(num_blocos);
    if(strlen(num_blocos) > 0)
    {
        n_blocos = atoi(num_blocos);
        if(n_blocos < 100)
        {
            n_blocos = 1000;
            puts("Definido o numero padrao: 1000");
        }
    }
    else
    {
        n_blocos = 1000;
        puts("Definido o numero padrao: 1000");
    }

    Bloco blocos_disco[n_blocos];
    Diretorio dir_atual;

    Lista lista_blivres;
    inicializaLista(&lista_blivres, n_blocos);
    inicializaBlocos(blocos_disco, n_blocos, &lista_blivres, &raiz);
    char nomearquivo[NOMESARQDIR],bytes[8];
    int tamanho, pos,pos_bloco_livre,pos_no_dir,pos_bloco;
    strcpy(navegacao,"");
    do
    {
        puts(navegacao);
        fflush(stdin);
        gets(comando);
        res = findInstruction(comando);
        switch(res)
        {
            case 1: //chmod
            break;
            case 2: //vi
                printf("\nDigite o nome do Arquivo: ");
                fflush(stdin);
                gets(navegacao);

                char inicio[7], aux[80];
                for(i = 0; i < 6; i++)
                {
                    inicio[i] = navegacao[i];
                    aux[i] = navegacao[i];
                }
                inicio[i] = '\0';
                if(stricmp(inicio, "/raiz/") == 0)
                {
                    int x, cont = 0; stop = false;
                    Bloco b;
                    b = blocos_disco[raiz.itens[0].posi];
                    int z = 6;
                    while(i < strlen(navegacao) && !stop)
                    {
                        x= i - 1;
                        for(; i < strlen(navegacao) && navegacao[i] != '/'; i++, z++)
                            aux[z] = navegacao[i];
                        aux[z] = '\0'; i++;

                        if(i >= strlen(navegacao))
                        {
                            stop= true; exit = false;
                            if(cont == 0)
                            {
                                for(k = 0; k < raiz.tl && !exit; k++)
                                    if(stricmp(raiz.itens[k].nomeitem, aux) == 0)
                                    {
                                        pos = k;
                                        exit = true;
                                    }
                            }
                            if(exit || cont > 0)
                            {
                                if(cont == 0)
                                    b = blocos_disco[raiz.itens[pos].posi];

                                if(b.tipo == 'B')
                                    printf("\nErro: Arquivo ou Diretorio defeituoso!");
                                else
                                {
                                    aux[0] = '/';
                                    for(k = x + 1, j = 1; k < strlen(navegacao); k ++, j++)
                                        aux[j] = navegacao[k];
                                    aux[j] = '\0';

                                    exit = false; k = -1;
                                    verificaArquivo(b, blocos_disco, aux, &exit, &k);
                                    if(k != -1)
                                    {
                                        b = blocos_disco[k]; exit = false;
                                        Bloco b2; int erros = 0;
                                        for(j = 0; j < b.ino.tl && !exit; j++)
                                        {
                                            b2 = blocos_disco[b.ino.posi[j]];
                                            //printf("\n%c\n", b2.tipo);
                                            if(b2.tipo == 'B' || b2.tipo == 'L')
                                            {
                                                if(b2.tipo == 'B')
                                                    erros++;
                                                exit =  true;
                                            }
                                        }
                                        if(exit)
                                        {
                                            if(erros > 0)
                                                printf("\nErro: Arquivo ou Diretorio defeituoso!");
                                            else
                                                printf("\nOk: Arquivo ou Diretorio operando!");
                                        }
                                        else
                                        {
                                            if(b.ino.is.tl > 0)
                                            {
                                                b = blocos_disco[k]; exit = false;
                                                Bloco b2; int erros = 0;
                                                for(j = 0; j < b.ino.is.tl && !exit; j++)
                                                {
                                                    b2 = blocos_disco[b.ino.is.posi[j]];
                                                    if(b2.tipo == 'B' || b2.tipo == 'L')
                                                    {
                                                        if(b2.tipo == 'B')
                                                            erros++;
                                                        exit =  true;
                                                    }
                                                }
                                            }
                                            if(exit)
                                            {
                                                if(erros > 0)
                                                    printf("\nErro: Arquivo ou Diretorio defeituoso!");
                                                else
                                                    printf("\nOk: Arquivo ou Diretorio operando!");
                                            }
                                            else
                                            {
                                                if(b.ino.id.tl > 0)
                                                {
                                                    b = blocos_disco[k]; exit = false;
                                                    Bloco b2; int erros = 0;
                                                    for(j = 0; j < b.ino.id.tl && !exit; j++)
                                                    {
                                                        b2 = blocos_disco[b.ino.id.posi[j]];
                                                        if(b2.tipo == 'B' || b2.tipo == 'L')
                                                        {
                                                            if(b2.tipo == 'B')
                                                                erros++;
                                                            exit =  true;
                                                        }
                                                    }
                                                }
                                                if(exit)
                                                {
                                                    if(erros > 0)
                                                        printf("\nErro: Arquivo ou Diretorio defeituoso!");
                                                    else
                                                        printf("\nOk: Arquivo ou Diretorio operando!");
                                                }
                                                else
                                                {
                                                    if(b.ino.it.tl > 0)
                                                    {
                                                        b = blocos_disco[k]; exit = false;
                                                        Bloco b2; int erros = 0;
                                                        for(j = 0; j < b.ino.it.tl && !exit; j++)
                                                        {
                                                            b2 = blocos_disco[b.ino.it.posi[j]];
                                                            if(b2.tipo == 'B' || b2.tipo == 'L')
                                                            {
                                                                if(b2.tipo == 'B')
                                                                    erros++;
                                                                exit =  true;
                                                            }
                                                        }
                                                    }
                                                    if(exit)
                                                    {
                                                        if(erros > 0)
                                                            printf("\nErro: Arquivo ou Diretorio defeituoso!");
                                                        else
                                                            printf("\nOk: Arquivo ou Diretorio operando!");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                        printf("\nErro: O arquivo especificado nao faz parte deste Diretorio!");
                                }
                            }
                            else
                                printf("\nErro: O arquivo especificado nao faz parte deste Diretorio!");
                        }
                        else
                        {
                            exit = false; k = -1;
                            verificaArquivo(b, blocos_disco, aux, &exit, &k);
                            if(k != -1)
                            {
                                Bloco b = blocos_disco[k];
                                pos = b.ino.posi[0];

                            }
                            else
                            { }
                            cont++;
                        }
                    }
                }
                else
                    printf("\n[1] Erro: O arquivo especificado nao faz parte deste Diretorio!");
                strcpy(navegacao,"");
            break;
            case 3: //ls

                if(strlen(comando)==0)
                {
                    for(i=0; i<dir_atual.tl; i++)
                        printf("\t%s\n",dir_atual.itens[i].nomeitem);
                }
                else
                {
                    if(!strcmp(comando, "-l"))
                    {
                        for(i=0; i<dir_atual.tl; i++)
                        {
                            printf("\t%s\n",dir_atual.itens[i].nomeitem);
                            //if(blocos_disco[dir_atual.itens[i].posi].tipo == 'I')
                            //{
                                printf("\t\tData: %s\n",blocos_disco[dir_atual.itens[i].posi].ino.data);
                                printf("\t\tHora: %s\n",blocos_disco[dir_atual.itens[i].posi].ino.hora);
                                printf("\t\tTamanho: %d\n",blocos_disco[dir_atual.itens[i].posi].ino.tamanho);
                                printf("\t\tPermissao de Acesso: %s\n",blocos_disco[dir_atual.itens[i].posi].ino.permissao);
                            //}
                        }
                    }
                    else
                        puts("comando invalido");
                }

            break;
            case 4: //mkdir

                if(dir_atual.tl < 10)
                {
                    if(buscaDiretorio(blocos_disco,dir_atual,comando) == -1)
                    {
                        if(numeroBlocosLivres(blocos_disco,n_blocos) > 2)
                        {
                            pos_bloco_livre = retornaBlocoLivre(&lista_blivres);
                            blocos_disco[pos_bloco_livre].tipo = 'D';
                            blocos_disco[pos_bloco_livre].ino = criaInode(10,"dRWXRWXRWX");

                            pos = retornaBlocoLivre(&lista_blivres);
                            blocos_disco[pos].tipo = 'A';
                            blocos_disco[pos].dir = criaDiretorio(pos,comando,dir_atual.posi,dir_atual.dir_raiz);

                            //referencia do inode para o arquivo diretorio
                            blocos_disco[pos_bloco_livre].ino.posi[blocos_disco[pos_bloco_livre].ino.tl++] = pos;
                            //-----------------------------------------------------------------------------------


                            strcpy(dir_atual.itens[dir_atual.tl].nomeitem, comando);
                            dir_atual.itens[dir_atual.tl].posi = pos_bloco_livre;
                            dir_atual.tl++;
                        }
                        else
                            puts("Nao ha espaco para armazenamento");
                    }
                    else
                        puts("Ja existe um diretorio com este nome");
                }

            break;
            case 5: //rmdir

                pos_no_dir = buscaDiretorio(blocos_disco,dir_atual,comando);
                pos_bloco = dir_atual.itens[pos_no_dir].posi;
                if(blocos_disco[pos_bloco].dir.tl > 0)
                    puts("Nao e possivel excluir o diretorio ele não esta vazio");
                else
                {
                    remanejaItensDir(dir_atual,pos);
                    ///inserir pos_bloco na lista de blocos livres
                    insereLista(&lista_blivres,pos_bloco);
                }

            break;
            case 6: //rm
            break;
            case 7: //cd
            break;
            case 8: //link
            break;
            case 9: //unlink
            break;
            case 10://bad
                printf("Digite o numero do Bloco: ");
                scanf("%d", &i);
                if(i < 0 || i > n_blocos)
                    printf("\nErro: Bloco fora dos limites do Disco!");
                else
                {
                    pos = i;

                    if(danificaBloco(&lista_blivres, pos))
                    {
                        blocos_disco[pos].tipo = 'B';
                        printf("\nOk: O bloco %d foi danificado dentre os Blocos Livres!", i);
                    }
                    else
                    {
                        blocos_disco[pos].tipo = 'B';
                        printf("\nOk: O bloco %d foi danificado dentre os Blocos Alocados!", i);
                    }
                }
            break;
            case 11://touch

                for(i=0,j=0; i<strlen(comando) && comando[i]!=' '; i++)
                    nomearquivo[j++] = comando[i];
                nomearquivo[j] = '\0';
                i++;
                if(i >= strlen(comando))
                    puts("comando invalido");
                else
                {
                    for(j=0; i<strlen(comando); i++)
                        bytes[j++] = comando[i];
                    bytes[j]='\0';
                    tamanho = atoi(bytes);
                    if(tamanho <= 0)
                        puts("comando invalido");
                    else
                    {
                        if(dir_atual.tl < 10)
                        {
                            if(buscaArquivo(blocos_disco,dir_atual,nomearquivo) != -1)
                                printf("Ja ha um arquivo com este nome");
                            else
                            {
                                if(numeroBlocosLivres(blocos_disco,n_blocos)>tamanho/10+1)
                                {
                                    pos_bloco_livre = retornaBlocoLivre(&lista_blivres);
                                    if(pos_bloco_livre == -1)
                                        printf("Espaço de armazenamento cheio");
                                    else
                                    {
                                        strcpy(raiz.itens[raiz.tl].nomeitem, nomearquivo);
                                        raiz.itens[raiz.tl++].posi = pos_bloco_livre;

                                        blocos_disco[pos_bloco_livre].tipo = 'I';
                                        blocos_disco[pos_bloco_livre].ino = criaInode(tamanho,"-RWXRWXRWX");
                                        //formato direto
                                        while(blocos_disco[pos_bloco_livre].ino.tl < 5 && tamanho > 0)
                                        {
                                            tamanho-=10;
                                            pos = retornaBlocoLivre(&lista_blivres);
                                            blocos_disco[pos_bloco_livre].ino.posi[blocos_disco[pos_bloco_livre].ino.tl++] = pos;
                                            blocos_disco[pos].tipo = 'A';
                                        }

                                        if(tamanho <= 0)
                                        {
                                            pos = retornaBlocoLivre(&lista_blivres);
                                            blocos_disco[pos_bloco_livre].ino.posi[blocos_disco[pos_bloco_livre].ino.tl++] = pos;
                                            blocos_disco[pos].tipo = 'L';
                                        }

                                        //indireto simples
                                        if(tamanho > 0)
                                        {
                                            while(blocos_disco[pos_bloco_livre].ino.is.tl < 5 && tamanho > 0)
                                            {
                                                tamanho-=10;
                                                pos = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos_bloco_livre].ino.is.posi[blocos_disco[pos_bloco_livre].ino.is.tl++] = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos].tipo = 'A';
                                            }

                                            if(tamanho <= 0)
                                            {
                                                pos = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos_bloco_livre].ino.is.posi[blocos_disco[pos_bloco_livre].ino.is.tl++] = pos;
                                                blocos_disco[pos].tipo = 'L';
                                            }
                                        }
                                        //indireto duplo
                                        if(tamanho > 0)
                                        {
                                            while(blocos_disco[pos_bloco_livre].ino.id.tl < 10 && tamanho > 0)
                                            {
                                                tamanho-=10;
                                                pos = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos_bloco_livre].ino.id.posi[blocos_disco[pos_bloco_livre].ino.id.tl++] = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos].tipo = 'A';
                                            }

                                            if(tamanho <= 0)
                                            {
                                                pos = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos_bloco_livre].ino.id.posi[blocos_disco[pos_bloco_livre].ino.id.tl++] = pos;
                                                blocos_disco[pos].tipo = 'L';
                                            }
                                        }
                                        //indireto triplo
                                        if(tamanho > 0)
                                        {
                                            while(blocos_disco[pos_bloco_livre].ino.it.tl < 10 && tamanho > 0)
                                            {
                                                tamanho-=10;
                                                pos = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos_bloco_livre].ino.it.posi[blocos_disco[pos_bloco_livre].ino.it.tl++] = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos].tipo = 'A';
                                            }

                                            if(tamanho <= 0)
                                            {
                                                pos = retornaBlocoLivre(&lista_blivres);
                                                blocos_disco[pos_bloco_livre].ino.it.posi[blocos_disco[pos_bloco_livre].ino.it.tl++] = pos;
                                                blocos_disco[pos].tipo = 'L';
                                            }
                                        }
                                    }
                                }
                                else
                                    printf("nao ha espaco para armazenamento");
                            }
                        }
                    }
                }

            break;
            case 12://df
                j = 0;
                for(i = 0; i < n_blocos; i++)
                    if(blocos_disco[i].tipo == 'F')
                        j++;
                printf("\n\n=============================================\n");
                printf("Numero de blocos livres do disco: %d Bytes", (j*tam_bloco));
                printf("\n=============================================\n\n");

                j=0;
                j = contaBlocosOcupados(raiz, blocos_disco, j);
                printf("\n\n=============================================\n");
                printf("Numero de blocos ocupados do disco: %d Bytes", (j*tam_bloco));
                printf("\n=============================================\n\n");
            break;

            case 13://quit
                    sair = 1;
            break;
            default: puts("comando invalido");
        }
    }while(sair != 1);
}

