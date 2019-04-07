#define TF 3000

struct No
{
    struct Stack s;
};

struct Lista
{
    unsigned int tf2, tl;
    struct No posi[TF];
};

void insereLista(Lista &l, int valor)
{
    if(isEmpty(l.posi[l.tl].s))
    {
        No aux;
        init(aux.s);
        push(aux.s, valor);
        l.posi[++l.tl] = aux;
    }
    else
        push(l.posi[l.tl].s, valor);
}

void inicializaLista(Lista &l, int tf)
{
    l.tf2 = (tf+1)/10;
    l.tl = 0;
    No aux;
    init(aux.s);
    l.posi[l.tl] = aux;

    for(int i = 0; i < tf; i++)
        insereLista(l, i);
}

void retiraLista(Lista &l)
{
    for(int i = 0; i < l.tl; i++)
        l.posi[i] = l.posi[i+1];
    l.tl--;
}

int retornaBlocoLivre(Lista &l)
{
    int pos = -1;
    if(!isEmpty(l.posi[0].s))
    {
        pos = pop((l.posi[0].s));
        if(isEmpty(l.posi[0].s))
           retiraLista(l);
    }    
    return pos;
}

void exibeLista(Lista l)
{
    for(int i = 0; i <= l.tl; i++)
        show(l.posi[i].s);
}

int verificaBlocoLivre(Lista l, int pos)
{
    int num_p = -1;
    bool achou = false;
    for(int i = 0; i <= l.tl && !achou; i++)
    {
        if(procuraBloco(l.posi[i].s, pos))
        {
            num_p = i;
            achou = true;
        }
    }
    return num_p;
}

bool danificaBloco(Lista &l, int pos_bloco)
{
    int valor;
    int pos_pilha = verificaBlocoLivre(l, pos_bloco);
    if(pos_pilha != -1)
    {
        No backup, aux;
        init(aux.s);
        backup = l.posi[pos_pilha];
        while(!isEmpty(backup.s))
        {
            valor = pop(backup.s);
            if(valor != pos_bloco)
                push(aux.s, valor);
        }

        l.posi[pos_pilha] = aux;
        if(isEmpty(l.posi[pos_pilha].s))
            if(pos_pilha == 0)
                retiraLista(l);
        return true;
    }
    else
        return false;
}