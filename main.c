/**
 * @Author: João Guilherme de A. Prado RA: 05221-007
 */

#include <stdio.h>
#include <stdlib.h>

struct{ //Struct com int (valor) e pointeiro (* next) para o proximo valor da lista
    int value;
    struct linkedList * next;
} typedef linkedList;

//Função para iniciar a lista em NULL
linkedList * newList(){
    return NULL;
}

//Função para adicionar um valor a lista passada pelos parametros
linkedList * addList(linkedList * list, int val){
    linkedList * newList = (linkedList *) malloc(sizeof (linkedList));
    //Função malloc aloca um espaço da memoria do tamanho da struct linkedList
    if(newList != NULL){
        //se a alocação ocorrer corretamente ela retornara um valor de memoria diferente de NULL
        newList->value = val; //guardando o valor dos paramentros na struct
        newList->next = (struct linkedList *) list; //atribuindo o ponteiro para a struct anterior
        return newList; //retornando a nova struct criada aqui
    }
    return NULL; //caso não tenha sido possivel a alocação de memoria
}
//Função desenvolvida para pegar a primeira posição da lista antes de NULL:
//Lista1:  {8}->{5}->{3}->{6}->{9}->NULL
//getList(lista1) : {9}->NULL
//Por enquanto essa função é utilizada apenas para adicionar um valor no fim da lista entre o primeiro valor e o NULL
linkedList * getList(linkedList * list){
    linkedList * novaList = list;
    while(novaList->next!=NULL){
        novaList = novaList->next;
    }
    return novaList;
}


//Função para calcular o tamanho de uma lista passada nos parametros
int getSize(linkedList * list){
    //criasse uma variavel (size), e a lista vai sendo percorrida até que chegue no primeiro valor, antes
    //do NULL, e a cada iteração com a lista a variavel size incrementa 1, portanto quando percorrer a lista
    //toda size tera o tamanho da lista, lembrando que por convenção a contagem começa em 0, portanto
    //se size retornar 9 quer dizer que a lista tem 10 valores
    int size = 0;
    while(list->next!=NULL){
        list = (linkedList *) list->next;
        size+=1;
    }
    return size;
}


//Função para retornar o valor de uma certa posição da lista passada nos parametros
//utilizando-se da função anteriror a essa, (a getSize()), é calculado o tamanho da lista
//e subtraido a posição da qual solicitada, por exemplo, se eu quiser o valor da posição 3 de uma lista de tamanho 8
//(7 contando com o 0) então é calculado 7-3= 4, portanto e o quantidade de vezes que eu tenho que percorrer a lista
//{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
// 0º   1º   2º   3º   4º   5º   6º   7º
//Assim retornando o valor 2 na posição 4
int get(linkedList * list, int pos ){
    int i, item =getSize(list)-pos; //Aqui é feito o calculo para determinar quantas iteraçõs são necessarias
    if(item<0){ //caso o calculo resulte em menos que zero, quer dizer que foi passado um valor maior que o tamanho da lista
        printf("\nA lista e menor que %d, retornando ultimo valor da lista.\n", pos);
    }
    for(i = 0; i<item; i++){//aqui é percorrido a lista de acordo com o a quantidade de iterações previamente calculado
        list = (linkedList *) list->next; //o for loop tem a condição "i<item" sendo assim o fator limitador de iterações
    } //mas tambem, caso ele seja falso a principio, o loop não e rodado, e o loop sera falso quando i (que vale zero)
      //for maior ou igual ao item, se item for menor que zero já foi previamente cuidado pelo if acima,
      //agora se item for igual a 0 quer dizer que a subtração acima resultou em zero, portanto o ultimo valor a ter sido adicionado
    return list->value;//sendo assim o loop não é percorrido e é retornado o ultimo valor, sem mexer na lista.
}

//Metódo para dividir a lista em relação a uma posição
//se eu tenho uma lista : {1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
//e quero dividi-la em duas partes em relação ao 2
//sobra duas listas {1}->{0}->{9}->{7}->{2}-> e {3}->{4}->{5}->NULL
//como não é possivel retornar um vetor de uma função em C eu decidi colocar a escolha da lista resultante nos
//parametros, sendo assim você escolhe qual parte você quer, 0 ou 1
linkedList * sliptListAt(linkedList * list, int pos, int resultList){
    //como iremos manipular a lista, é necessario ter uma copia dela, como estamos mexendo com ponteiros
    //qualquer mudança que eu fizer na lista original se aplica as duas novas
    linkedList * newListZero = list;
    linkedList * newListOne = list;
    int i, item =getSize(list)-pos; //novamente mesma logica para determinar a posição, feita no metodo, get()
    for(i = 0; i<item; i++){
        //lembrando que a lista é uma corrente, que se liga de uma ponta a outra
        //quando pegamos a lista na possição que ela está, tem toda a corrente para frente, e do jeito que foi feita
        //não é possivel saber qual valor está antes dela, pegando o exemplo anterior
        //{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL se eu pegar essa lista, eu sei todos os valores depois de 1
        //mas se eu mexer a lista pra 2º posição ({9}->), eu não tenho como acessar a lista antiga
        //resultado :{9}->{7}->{2}->{3}->{4}->{5}->NULL
        //sabendo disso, no codigo abaixo, estou atualizando a posição da variavel, atribuindo o ponteiro
        //da proxima corrente da lista a ela mesmo
        //{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
        //{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
        //{9}->{7}->{2}->{3}->{4}->{5}->NULL
        list = (linkedList *) list->next;
        newListZero = (linkedList *) list->next;
        //e estou tambem atualizando o valor da variavel newListZero, mas lembra que a variavel newListOne
        //foi declarado como uma copia anteriormente, e não estamos mexendo com ela?
        //então, idiferente onde que a variavel lista está, por exemplo :{9}->{7}->{2}->{3}->{4}->{5}->NULL
        //a variavel newListOne continua no inicio da lista {1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
    }
    //quando as iterações acaberem, quer dizer que chegamos na posição na qual que queremos dividir a lista
    //mas a lista ainda continua apartir dela, então quebramos a corrente aqui declarando que o ponteiro para
    //o proximo nó é NULL
    list->next = NULL;// ou seja {9}->NULL
    //mas lembra que eu valei que as variaveis newListOne e newListZero como são com ponteiros
    // se a lista principal (na memoria, não a variavel) sofrer uma alteração elas tambem sofreram?
    //então o resultado ficou assim:
    if(resultList==1){
        return newListOne; //{1}->{0}->{9}->NULL
    }else if(resultList == 0){
        return newListZero;//{7}->{2}->{3}->{4}->{5}->NULL
    }

}

//Essa função eu fiz pra praticar mesmo, basicamente, ela organiza a lista em ordem crescente
//{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL fica {0}->{1}->{2}->{3}->{4}->{5}->{7}->{9}->NULL
//não é muito complexo como fazer isso, eu decidi fazer utilizando de um vetor, como sabemos o tamanho da lista atravez
//do metodo getSize(), é possivel criar um vetor do mesmo tamanho
//e por fim um loop dentro com o a quantidade de iterações sendo o tamanho da lista
//e comparando com um if e uma variavel auxiliar, dps que terminar de ordenar o vetor, basta percorrelo atribiundo
//cada valor a uma lista nova usando o metodo addList()
linkedList * sort(linkedList * list){
    linkedList * listCopy;
    listCopy = newList();
    int i,j=1,size = getSize(list), listAsArray[size];
    for (i = 0; i <= size; i++) {
        listAsArray[i] = get(list, i);
    }
    for (int k = 0; k <= size; ++k) {
        j = 1;
        for (i = 0; i < size; i++, j++) {
            if (listAsArray[i] < listAsArray[j]) {
                int aux = listAsArray[j];
                listAsArray[j] = listAsArray[i];
                listAsArray[i] = aux;
            }
        }
    }
    for (i = 0; i <=size ; i++) {
        listCopy = addList(listCopy, listAsArray[i]);
    }
    free(list); //metodo para limpar a lista antiga da memoria já que ela mudou
    return listCopy;
}

//Metodo para remover um valor de uma certa posição da lista
linkedList * removeAt(linkedList * list, int pos) {
    linkedList *oldList = list; //copia da lista
    linkedList *nextItemOnList; //proximo valor do qual será removido
    nextItemOnList = NULL; //atribuição de NULL para ele
    //se temos essa lista: {1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
    // e quero remover o valor da 3º posição (o 7) e manter a lista
    // eu preciso editar o valor do nó da 2º posição para apontar para o nó da 4º posição
    //considerando que eventualmente possa querer remover o valor da 7º, oque eu aponto para o NULL
    //e necessario que o valor da 6º possição tambem aponte para o NULL, assim terminando a lista
    //por isso que primeiro eu atribui o valor de NULL para nextItemOnList
    int i, item = getSize(list) - pos; //lembra do código para saber quantas iterações é necessario para
    for (i = 1; i < item; i++){       //chegar na posição desejada, olha ele aqui denovo
        list = (linkedList *) list->next; //movendo a lista de posição
    }
    if (item >= 1) { //caso o resultado da posição seja maior que 1 ou seja uma posição antes da primeira (7-3=4 em
        // relação ao exemplo anterior),
        linkedList *itemToRemove;  //criado o novo nó para lista, no qual é o item a ser removido
        itemToRemove = list->next; //o item a ser removido é o proximo de onde a lista está, o porque ?
        // se você reparar no loop acima, ele começo com i valendo 1 ou seja uma iteração a menos
        //pois se eu chegar na posição a ser removida, eu não saberei qual é a anterior para apontar para o proximo nó
        if (itemToRemove->next != NULL) {//se o proximo item, depois do que vai ser removido da lista for NULL
            //quer dizer que está no fim da lista, portanto não é necessario atualizar a variavel nextItemOnList
            //caso for diferente de NULL é necessario atualiza-la, como é feito abaixo
            nextItemOnList = itemToRemove->next;
            list->next = nextItemOnList;//apos isso a lista que lembrando, está um nó anterior ao ser removido
            // aponta para o proximo nó, assim dessasociado o nó da lista antiga
            //{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL  - lista original
            //               {7}->                          - nó a ser removido
            //{1}->{0}->{9}->---->{2}->{3}->{4}->{5}->NULL  - lista dps do nó ser removido
            // basicamente separando o nó da lista
            free(itemToRemove);//e por fim apagando ele da memoria
            return oldList;
        } else {//caso o proximo nó seja NULL
            list->next = nextItemOnList; //o proximo nó da lista é o nextItemOnList, que continua NULL
            free(itemToRemove); //e o item é removido da memoria
            //{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL  - lista original
            //                                   {5}->NULL  - nó a ser removido
            //{1}->{0}->{9}->{7}->{2}->{3}->{4}->---->NULL  - lista dps do nó ser removido
            return oldList;
        }
    }if(item == 0){//se item for igual a zero quer dizer que foi solocitado a remoção do primeiro nó da lista
        //como por padrão ele teoricamente vai apontar para o proximo numero é redundante fazer
        //essa verificação, mas uma lista de um valor ainda continua sendo uma lista
        if (list->next != NULL) {
            nextItemOnList = list->next;//proximo item da lista é atribuido ao nextItemOnList
            list->next = nextItemOnList; //lembrando que item sendo 0 o loop não foi percorrido
            //{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL  - lista original
            //{1}->                                        - nó a ser removido
            //     {0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL - lista dps do nó ser removido
            free(list);
            return nextItemOnList;
        }else {//caso o proximo nó seja NULL
            list->next = nextItemOnList; //o proximo nó da lista é o nextItemOnList, que continua NULL
            free(list); //e o item é removido da memoria
            //{1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL  - lista original
            //                                   {5}->NULL  - lista original
            //{1}->{0}->{9}->{7}->{2}->{3}->{4}->---->NULL  - lista dps do nó ser removido
            return oldList;
        }
    }

}

//Metodo para adicionar um valor ao começo da lista
//Exemplo: {1}->{0}->{9}->{7}->{2}->{3}->{4}->{5}->NULL
//caso eu queria adicionar um nó entre o {5}-> e o NULL
linkedList * addAtStart(linkedList * list, int val){
    linkedList * newListToAdd = newList(); //eu preciso criar o nó como se fosse uma lista nova
    newListToAdd = addList(newListToAdd, val); //adiciono o valor a essa nova lista
    linkedList * oldList = list;// copia a lista antiga a uma variavel, lembrando que se na memoria a lista for atualizada
    //essa variavel como é um ponteiro e compartilha a mesma memoria tambem será atualizada
    list = getList(list);//função para percorrer a lista até a primeira casa
    list->next = newListToAdd;//atualiza o nó da primeira casa para apontar para a nova lista criada acima
    return oldList; //retorna a copia da lista que a posição está no começo
}

//Metodo para imprimir a lista, ele percorre um loop imprimindo o valor enquanto for diferente de NULL
void printList(linkedList * L ){
    while(L!=NULL){
        printf("[%d]->", L->value);
        L = L->next; //se deslocando na 'corrente' da lista
    }
}

int main() {
    //Utilizando os metodos:
    linkedList * L;
    L = newList();
    L = addList(L, 5);
    L = addList(L, 4);
    L = addList(L, 2);
    L = addList(L, 7);
    L = addList(L, 20);
    printList(L);
    printf("\nValor posicao 5: %d\n", get(L, 5));
    L = addAtStart(L, 3);
    printList(L);
    printf("\nValor posicao 2: %d\n", get(L, 2));
    linkedList * L2;
    L2 = newList();
    L2 = addList(L2, 5);
    L2 = addList(L2, 4);
    L2 = addList(L2, 2);
    L2 = addList(L2, 7);
    L2 = addList(L2, 20);
    L2 = addAtStart(L2, 3);
    printf("\nLista L: ");
    L = sliptListAt(L, 3, 1);
    printList(L);
    printf("\nLista L2: ");
    L2 = sliptListAt(L2, 3, 0);
    printList(L2);
    L = removeAt(L, 0);
    printf("\nLista L dps de remover: ");
    printList(L);
    linkedList * L3;
    L3 = newList();
    L3 = addList(L3, 10);
    L3 = addList(L3, 3);
    L3 = addList(L3, 6);
    L3 = addList(L3, 2);
    L3 = addList(L3, 250);
    L3 = addList(L3, 7);
    L3 = addList(L3, 15);
    L3 = addList(L3, 69);
    L3 = addList(L3, -10);
    printf("\nLista original: ");
    printList(L3);
    printf("\nLista organizada:");
    L3 = sort(L3);
    printList(L3);
}
