struct IS
{
    unsigned int posi[5];
    int tl;
};

struct ID
{
    int posi[10];
    int tl;
};

struct IT
{
    int posi[125];
    int tl;
};

struct DirItens
{
    char nomeitem[40];
    int posi;
};

struct Diretorio
{
    char nome[60];
    DirItens itens[20];
    int tl, dir_pai,dir_raiz;
    unsigned int posi;
} ;

struct Inode
{
    char data[11];
    char permissao[11];
    char hora[10];
    unsigned int tamanho;
    unsigned int posi[5], tl;
    struct IS is;
    struct ID id;
    struct IT it;
};

struct Bloco
{
    char tipo;
    struct Diretorio dir;
    struct Inode ino;
};

void inicializaBlocos(Bloco vet[], int n, Lista &l, Diretorio &raiz)
{
    int bloco=0, bloco1=0, bloco3=0, tl=0, b4=0;

    for(int i = 0; i < n; i++)
        vet[i].tipo = 'F';
    // Inserindo o registro com nome boot no diret�rio raiz
    b4 = retornaBlocoLivre(l);
    strcpy(raiz.itens[raiz.tl].nomeitem, "/boot");
    raiz.itens[raiz.tl].posi = b4;
    raiz.tl++;

    vet[b4].tipo = 'D';
    strcpy(vet[b4].ino.data, "-");
    strcpy(vet[b4].ino.hora, "-");
    strcpy(vet[b4].ino.data, "-");
    vet[b4].ino.id.tl = 0;
    vet[b4].ino.is.tl = 0;
    vet[b4].ino.it.tl = 0;
    strcpy(vet[b4].ino.permissao, "----------");
    vet[b4].ino.tl=0;
    bloco = retornaBlocoLivre(l);
    vet[b4].ino.posi[vet[b4].ino.tl++] = bloco;

    vet[bloco].tipo = 'A';
    strcpy(vet[bloco].dir.nome, "/raiz/boot");
    vet[bloco].dir.tl = 0;
    strcpy(vet[bloco].dir.itens[vet[bloco].dir.tl].nomeitem, "/kernel");
    bloco3 = retornaBlocoLivre(l);
    vet[bloco].dir.itens[vet[bloco].dir.tl].posi = bloco3;
    vet[bloco].dir.tl++;

    vet[bloco3].tipo = 'I';
    strcpy(vet[bloco3].ino.data, "-");
    strcpy(vet[bloco3].ino.hora, "-");
    strcpy(vet[bloco3].ino.data, "-");
    vet[bloco3].ino.id.tl = 0;
    vet[bloco3].ino.is.tl = 0;
    vet[bloco3].ino.it.tl = 0;
    strcpy(vet[bloco3].ino.permissao, "----------");
    vet[bloco3].ino.tl=0;
    b4 = retornaBlocoLivre(l);
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'A';

    b4 = retornaBlocoLivre(l);
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'A';

    b4 = retornaBlocoLivre(l);
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'A';

    b4 = retornaBlocoLivre(l);
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'L';

    /*strcpy(vet[bloco].dir.itens[vet[bloco].dir.tl].nomeitem, "/kernel2");
    bloco3 = retornaBlocoLivre(&(*l));
    vet[bloco].dir.itens[vet[bloco].dir.tl].posi = bloco3;
    vet[bloco].dir.tl++;

    vet[bloco3].tipo = 'I';
    strcpy(vet[bloco3].ino.data, "-");
    strcpy(vet[bloco3].ino.hora, "-");
    strcpy(vet[bloco3].ino.data, "-");
    vet[bloco3].ino.id.tl = 0;
    vet[bloco3].ino.is.tl = 0;
    vet[bloco3].ino.it.tl = 0;
    strcpy(vet[bloco3].ino.permissao, "----------");
    vet[bloco3].ino.tl=0;
    b4 = retornaBlocoLivre(&(*l));
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'A';

    b4 = retornaBlocoLivre(&(*l));
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'A';

    b4 = retornaBlocoLivre(&(*l));
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'A';

    b4 = retornaBlocoLivre(&(*l));
    vet[bloco3].ino.posi[vet[bloco3].ino.tl++] = b4;
    vet[b4].tipo = 'L';*/
}

Diretorio criaDiretorio(int posi, char nome[], int dir_par, int dir_raiz)
{
    Diretorio dir;
    dir.dir_pai = dir_par;
    dir.tl=0;
    strcpy(dir.nome,nome);
    dir.posi = posi;
    return dir;
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
