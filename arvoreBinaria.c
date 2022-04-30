#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct spotify
{
    char artista [30];
    int musica;
    float duracao;

    struct spotify *ant;
    struct register_tree *prox;
} p;
p *novo, *topo=NULL;



typedef struct node{
    struct spotify *dado;
    struct node *dir;
    struct node *esq;
} Node;


typedef struct lista{
    Node *inicial;
    Node *raiz;
    int tamanho;
} Lista;






int i=0;
int quant;
FILE *arquivo;


int insert ()
{
    printf("\n\n    QUANTAS MUSICAS IRÁ CADASTRAR NO SPOTIFY?: ");
    scanf("%d",&quant);

    for (i=0; i<quant; i++)
    {
        novo=(p *) malloc (2*sizeof(p));

        fflush(stdin);
        printf("\n\n    ARTISTA: ");
        gets(novo->artista);
        printf("    MÚSICA: ");
        scanf("%d",&novo->musica);
        printf("    DURAÇÃO: R$");
        scanf("%f",&novo->duracao);
        novo->ant=NULL;
        if(topo==NULL) //Caso a lista esteja vazia
        {
            topo=novo;

        }
        else
        {
            novo->ant=topo;
            topo=novo;
        }
    }
    return (0);
}

int show ()
{
    p *tmp;
    tmp=topo;
    if (tmp==NULL)  
    {
        printf ("\n\n   LISTA VAZIA! INSIRA UM DADO E TENTE NOVAMENTE.\n");
    }
    else
    {
        while (tmp!=NULL)
        {
            printf("\n\n    PRODUTO: %s\n", tmp->artista);
            printf("    musicaIGO: %d\n",tmp->musica);
            printf("    duracao: R$%0.2f\n\n",tmp->duracao);
            tmp=tmp->ant;
        }

    }

    return (0);
}

int delete ()
{
    char alerta;
    p *extra;
    extra = topo;
    if (topo == NULL)
    {
        printf ("\n\n     LISTA COMPLETAMENTE VAZIA!\n");
    }
    else
    {
        printf("\n\n      TEM CERTEZA DE DESEJA EXCLUIR TODOS OS DADOS? (S/N): ");
        scanf("%c",&alerta);
        alerta=tolower(alerta);
        if (alerta=='s')
        {
            topo = topo -> ant;
            free(extra);
            printf("\n      PILHA DELETADA! \n");
        }
        if (alerta=='n')
        {
            printf("\n      PILHA NAO DELETADA! \n");
        }
        if (alerta!='s' && alerta!='n')
        {
            printf("\n\n      OPCAO INVALIDA\n");
        }
    }

    return(0);
}

int save()
{
    p *tmp;
    tmp=topo;

    arquivo=fopen("text.txt","wb");

    /*    if (tmp==NULL)
        {
            printf("\n\n    ERRO AO SALVAR, PILHA ESTA VAZIA. INSIRA UM DADO E TENTE NOVAMENTE! \n");
        }*/
    while (tmp!=NULL)
    {
        fprintf(arquivo,"\n\n     ARTISTA: %s \n",tmp->artista);
        fprintf(arquivo,"     TITULO: %d \n",tmp->musica);
        fprintf(arquivo,"     DURACAO: %f ",tmp->duracao);
        tmp=tmp->ant;
    }

    fclose(arquivo);
    printf("\n\n    ARQUIVO SALVO COM SUCESSO!\n");


    return 0;
}

int open()
{
    p *tmp;
    tmp=topo;

    arquivo=fopen("text.txt","rt");

    if (arquivo == NULL)
    {
        printf("\n\n    NAO FOI POSSIVEL ABRIR O ARQUIVO. SALVE E TENTE NOVAMENTE! \n");
    }

    char frase [10000];
    while (fgets(frase, 1000,arquivo)!=NULL)
    {
        printf("%s\n",frase);
    }
    fclose(arquivo);

    return 0;
}




void about ()
{
    printf("\n\n");
    printf("    *================================ SOBRE ================================*\n");
    printf("    |                                                                       |\n");
    printf("    |Dados alocados de forma dinamica, com uso de ponteiros e structs|\n");
    printf("    |Avaliação para AA de Estrutura de Dados da IESB:  |\n");
    printf("    |    |\n");
    printf("    |                          |\n");
    printf("    |                                                                       |\n");
    printf("    |                       DADOS DO DESENVOLVEDOR/ESTUDIOSO:                              |\n");
    printf("    |CURSO: Engenharia de Software                                                     |\n");
    printf("    |NOME: Nivan José dos Santos Junior                                 |\n");
    printf("    |RA:2172190133               |\n");
    printf("    |                                                                       |\n");
    printf("    =========================================================================\n");
}

//A raiz passou a **raiz, e registro a *registro
void insere_Arvore(Node **raiz, struct register_tree *registro) {
    Node* novo = malloc(sizeof(Node)); //agora sem cast pois é desnecessário
    if(novo == NULL){
        return; // é void logo não pode ter tipo de retorno
    }

    novo->dado = registro; //o dado é o registro todo em si
    novo->dir = NULL;
    novo->esq= NULL;

    if(*raiz == NULL){ //ver se o duracao do ponteiro é null, logo arvore vazia
        *raiz = novo;
        return;
    }

    Node* atual = *raiz;
    Node* ant = NULL;

    while(atual != NULL){ // laço/ciclo agora só para navegar até ao sitio correto
        ant = atual;

        //o duracao a ser inserido vem no próprio registro, com registro->duracao
        if (ant->dado->duracao == atual->dado->duracao){
            free(novo);
            return; // é void logo não pode ter tipo de retorno
        }

        if(ant->dado->duracao > atual->dado->duracao){
            atual = atual->dir;
        }
        else{
            atual = atual->esq;
        }
    }

    //após navegar é feita a inserção pelo no anterior.
    if (atual->dado->duracao > ant->dado->duracao){ //se maior que o anterior fica a direita
        ant->dir = novo;
    }
    else { //senão fica a esquerda
        ant->esq = novo;
    }
}



int main ()
{
    Node *arvore = NULL;
    p *spotify = NULL;
    Lista *reg = malloc(sizeof(p));
    insere_Arvore(&arvore, reg); 

    char op_menu=0, op_menu_interno=0; /* Zera as listas, caso o programa seja usado novamente.*/

    do
    {
        printf("\n\n");
        printf("    *======================= MENU PRINCIPAL =========================*\n");
        printf("    |                                                                |\n");
        printf("    |                                                                |\n");
        printf("    |         A - INSERIR                   B - MOSTRAR              |\n");
        printf("    |                                                                |\n");
        printf("    |         C - DELETAR                   D - EDITAR               |\n");
        printf("    |                                                                |\n");
        printf("    |         E - BUSCAR                    F - SALVAR               |\n");
        printf("    |                                                                |\n");
        printf("    |         G - ABRIR                     H - SOBRE                |\n");
        printf("    |                                                                |\n");
        printf("    |                        S - SAIR                                |\n");
        printf("    |                                                                |\n");
        printf("    |                                                                |\n");
        printf("    ==================================================================\n");
        fflush(stdin);
        printf("\n    Digite...: ");
        scanf("%c", &op_menu);
        op_menu=tolower(op_menu);
        fflush(stdin); //limpa o buffer do teclado
        switch(op_menu)
        {
        case 'a'  :
            fflush(stdin);
            system("cls"); //limpa a tela
            insert();
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;
            fflush(stdin);
        case 'b':
            system("cls");
            show();
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;


        case 'c':
            fflush(stdin);
            system("cls");
            delete();
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;
            fflush(stdin);
        case 'd':
            fflush(stdin);
            system("cls");
            printf("você digitou: 4");
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;
            fflush(stdin);
        case 'e':

        case 'f':
            fflush(stdin);
            system("cls");
            save();
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;
        case 'g':
            fflush(stdin);
            system("cls");
            open();
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;
        case 'h':
            system("cls");
            about();
            printf("\n");
            do
            {
                printf("    0 - Menu principal: ");
                scanf("%s",&op_menu_interno);
            }
            while (op_menu_interno!='0');
            system("cls");
            break;
        case 's':
            system("cls");
            printf("\n");
            printf("Finalizando programa...");
            printf("\n");
            exit(0);
            break;
        default:
            system("cls");
            printf("dado invalido! Digite novamente");
            break;
        }

    }
    while (op_menu!=5);
    return (0);
} 