#include <stdio.h>
#include <stdlib.h>

typedef int TipoL;

typedef struct ListaNo
{
    TipoL info;
    struct ListaNo *prox;
} *pListaNo;

typedef struct TLista
{
    pListaNo primeiro, ultimo, iterador;
    int longitude;
} * Lista;


Lista inicLista()
{

    Lista lst;
    lst=(Lista) malloc(sizeof(struct TLista)); // alocando a struct TLista
    lst->longitude = 0;   // zero elmentos
    lst->iterador = NULL;
    lst->primeiro = NULL;
    lst->ultimo = NULL;
    return lst; // retorna o endereco onde a struct Lista foi alocada
}


void primLista(Lista lst)
{
    //por o iterador sobre o primeiro No da lista
    lst->iterador = lst->primeiro;
}

void ultLista(Lista lst){
    //por o iterador sobre o ultimo No da lista
    lst->iterador = lst->ultimo;
}

void posLista(Lista lst, int pos){

    if(lst->longitude > 0 && pos >=1 && pos <= lst->longitude){

        int i;
        for(i=1, lst->iterador = lst->primeiro; i < pos; i++, lst->iterador = lst->iterador->prox)
        {}
    }
    else{
        lst->iterador = NULL; // iterador indefinido
    }
}

int fimLista(Lista lst)
{
    return (lst->iterador == NULL);
}

void segLista(Lista lst)
{
    if(lst->iterador == NULL)
    {
        printf("\n erro: iterador indefinido \n");
    }
    else
    {
        lst->iterador = lst->iterador->prox;
    }
}

TipoL infoLista(Lista lst)
{
    if(lst->iterador == NULL)
    {
        printf("\n erro: iterador indefinido \n");
        return 0;
    }
    else
        return lst->iterador->info;
}

int longLista(Lista lst)
{
    return lst->longitude;
}


//3 casos: Lista vazia, iterador sobre o ultimo elemento, iterador sobre um elemento intermediario
void anxLista(Lista lst, TipoL elem)
{
    //tratamento de erro
    if(lst->iterador==NULL && lst->longitude > 0)
    {
        printf("\n erro: iterador indefinido e lista cheia \n");

    }
    else
    {

        //alocar memória para o novoNo a ser adicionado
        pListaNo novoNo = ( pListaNo )malloc( sizeof( struct ListaNo ) );
        novoNo->info = elem; // atribuir o elemento a ser armazenado
        novoNo->prox= NULL;  // atribuir NULL para deixar o novoNo preparado

        if (lst->longitude == 0)  // lista vazia
        {
            //apontar para o novoNo
            lst->primeiro = novoNo;
            lst->ultimo = novoNo;
            lst->iterador = novoNo;
            lst->longitude++;
        }
        else if (lst->iterador == lst->ultimo )  // iterador sobre o ultimo elemento
        {
            //por no campo prox do ultimo no o endereco do novoNo
            lst->iterador->prox = novoNo;
            //lst->ultimo->prox = novoNo;
            //atualizar o campo ultimo com o endereco do novoNo
            lst->ultimo = novoNo;
            //atualizar o campo iterador com o endereco do novoNo
            lst->iterador = novoNo;
            //incrementar a quantidade de nos
            lst->longitude++;
        }
        else  //iterador sobre um noh intermediario
        {
            // o prox do novoNo aponta para o proximo Noh depois do iterador
            // fazer o prox do iterador apontar para o novoNo
            novoNo->prox = lst->iterador->prox;
            lst->iterador->prox = novoNo;
            lst->iterador = novoNo;
            lst->longitude++;
        }

    }

}



//3 casos: Lista vazia, iterador sobre o primeiro elemento, iterador sobre qualquer outro elemento
void insLista( Lista lst, TipoL elem )
{

    if(lst->iterador == NULL && lst->longitude > 0)
    {
        printf("\n erro: iterador indefinido e lista cheia \n");

    }
    else
    {

        //alocar memória para o novoNo a ser adicionado
        pListaNo novoNo = ( pListaNo )malloc( sizeof( struct ListaNo ) );
        novoNo->info = elem; // atribuir o elemento a ser armazenado
        novoNo->prox= NULL;  // atribuir NULL para deixar o novoNo preparado

        if (lst->longitude == 0)  // lista vazia
        {
            //apontar para o novoNo
            lst->primeiro = novoNo;
            lst->ultimo = novoNo;
            lst->iterador = novoNo;
            lst->longitude++;
        }
        else if ( lst->iterador == lst->primeiro)  // iterador sobre o primeiro elemento
        {
            //novoNo->prox = lst->iterador;
            novoNo->prox = lst->primeiro;
            lst->primeiro = novoNo;
            lst->iterador = novoNo;
            lst->longitude++;
        }
        else  //iterador sobre qualquer outro noh
        {
            //usar um segundo iterador para percorrer a lista e parar uma posicao antes do iterador
            pListaNo p;
            for(p = lst->primeiro; p->prox != lst->iterador ; p = p->prox )
            {

            }
            //ao sair do for, p esta um noh antes do iterador
            //acertar os ponteiros
            novoNo->prox = lst->iterador;
            p->prox = novoNo;
            lst->iterador = novoNo;
            lst->longitude++;
        }

    }

}

void elimLista( Lista lst )
{

    if(lst->iterador != NULL)
    {

        pListaNo noAserDesalocado;
        if (lst->iterador == lst->primeiro)  // se o iterador estiver sobre o primeiro elemento
        {
            if (lst->longitude == 1){

                noAserDesalocado = lst->iterador;
                lst->iterador = NULL;
                lst->primeiro = NULL;
                lst->ultimo = NULL;
                lst->longitude--;
                free(noAserDesalocado);

            }
            else{

                noAserDesalocado = lst->iterador;
                lst->iterador = lst->iterador->prox;
                //lst->primeiro = lst->primeiro->prox;
                lst->primeiro = lst->iterador;
                lst->longitude--;
                free(noAserDesalocado);
            }
        }
        else  // iterador esta sobre qualquer outro no que nao o primeiro no
        {
            //iterador sobre no intermediario ou o ultimo no
            pListaNo p;
            for(p = lst->primeiro; p->prox != lst->iterador; p = p->prox)
            {
            }
            noAserDesalocado = lst->iterador;
            p->prox = lst->iterador->prox;

            if( lst->iterador == lst->ultimo) // se o iterador estiver sobre o utlimo no
                lst->ultimo = p;

            lst->iterador = lst->iterador->prox;
            free(noAserDesalocado);
            lst->longitude--;
        }
    }
    else
    {
        printf("\n erro: iterador indefinido \n");
    }
}



void addNoInicio(Lista lst, TipoL elem)
{
    pListaNo no = (pListaNo) malloc(sizeof(struct ListaNo));
    no->info = elem;
    no->prox = NULL;

    if(lst->longitude == 0)
    {
        lst->primeiro = no;
        lst->iterador = no;
        lst->ultimo = no;
    }
    else
    {
        no->prox = lst->primeiro;
        lst->iterador = no;
        lst->primeiro = no;
    }
    lst->longitude++;
}

void printLista(Lista lst)
{
    for(primLista(lst);!fimLista(lst);segLista(lst))
    {
        printf("%d ", infoLista(lst));
    }
}

//------------------------------------------------------------------------------------------------------------------------------

TipoL maiorElemento(Lista lst)
{
    TipoL maior;
    if(longLista(lst) == 0)
    {
        //lista vazia
        return 0;
    }
    else   //lista cheia
    {
        primLista(lst);
        maior = infoLista(lst);
        for(primLista(lst) ; !fimLista(lst) ; segLista(lst) )
        {

            if(infoLista(lst) > maior)
                maior = infoLista(lst);
        }
        return maior;
    }

}
//1) Verificar se duas listas são iguais. Duas listas são iguais se ambas as estruturas têm o mesmo número de elementos, e estes são iguais um a um. Em particular, duas listas vazias são iguais.
int iguaisListas(Lista lst1, Lista lst2)
{

    //verificar se lst1 e lst2 sao vazias
    if(longLista(lst1) == 0 && longLista(lst2)== 0)
        return 1;
    //senao se long de lst1 == long lst2
    if(longLista(lst1) == longLista(lst2))
    {
        //percorrer lst1 e lst2 e comparar noh a noh
        for(primLista(lst1), primLista(lst2); !fimLista(lst1); segLista(lst1), segLista(lst2))
        {
            if(infoLista(lst1) != infoLista(lst2))
                return 0;
        }
        return 1;
    }
    else
    {
        //senao nao sao iguais
        return 0;
    }

}

//2) Verificar se duas listas são semelhantes. Duas listas são semelhantes se têm os mesmos elementos mesmo em ordem diferente. Se existe um elemento repetido na lista lst1, o mesmo deve aparecer repetido na lista lst2.
int semelhantesListas(Lista lst1, Lista lst2)
{
    //verificar se lst1 e lst2 sao vazias
    if(longLista(lst1) == longLista(lst2))
    {
        primLista(lst1);
        primLista(lst2);
        while(!fimLista(lst1))
        {
            if(infoLista(lst1) == infoLista(lst2))
            {
                segLista(lst1);
                primLista(lst2);
            }
            else if(lst2->iterador==NULL)
                return 0;
            else
                segLista(lst2);
        }
        return 1;
    }
    else
        return 0;
}

//3)  Verificar se a lista lst2 é uma sublista de lst1.
int subLista(Lista lst1, Lista lst2)
{
    if(longLista(lst2)==0)
        return 1;
    else if(longLista(lst2)<=longLista(lst1))
    {
        primLista(lst1);
        primLista(lst2);
        while(!fimLista(lst1))
        {
            if(infoLista(lst2)==infoLista(lst1))
            {
                for(primLista(lst2);!fimLista(lst2);segLista(lst2), segLista(lst1))
                {
                    if(fimLista(lst1) || infoLista(lst1)!=infoLista(lst2))
                        return 0;
                }
                return 1;
            }
            else
                segLista(lst1);
        }
        return 0;
    }
    else
        return 0;
}

//4)Verificar se uma lista lst2 está contida numa lista lst1.
int contidaLista(Lista lst1, Lista lst2)
{
    if(longLista(lst2)==0)
        return 1;
    else if(longLista(lst2)<=longLista(lst1))
    {
        primLista(lst1);
        primLista(lst2);
        while(!fimLista(lst2))
        {
            if(infoLista(lst2)==infoLista(lst1))
            {
                segLista(lst2);
                primLista(lst1);
            }
            else
            {
                segLista(lst1);
                if(lst1->iterador==NULL)
                    return 0;
            }
        }
        return 1;
    }
    else
        return 0;
}

//5)Verificar se uma lista lst está ordenada
int ordenadaLista(Lista lst)
{
    TipoL aux;
    if(longLista(lst)==0 || longLista(lst)==1)
        return 1;
    else
    {
        aux = lst->primeiro->info;
        for(primLista(lst); !fimLista(lst); segLista(lst))
        {
            if(infoLista(lst)>aux)
                return 0;
            else
                aux=infoLista(lst);
        }
        return 1;
    }
}

//6) Adiciona o elemento elem no final de lst:
void adicLista( Lista lst, TipoL elem){

    if(longLista(lst) == 0){ // lista vazia
        anxLista(lst, elem);
    }
    else{ // lista está cheia
        //por o iterador na ultima posicao
        ultLista(lst);
        anxLista(lst, elem);
    }
}

//7) Substitue o conteúdo atual do iterador pelo elemento elem:
void substitueLista( Lista lst, TipoL elem){

    lst->iterador->info = elem;
}

//8) Indica se o elemento elem aparece na lista:
int estaNaLista( Lista lst, TipoL elem){

    if(longLista(lst) == 0)
        return 0;
    else{
        for(primLista(lst); !fimLista(lst); segLista(lst)){
            if(infoLista(lst) == elem)
                return 1; // achou o elemento
        }
        return 0; // elem nao esta na lista
    }
}

//9) Exibe todos os elementos da lista, utilizando a operação posLista para avançar:
void exibeLista(Lista lst)
{
    int i=1;
    for(primLista(lst); !fimLista(lst); posLista(lst,i))
    {
        printf("%d", infoLista(lst));
        i++;
    }
}

//10) Coloca o iterador na posição anterior à atual:
void antLista( Lista lst){

    int i;
    pListaNo p;
    if(lst->iterador != lst->primeiro){
        for( p = lst->primeiro, i=1; p->prox != lst->iterador; p=p->prox, i++)
        { }
        posLista(lst, i);
    }
}

//11) Retorna a posição do iterador na lista:
int posIteradorLista(Lista lst)
{
    int pos=0;
    if(longLista(lst)==0)
        printf("Lista Vazia\n");
    else if(lst->iterador==NULL)
        printf("Iterador Indefinido\n");
    else
    {
        while(!fimLista(lst))
        {
            pos++;
            segLista(lst);
        }
        pos = longLista(lst) - pos + 1;
    }
    posLista(lst, pos);
    return pos;
}

//12) Deixar na lista somente uma ocorrência de cada um dos elementos:
void simplificarLista(Lista lst)
{
    pListaNo aux;
    for(primLista(lst); !fimLista(lst); segLista(lst))
    {
        aux = lst->iterador;
        for(primLista(lst); lst->iterador!=aux; segLista(lst))
        {
            if(lst->iterador->info == aux->info)
            {
                elimLista(lst);
                antLista(lst);
            }
        }
    }
}

//13)Retorna o número total de elementos diferentes em lst:
int numDiferentesLista(Lista lst)
{
    int n=0, pos=0;
    pListaNo aux;
    for(primLista(lst); !fimLista(lst); segLista(lst))
    {
        aux = lst->iterador;
        n++;
        pos++;
        for(primLista(lst); lst->iterador!=aux; segLista(lst))
        {
            if(lst->iterador->info == aux->info)
            {
                n--;
                posLista(lst, pos-1);
            }
        }
    }
    return n;
}

//14) Computa o número de vezes que o elemento elem aparece na lista:
int numOcorrenciasLista(Lista lst, TipoL elem)
{
    int n=0;
    for(primLista(lst); !fimLista(lst); segLista(lst))
    {
        if(lst->iterador->info == elem)
            n++;
    }
    return n;
}

//15) Retorna o elemento que aparece mais vezes na lista não vazia lst:
TipoL maxOcorrenciaLista(Lista lst)
{
    if(lst->longitude!=0)
    {
        pListaNo aux;
        TipoL maxElem;
        int n, max;

        for(primLista(lst); !fimLista(lst); segLista(lst))
        {
            n=0;
            aux = lst->iterador;
            for(primLista(lst); !fimLista(lst); segLista(lst))
            {
                if(lst->iterador->info==aux->info)
                    n++;
            }
            if(aux == lst->primeiro || n>max)
            {
                max=n;
                maxElem=aux->info;
            }
            lst->iterador=aux;
        }
        return maxElem;
    }
    else
    {
        printf("Erro! Lista Vazia");
        return 0;
    }
}

//16) Retorna a posiçãoda última ocorrência do elemento elem. Se não ocorre, retorna zero:
int ultOcorrenciaLista(Lista lst, TipoL elem)
{
    int n=1, pos=0;
    for(primLista(lst);!fimLista(lst);segLista(lst), n++)
    {
        if(lst->iterador->info==elem)
            pos=n;
    }
    return pos;
}

//17) Elimina da lista lst todos os elementos compreendidos entre a posição p1 e p2, inclusive:
void eliminarLista(Lista lst, int p1, int p2)
{
    int pos=1;
    for(primLista(lst);pos!=p1 && pos!=p2;segLista(lst), pos++)
    {
    }
    if(pos==p1)
    {
        while(pos!=p2+1)
        {
            elimLista(lst);
            pos++;
        }
    }
    else if(pos==p2)
    {
        while(pos!=p1+1)
        {
            elimLista(lst);
            pos++;
        }
    }
}

//18) Ordena em ordem crescente a lista lst:
void ordenarLista(Lista lst)
{
    TipoL aux;
    for(primLista(lst);!fimLista(lst);)
    {
        if(( lst->iterador->prox != NULL )&&( lst->iterador->info > lst->iterador->prox->info ))
        {
            aux = lst->iterador->info;
            lst->iterador->info = lst->iterador->prox->info;
            lst->iterador->prox->info = aux;
            antLista(lst);
        }
        else
            segLista(lst);
    }
}

//19) Elimina da lista lst1 todos os elementos que aparecem na lista lst2:
void diferencaLista( Lista lst1, Lista lst2)
{
    if(lst1->longitude < lst2->longitude)
        printf("Erro! Lista 2 contem mais elementos do que a Lista 1\n");
    else
    {
        for(primLista(lst1);!fimLista(lst1);segLista(lst1))
        {
            for(primLista(lst2);!fimLista(lst2);segLista(lst2))
            {
                while(lst1->iterador->info==lst2->iterador->info)
                {
                    elimLista(lst1);
                }
            }
        }
    }
}

int main()
{
    printf("    Inicio\n");
    Lista Numeros1 = inicLista();
    Lista Numeros2 = inicLista();
    int fim=0;
    int op1, op2;
    int pos;
    TipoL elem;

    while(fim!=1)
    {
        printf("\n-----------------------------MENU------------------------------\n");

        printf("(1-Menu Lista 1)\n");
        printf("(2-Menu Lista 2)\n");
        printf("(3-Exibe Listas)\n");
        printf("(4-Verificar se Semelhantes)\n");
        printf("(5-Verificar se Lista 2 eh SubLista de Lista 1)\n");
        printf("(6-Verificar se Lista 2 esta contida em Lista 1)\n");
        printf("(7-Eliminar os elementos da Lista 1 que estao presentes na Lista 2)\n");
        printf("(0-Sair)\n");
        printf("Digite Sua Escolha: ");
        scanf("%d", &op1);

        if(op1==1)
        {
            printf("\n--------------------LISTA 1--------------------\n");

            printf("(1-Adicionar Numero na Lista)\n");
            printf("(2-Eliminar Numero do Iterador da Lista)\n");
            printf("(3-Posicionar Iterador da Lista)\n");
            printf("(4-Print Maior Elemento da Lista)\n");
            printf("(5-Verificar se esta Ordenada)\n");
            printf("(6-Substitue o conteudo do iterador por elemento)\n");
            printf("(7-Verificar Elemento na Lista)\n");
            printf("(8-Mover Iterador Para Tras)\n");
            printf("(9-Print Posicao do Iterador)\n");
            printf("(10-Eliminar Itens Repetidos na Lista)\n");
            printf("(11-Print Numero de Elementos Diferentes)\n");
            printf("(12-Print Numero de Ocorrencias de um Elemento)\n");
            printf("(13-Print Elemento Mais Recorrente)\n");
            printf("(14-Print Ultima Posicao de Elemento)\n");
            printf("(15-Eliminar Elementos Entre Posicoes)\n");
            printf("(16-Ordenar a Lista de Forma Crescente)\n");
            printf("(0-Voltar)\n");
            printf("Digite Sua Escolha: ");
            scanf("%d", &op2);

            if(op2==1)
            {
                printf("Digite o elemento para adicionar:");
                scanf("%d", &elem);
                adicLista(Numeros1, elem);
                printf("Elemento Adicionado.\n");
            }
            else if(op2==2)
            {
                if(Numeros1->iterador != NULL)
                {
                    elimLista(Numeros1);
                    printf("Elemento Eliminado.\n");
                }
                else
                    printf("Erro! Iterador NULO\n");
            }
            else if(op2==3)
            {
                printf("Digite a posicao para o iterador:");
                scanf("%d", &pos);
                if(pos>0 && pos<=Numeros1->longitude)
                {
                    posLista(Numeros1, pos);
                    printf("Iterador Posicionado.\n");
                }
                else
                    printf("Erro! Posicao Invalida.\n");
            }
            else if(op2==4)
            {
                printf("Maior Elemento: %d\n", maiorElemento(Numeros1));
            }
            else if(op2==5)
            {
                if(ordenadaLista(Numeros1))
                    printf("Lista 1 Ordenada\n");
                else
                    printf("Lista 1 Desordenada\n");
            }
            else if(op2==6)
            {
                printf("Digite o Elemento Substituto: ");
                scanf("%d", &elem);
                substitueLista(Numeros1, elem);
            }
            else if(op2==7)
            {
                printf("Digite o Elemento Desejado: ");
                scanf("%d", &elem);
                if(estaNaLista(Numeros1, elem))
                    printf("Elemento Encontrado\n");
                else
                    printf("Elemento Nao Encontrado\n");
            }
            else if(op2==8)
            {
                if(Numeros1->iterador == Numeros1->primeiro)
                    printf("Erro! Iterador na primeira posicao.\n");
                else if(Numeros1->iterador != NULL)
                {
                    antLista(Numeros1);
                    printf("Iterador Movido\n");
                }
                else
                    printf("Erro! Iterador NULO\n");
            }
            else if(op2==9)
            {
                if(Numeros1->iterador != NULL)
                    printf("Posicao: %d", posIteradorLista(Numeros1));
                else
                    printf("Iterador NULO\n");
            }
            else if(op2==10)
            {
                simplificarLista(Numeros1);
                printf("Lista Simplificada\n");
            }
            else if(op2==11)
            {
                printf("%d Elementos Diferentes na Lista 1\n", numDiferentesLista(Numeros1));
                ultLista(Numeros1);
            }
            else if(op2==12)
            {
                printf("Digite o Elemento Desejado: ");
                scanf("%d", &elem);
                printf("%d Ocorrencias de '%d' na Lista 1\n", numOcorrenciasLista(Numeros1, elem), elem);
                ultLista(Numeros1);
            }
            else if(op2==13)
            {
                printf("Elemento mais recorrente: %d\n", maxOcorrenciaLista(Numeros1));
                ultLista(Numeros1);
            }
            else if(op2==14)
            {
                printf("Digite o Elemento Desejado: ");
                scanf("%d", &elem);
                printf("Ultima Posicao do Elemento %d: %d\n", elem, ultOcorrenciaLista(Numeros1, elem));
                ultLista(Numeros1);
            }
            else if(op2==15)
            {
                int pos2;

                printf("Digite a posicao 1:");
                scanf("%d", &pos);

                if(pos<=0 || pos>longLista(Numeros1))
                    printf("Erro! Posicao Invalida\n");
                else
                {
                    printf("Digite a posicao 2:");
                    scanf("%d", &pos2);

                    if(pos2<=0 || pos2>longLista(Numeros1))
                        printf("Erro! Posicao Invalida\n");
                    else
                    {
                        eliminarLista(Numeros1, pos, pos2);
                        printf("Elementos Eliminados\n");
                    }
                }
            }
            else if(op2==16)
            {
                if(Numeros1->longitude == 0)
                    printf("Erro! Lista Vazia");
                else
                {
                    ordenarLista(Numeros1);
                    printf("Lista 1 Ordenada\n");
                    ultLista(Numeros1);
                }
            }
            else if(op2==0){}
            else
                printf("Opcao Invalida!\n");
        }
        else if(op1==2)
        {
            printf("\n--------------------LISTA 2--------------------\n");

            printf("(1-Adicionar Numero na Lista)\n");
            printf("(2-Eliminar Numero da Lista)\n");
            printf("(3-Posicionar Iterador da Lista)\n");
            printf("(4-Print Maior Elemento da Lista)\n");
            printf("(5-Verificar se esta Ordenada)\n");
            printf("(6-Substitue o conteudo do iterador por elemento)\n");
            printf("(7-Verificar Elemento na Lista)\n");
            printf("(8-Mover Iterador Para Tras)\n");
            printf("(9-Print Posicao do Iterador)\n");
            printf("(10-Eliminar Itens Repetidos na Lista)\n");
            printf("(11-Print Numero de Elementos Diferentes)\n");
            printf("(12-Print Numero de Ocorrencias de um Elemento)\n");
            printf("(13-Print Elemento Mais Recorrente)\n");
            printf("(14-Print Ultima Posicao de Elemento)\n");
            printf("(15-Eliminar Elementos Entre Posicoes)\n");
            printf("(16-Ordenar a Lista de Forma Crescente)\n");
            printf("(0-Voltar)\n");
            printf("Digite Sua Escolha: ");
            scanf("%d", &op2);

            if(op2==1)
            {
                printf("Digite o elemento para adicionar:");
                scanf("%d", &elem);
                adicLista(Numeros2, elem);
                printf("Elemento Adicionado.\n");
            }
            else if(op2==2)
            {
                if(Numeros2->iterador != NULL)
                {
                    elimLista(Numeros2);
                    printf("Elemento Eliminado.\n");
                }
                else
                    printf("Erro! Iterador NULO");
            }
            else if(op2==3)
            {
                printf("Digite a posicao para o iterador:");
                scanf("%d", &pos);
                if(pos>0 && pos<=Numeros2->longitude)
                {
                    posLista(Numeros2, pos);
                    printf("Iterador Posicionado.\n");
                }
                else
                    printf("Erro! Posicao Invalida.\n");
            }
            else if(op2==4)
            {
                printf("Maior Elemento: %d\n", maiorElemento(Numeros2));
            }
            else if(op2==5)
            {
                if(ordenadaLista(Numeros2))
                    printf("Lista 2: Ordenada\n");
                else
                    printf("Lista 2: Desordenada\n");
            }
            else if(op2==6)
            {
                printf("Digite o Elemento Substituto: ");
                scanf("%d", &elem);
                substitueLista(Numeros2, elem);
            }
            else if(op2==7)
            {
                printf("Digite o Elemento Desejado: ");
                scanf("%d", &elem);
                if(estaNaLista(Numeros2, elem))
                    printf("Elemento Encontrado\n");
                else
                    printf("Elemento Nao Encontrado\n");
            }
            else if(op2==8)
            {
                if(Numeros2->iterador == Numeros2->primeiro)
                    printf("Erro! Iterador na primeira posicao.\n");
                else if(Numeros2->iterador != NULL)
                {
                    antLista(Numeros2);
                    printf("Iterador Movido\n");
                }
                else
                    printf("Erro! Iterador NULO\n");
            }
            else if(op2==9)
            {
                if(Numeros2->iterador != NULL)
                    printf("Posicao: %d", posIteradorLista(Numeros2));
                else
                    printf("Iterador NULO");
            }
            else if(op2==10)
            {
                simplificarLista(Numeros2);
                printf("Lista Simplificada\n");
            }
            else if(op2==11)
            {
                printf("%d Elementos Diferentes na Lista 1\n", numDiferentesLista(Numeros2));
                ultLista(Numeros2);
            }
            else if(op2==12)
            {
                printf("Digite o Elemento Desejado: ");
                scanf("%d", &elem);
                printf("%d Ocorrencias de '%d' na Lista 2\n", numOcorrenciasLista(Numeros2, elem), elem);
                ultLista(Numeros2);
            }
            else if(op2==13)
            {
                printf("Elemento mais recorrente: %d\n", maxOcorrenciaLista(Numeros2));
                ultLista(Numeros2);
            }
            else if(op2==14)
            {
                printf("Digite o Elemento Desejado: ");
                scanf("%d", &elem);
                printf("Ultima Posicao do Elemento %d: %d\n", elem, ultOcorrenciaLista(Numeros2, elem));
                ultLista(Numeros2);
            }
            else if(op2==15)
            {
                int pos2;

                printf("Digite a posicao 1:");
                scanf("%d", &pos);

                if(pos<=0 || pos>longLista(Numeros2))
                    printf("Erro! Posicao Invalida\n");
                else
                {
                    printf("Digite a posicao 2:");
                    scanf("%d", &pos2);

                    if(pos2<=0 || pos2>longLista(Numeros2))
                        printf("Erro! Posicao Invalida\n");
                    else
                    {
                        eliminarLista(Numeros2, pos, pos2);
                        printf("Elementos Eliminados\n");
                    }
                }
            }
            else if(op2==16)
            {
                if(Numeros2->longitude == 0)
                    printf("Erro! Lista Vazia");
                else
                {
                    ordenarLista(Numeros2);
                    printf("Lista 2 Ordenada\n");
                    ultLista(Numeros2);
                }
            }
            else if(op2==0){}
            else
                printf("Opcao Invalida!\n");

        }
        else if(op1==3)
        {
            printf("Print - \n");
            printf("Lista 1: ");
            exibeLista(Numeros1);
            printf("\n");
            printf("Lista 2: ");
            exibeLista(Numeros2);
            printf("\n");
            ultLista(Numeros1);
            ultLista(Numeros2);
        }
        else if(op1==4)
        {
            if(semelhantesListas(Numeros1, Numeros2))
                printf("Listas: Semelhantes\n");
            else
                printf("Listas: Nao Semelhantes\n");
        }
        else if(op1==5)
        {
            if(subLista(Numeros1, Numeros2))
                printf("Lista 2 SubLista de Lista 1\n");
            else
                printf("Lista 2 Nao eh SubLista de Lista 1\n");
        }
        else if(op1==6)
        {
            if(contidaLista(Numeros1, Numeros2))
                printf("Lista 2 Contida em Lista 1\n");
            else
                printf("Lista 2 Nao Contida em Lista 1\n");
        }
        else if(op1==7)
        {
            diferencaLista(Numeros1, Numeros2);
            printf("Elementos Eliminados\n");
        }
        else if(op1==0)
            fim=1;
        else
            printf("Opcao Invalida!\n");

        printf("\n");
        system("pause");
        system("cls");

    }
    return 0;
}
