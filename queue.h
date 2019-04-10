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
            insertQueue(&(*l), i);
    }
}

void removeQueue(Queue *l)
{
	int i;
    for(i = 0; i < (*l).tl; i++)
        (*l).stack[i] = (*l).stack[i+1];
    (*l).tl--;
}

void showQueue(Queue l)
{
	int i;
    for(i = 0; i <= l.tl; i++)
        show(l.stack[i]);
}