#include <stdio.h>
#include <stdlib.h>

struct{
    int value;
    struct LinkedList * next;
} typedef LinkedList;
LinkedList * newList(){
    return NULL;
}
LinkedList * addList(LinkedList * list, int val){
    LinkedList * newList = (LinkedList *) malloc(sizeof (LinkedList));
    if(newList != NULL){
        newList->value = val;
        newList->next = (struct LinkedList *) list;
        return newList;
    }
    return NULL;
}
LinkedList * getList(LinkedList * list){
    LinkedList * novaList = list;
    while(novaList->next!=NULL){
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

LinkedList * sliptListAt(LinkedList * list, int pos, int resultList){
    LinkedList * newListZero = list;
    LinkedList * newListOne = list;
    int i, item =getSize(list)-pos;
    for(i = 0; i<item; i++){
        list = (LinkedList *) list->next;
        newListZero = (LinkedList *) list->next;
    }
    list->next = NULL;
    if(resultList==1){
        return newListOne;
    }else if(resultList == 0){
        return newListZero;
    }

}

LinkedList * removeAt(LinkedList * list, int pos) {
    LinkedList *oldList = list;
    int i, item = getSize(list) - pos;
    LinkedList *nextItemOnList;
    nextItemOnList = NULL;
    for (i = 1; i < item; i++) {
        list = (LinkedList *) list->next;
    }
    if (item >= 1) {
        LinkedList *itemToRemove;
        itemToRemove = list->next;
        if (itemToRemove->next != NULL) {
            nextItemOnList = itemToRemove->next;
            list->next = nextItemOnList;
        } else {
            nextItemOnList = NULL;
            list->next = nextItemOnList;
        }
        free(itemToRemove);
        return oldList;
    }else{
        if (list->next != NULL) {
            nextItemOnList = list->next;
            list->next = nextItemOnList;
        } else {
            nextItemOnList = NULL;
            list->next = nextItemOnList;
        }
        free(list);
        return nextItemOnList;
    }


}

LinkedList * addAtStart(LinkedList * list, int val){
    LinkedList * newListToAdd = newList();
    newListToAdd = addList(newListToAdd, val);
    LinkedList * oldList = list;
    list = getList(list);
    list->next = newListToAdd;
    return oldList;
}


void printList(LinkedList * L ){
    while(L!=NULL){
        printf("[%d]->", L->value);
        L = L->next;
    }
}

int main() {
    LinkedList * L;
    L = newList();
    L = addList(L, 1);
    L = addList(L, 10);
    L = addList(L, 100);
    L = addList(L, 1000);
    L = addList(L, 10000);
    printList(L);
    printf("\nValor posicao 5: %d\n", get(L, 5));
    L = addAtStart(L, 5);
    printList(L);
    printf("\nValor posicao 2: %d\n", get(L, 2));
    LinkedList * L2;
    L2 = newList();
    L2 = addList(L2, 1);
    L2 = addList(L2, 10);
    L2 = addList(L2, 100);
    L2 = addList(L2, 1000);
    L2 = addList(L2, 10000);
    L2 = addAtStart(L2, 5);
    printf("\nLista L: ");
    L = sliptListAt(L, 3, 1);
    printList(L);
    printf("\nLista L2: ");
    L2 = sliptListAt(L2, 3, 0);
    printList(L2);
    L = removeAt(L, 2);
    printf("\nLista L dps de remover: ");
    printList(L);
}
