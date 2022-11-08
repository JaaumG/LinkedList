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
LinkedList * ProximoItem(LinkedList list){
    return (LinkedList *) list.next;
}

int get(LinkedList * list, int pos ){
    LinkedList * novaList = list;
    int size = 0;
    while(novaList!=NULL){
        size+=1;
        novaList = novaList->next;
    }
    int i;
    novaList = list;
    for(i = 0; i++; i<size-pos){
        novaList = novaList->next;
    }
    return novaList->value;
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
    L = InserirLista(L, 10);
    L = InserirLista(L, 10);
    L = InserirLista(L, 100);
    L = InserirLista(L, 1000);
    L = InserirLista(L, 10000);
    ImprimeList(L);
    printf("\n%d", get(L, 2));
}
