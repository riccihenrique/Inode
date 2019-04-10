#define TF 999

struct Stack
{
    int top, stack[TF];
};
typedef struct Stack Stack; 

struct Queue
{
    int tl;
    Stack stack[30];
};
typedef struct Queue Queue;

struct IS
{
    int pos[5], tl;
};
typedef struct IS IS;

struct ID
{
    int pos[25], tl;
};
typedef struct ID ID;

struct IT
{
    int pos[125], tl;
};
typedef struct IT IT;

struct Itens
{
    int pos;
    char nome[40];
};
typedef struct Itens Itens;

struct Diretorio
{
    int tl, dir_pai,dir_raiz, pos;
    char nome[60];
    Itens itens[20];
};
typedef struct Diretorio Diretorio;

struct Inode
{
    char data[11], permissao[11], hora[10], usuario[50], grupo[50];
    int tamanho, pos[5], tl;
    struct IS is;
    struct ID id;
    struct IT it;
};
typedef struct Inode Inode;

struct Bloco
{
    char tipo;
    struct Diretorio dir;
    struct Inode ino;
};
typedef struct Bloco Bloco;
