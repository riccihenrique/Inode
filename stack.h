void initStack(Stack *s)
{ 
    (*s).top = -1; 
}

char isFull(Stack s)
{ 
    return s.top == TF-1;
}

char isEmpty(Stack s)
{ 
    return s.top == -1; 
}

void push(Stack *s, int info)
{ 
    (*s).stack[++(*s).top] = info;
}

int pop(Stack *s)
{ 
    return (*s).stack[(*s).top--]; 
}

int top(Stack s)
{ 
    return s.stack[s.top]; 
}

void show(Stack s)
{
    while(!isEmpty(s))
        printf("%d\n",s.stack[s.top--]);
}
