Diretorio criaDiretorio(int pos, char nome[], int pai, int raiz)
{
    Diretorio dir;
    
    strcpy(dir.nome,nome);
    dir.dir_pai = pai;
    dir.tl=0;
    dir.pos = pos;
    dir.dir_raiz = 0;
    return dir;
}

void inicializaBlocos(Bloco vet[], int tl)
{
    int i;

    for(i = 0; i < tl; i++)
        vet[i].tipo = 'F';

    for(i = 0; i < 30; i++)
        vet[(rand() % tl - 2) + 2].tipo = 'B';

    vet[0].dir = criaDiretorio(0, "/", 0, 0);
}

void pegarData_Hora(char hora[],char data[])
{
    char c1,c2;
    _strdate(data);
    c1 = data[3];
    c2 = data[4];
    data[3] = data[0];
    data[4] = data[1];
    data[0] = c1;
    data[1] = c2;
    _strtime(hora);
}

Inode criaInode(int tamanho, char perm[])
{
    Inode ino;
    char data[10],hora[10];
    pegarData_Hora(hora,data);
    strcpy(ino.data,data);
    strcpy(ino.hora,hora);
    strcpy(ino.permissao,perm);
    ino.tamanho = tamanho;
    ino.tl=0;
    ino.is.tl=ino.id.tl=ino.it.tl=0;
}
