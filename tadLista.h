#ifndef TADLISTA_H_INCLUDED
#define TADLISTA_H_INCLUDED
#define TF 3000

struct No
{
    struct Pilha p;
};

struct Lista
{
    unsigned int tf2, tl;
    struct No posi[TF];
};

void insereLista(Lista *l, int valor)
{
    if(pilhaCheia((*l).posi[(*l).tl].p.topo))
    {
        No aux;
        inicializaPilha(&aux.p);
        push(&aux.p, valor);
        (*l).posi[++(*l).tl] = aux;
    }
    else
        push(&(*l).posi[(*l).tl].p, valor);
}

void inicializaLista(Lista *l, int tf)
{
    (*l).tf2 = (tf+1)/10;
    (*l).tl = 0;
    No aux;
    inicializaPilha(&aux.p);
    (*l).posi[(*l).tl] = aux;

    for(int i = 0; i < tf; i++)
        insereLista(&(*l), i);
}

void retiraLista(Lista *l)
{
    for(int i = 0; i < (*l).tl; i++)
        (*l).posi[i] = (*l).posi[i+1];
    (*l).tl--;
}

int retornaBlocoLivre(Lista *l)
{
    int pos=-1;
    if(!pilhaVazia((*l).posi[0].p.topo))
    {
        pos = pop(&((*l).posi[0].p));
        if(pilhaVazia((*l).posi[0].p.topo))
           retiraLista(&(*l));
        return pos;
    }
}

void exibeLista(Lista l)
{
    for(int i = 0; i <= l.tl; i++)
        exibePilha(l.posi[i].p);
}

int verificaBlocoLivre(Lista l, unsigned int pos)
{
    int num_p = -1; bool achou = false;
    for(int i = 0; i <= l.tl && !achou; i++)
    {
        if(procuraBloco(l.posi[i].p, pos))
        {
            num_p = i;
            achou = true;
        }
    }
    return num_p;
}

bool danificaBloco(Lista *l, unsigned int pos_bloco)
{
    unsigned int valor;
    int pos_pilha = verificaBlocoLivre(*l, pos_bloco);
    if(pos_pilha != -1)
    {
        No backup, aux;
        inicializaPilha(&aux.p);
        backup = (*l).posi[pos_pilha];
        while(!pilhaVazia(backup.p.topo))
        {
            valor = pop(&backup.p);
            if(valor != pos_bloco)
                push(&aux.p, valor);
        }

        (*l).posi[pos_pilha] = aux;
        if(pilhaVazia((*l).posi[pos_pilha].p.topo))
            if(pos_pilha == 0)
                retiraLista(&(*l));
        return true;
    }
    else
        return false;
}

#endif // TADLISTA_H_INCLUDED
