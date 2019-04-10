void insertQueue(Queue *l, int valor)
{
    if(isEmpty((*l).stack[(*l).tl]))
        push(&(*l).stack[(*l).tl], valor);
    else
        push(&(*l).stack[(*l).tl], valor);

    if(isFull((*l).stack[(*l).tl]))
    {
        (*l).tl++;
        initStack(&(*l).stack[(*l).tl]);
    }
}

void initQueue(Queue *l, Bloco blocos[], int tl)
{
    int i;
    (*l).tl = 0;
    initStack(&(*l).stack[(*l).tl]);

    for(i = 0; i < tl; i++)
    {
        if(blocos[i].tipo == 'L');
            //insertQueue(&(*l), i);
    }
}

void removeQueue(Queue *l)
{
	int i;
    for(i = 0; i < (*l).tl; i++)
        (*l).stack[i] = (*l).stack[i+1];
    (*l).tl--;
}

int retornaBlocoLivre(Queue l)
{
    int pos = -1;
    if(!isEmpty(l.stack[0]))
    {
        pos = pop((&l.stack[0]));
        if(isEmpty(l.stack[0]))
           removeQueue(&l);
    }    
    return pos;
}

void exibeLista(Queue l)
{
	int i;
    for(i = 0; i <= l.tl; i++)
        show(l.stack[i]);
}

int verificaBlocoLivre(Queue l, int pos)
{
    int num_p = -1, i;
    int achou = 0;
    for(i = 0; i <= l.tl && !achou; i++)
    {
        if(procuraBloco(l.stack[i], pos))
        {
            num_p = i;
            achou = 1;
        }
    }
    return num_p;
}

char danificaBloco(Queue *l, int pos_bloco)
{
    int valor;
    int pos_pilha = verificaBlocoLivre((*l), pos_bloco);
    if(pos_pilha != -1)
    {
        Stack backup, aux;
        initStack(&aux);
        backup = (*l).stack[pos_pilha];
        while(!isEmpty(backup))
        {
            valor = pop(&backup);
            if(valor != pos_bloco)
                push(&aux, valor);
        }

        (*l).stack[pos_pilha] = aux;
        if(isEmpty((*l).stack[pos_pilha]))
            if(pos_pilha == 0)
                removeQueue(&(*l));
        return 1;
    }
    else
        return 0;
}
