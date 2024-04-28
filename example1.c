/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa


typedef struct graph
{
    int v;
    int *vis;
    struct Node **last;
}GRAPH;


typedef struct stack
{
    int top;
    int size;
    int *arr;
} STACK;

NODE *create_node(int v)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

void add_edge(GRAPH *graph,int src,int dest)
{
    NODE *newNode = create_node(dest);
    newNode->next = graph->last[src];
    graph->last[src] = newNode;
    newNode = create_node(src);
    newNode->next = graph->last[dest];
    graph->last[dest] = newNode;
}

GRAPH *create_g(int v)
{
    int i;
    GRAPH *g = malloc(sizeof(GRAPH));
    g->v = v;
    g->last = malloc(sizeof(NODE *));
    g->vis = malloc(sizeof(int) *v);

    for (int i = 0; i < v; i++)
    {
        g->last[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STACK *create_s(int size)
{
    STACK *s = malloc(sizeof(STACK));
    s->arr = malloc(size*sizeof(int));
    s->top = -1;
    s->size = size;

    return s;
}

void push(int data,STACK *s)
{
    s->top = s->top+1;
    s->arr[s->top] = data;
}

void DFS(GRAPH *g,STACK *s,int v_nr)
{
    NODE *adj_list = g->last[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ",v_nr);
    push(v_nr,s);
    while (aux != NULL){
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g,s,con_ver);
        aux = aux->next;
    }
}

void insert_edges(GRAPH *g,int edg_nr,int nrv)
{
    int src,dest,i;
    printf("adauga %d munchii (de la 1 la %d)\n",edg_nr,nrv);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d",&src,&dest);
        add_edge(g,src,dest);
    }
}

void wipe(GRAPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
}

void canbe(GRAPH *g, int nrv, STACK *s1, STACK *s2)/// Nu inteleg ce vreti de la mine aici
{
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{
    {
        for (int j = 0; j < 5; j++)
        {
            DFS(g, s1, i);
            wipe(g, nrv);
            DFS(g, s2, j);
            for (int j = 0; j < nrv && !canbe; j++)
                for (int i = 0; i < nrv && !canbe; i++)
                    if ((s1->arr[i] == j) && (s2->arr[j] == i))
                        *canbe = 1;
        }

    }
}


int main()
{

    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &edg_nr);

    GRAPH *g = create_g(nrv);

    STACK *s1 = create_s(2 * nrv);
    STACK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2);
}
