#ifndef TADPILHA_H_INCLUDED
#define TADPILHA_H_INCLUDED
#define TF 10

struct Pilha
{
    unsigned int topo;
    unsigned int pilha[TF];
};

void inicializaPilha(Pilha *p)
{ (*p).topo = -1; }

void push(Pilha *p, int elem)
{ (*p).pilha[++(*p).topo] = elem; }

char pilhaCheia(int topo)
{ return topo == TF-1; }

char pilhaVazia(int topo)
{ return topo == -1; }

int pop(Pilha *p)
{ return (*p).pilha[(*p).topo--]; }

int top(Pilha p)
{ return p.pilha[p.topo]; }

void exibePilha(Pilha p)
{
    while(!pilhaVazia(p.topo))
        printf("%d\n",p.pilha[p.topo--]);
    printf("\n");
}

bool procuraBloco(Pilha p, unsigned int pos)
{
    bool achou = false;
    unsigned int bloco;
    while(!pilhaVazia(p.topo) && !achou)
    {
        bloco = pop(&p);
        if(pos == bloco)
            achou = true;
    }
    return achou;
}

#endif // TADPILHA_H_INCLUDED
