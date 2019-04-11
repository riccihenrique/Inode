Diretorio criaDiretorio(int pos, char nome[], int pai)
{
    Diretorio dir;
    
    strcpy(dir.nome, nome);
    dir.dir_pai = pai;
    dir.tl = 0;
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

    vet[0].dir = criaDiretorio(0, "/", 0);
}

Inode criaInode(int tamanho, char permicao[])
{
    Inode inode;
    inode.tamanho = tamanho;
    strcpy(inode.data,"10/04/2019");
    strcpy(inode.hora,"hora");
    strcpy(inode.grupo, "FIPP");
    strcpy(inode.usuario, "User");
    strcpy(inode.permissao,permicao);
    inode.tl = inode.is.tl = inode.id.tl = inode.it.tl = 0;
    return inode;
}

int verificaBlocoLivre(Queue l, int pos)
{
    int i;

    for(i = 0; i <= l.tl; i++)
    {
        Stack s = l.stack[i];
        while(!isEmpty(s) && top(s) != pos)
            pop(&s);
        if(!isEmpty(s))
            return i;              
    }
    return -1;
}

int getBlocoLivre(Queue *l)
{
    int pos = -1;
    if(!isEmpty((*l).stack[0]))
    {
        pos = pop((&(*l).stack[(*l).tl]));
        if(isEmpty((*l).stack[(*l).tl]))
           removeQueue(&*l);
    }    
    return pos;
}

void BadBlock(Queue l, int pos_bloco, Bloco bloco[])
{
    int valor, pos_pilha = verificaBlocoLivre(l, pos_bloco);
    if(pos_pilha > -1)
    {
        Stack backup, aux;
        initStack(&aux);
        backup = l.stack[pos_pilha];
        while(!isEmpty(backup))
        {
            valor = pop(&backup);
            if(valor != pos_bloco)
                push(&aux, valor);
        }

        l.stack[pos_pilha] = aux;
        if(isEmpty(l.stack[pos_pilha]))
            if(pos_pilha == 0)
                removeQueue(&l);
    }

    bloco[pos_bloco].tipo = 'B';
}

int buscaDiretorio(Bloco bloco[], char nome[], int dir)
{
    int i;
    do
    {
        i = 0;
        
        if(!strcmpi(nome, ".."))
        	return bloco[dir].dir.dir_pai;
        
         if(!strcmpi(nome, "."))
        	return dir;
        if(bloco[dir].dir.tl - 1 == -1)
        	return -1;
        
        while(i < bloco[dir].dir.tl - 1)
        {
            if(!strcmpi(bloco[dir].dir.itens[i].nome, nome))
                return bloco[dir].dir.itens[i].pos; 
            i++;
                
        }
        if(!strcmpi(bloco[dir].dir.itens[i].nome, ""))
            dir = bloco[dir].dir.itens[i].pos;
        else  if(!strcmpi(bloco[dir].dir.itens[i].nome, nome))
            return bloco[dir].dir.itens[i].pos;
        else
                return -1;

    }while(dir != -1);
}
