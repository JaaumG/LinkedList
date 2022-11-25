#include <stdio.h>
#include <stdlib.h>
struct{
    int value;
    struct LinkedList * next;
} typedef LinkedList;

LinkedList * InicializarLista(){
    return NULL;
}
LinkedList * InserirLista(LinkedList * list, int val){
    LinkedList * novaList = (LinkedList *) malloc(sizeof (LinkedList));
    if(novaList!=NULL){
        novaList->value = val;
        novaList->next = (struct LinkedList *) list;
        return novaList;
    }

}
LinkedList * getList(LinkedList * list){
    LinkedList * novaList = list;
    int size = 0;
    while(novaList->next!=NULL){
        size+=1;
        novaList = novaList->next;
    }
    return novaList;
}
int getSize(LinkedList * list){
    int size = 0;
    while(list->next!=NULL){
        list = (LinkedList *) list->next;
        size+=1;
    }
    return size;
}

/*
 * Retorna o valor da lista na possição passada nos parametros
 */
int get(LinkedList * list, int pos ){
    int i, item =getSize(list)-pos;
    if(item<0){
        printf("\nA lista e menor que %d, retornando ultimo valor da lista.\n", pos);
    }
    for(i = 0; i<item; i++){
        list = (LinkedList *) list->next;
    }
    return list->value;
}


LinkedList * InserirComecoLista(LinkedList * list, int val){
    LinkedList * novaList = InicializarLista();
    novaList = InserirLista(novaList, val);
    LinkedList * oldList = list;
    list = getList(list);
    list->next = (struct LinkedList *) novaList;
    return oldList;
}
LinkedList * ProximoItem(LinkedList list){
    return (LinkedList *) list.next;
}


void ImprimeList(LinkedList * L ){
    while(L!=NULL){
        printf("[%d]->", L->value);
        L = L->next;
    }
}

int main() {
    LinkedList * L;
    L = InicializarLista();
    L = InserirLista(L, 1);
    L = InserirLista(L, 10);
    L = InserirLista(L, 100);
    L = InserirLista(L, 1000);
    L = InserirLista(L, 10000);
    ImprimeList(L);
    printf("\nvalor: %d\n", get(L, 5));
    L = InserirComecoLista(L, 5);
    ImprimeList(L);
    printf("\n%d\n", get(L, 2));
}
