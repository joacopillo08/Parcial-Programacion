#include <stdio.h>
#include <stdlib.h>

#include "definiciones.h"



int main() {

Nodo *root = createNodo(10);

printf("El padre de root es: %p\n", root->parent); 

root->child1 = createNodo(20); 
root->child1->parent = root;
root->child2 = createNodo(25); 
root->child2->parent = root; 

Nodo *foundNodo = searchNodo(root, 20); 
if (foundNodo != NULL) {
    printf("Nodo encontrado: %d\n", foundNodo->dato);
} else {
    printf("Nodo no encontrado\n");
}

    printf("Arbol: \n");
    printTree(root);
    printf("\n");


insChild(&root, 25, 26);
insChild(&root, 20, 21);
insChild(&root, 25, 27);

insChild(&root, 21, 22);

Nodo *parent = searchNodo(root, 25); 
if (parent != NULL && parent->child1 != NULL){
printf("El hijo del nodo padre %d es: %d\n",parent->dato, parent->child1->dato); 
}


    printf("Arbol: \n");
    printTree(root);
    printf("\n");

printNodeData(root, 26);

printf("Los nodos que no tienen hijos son:\n");
printLeafs(root);

freeTree(root);
/*
Eliminar una rama del arbol
delBranch(root, 20);
*/

/*
Si imprime cualquier cosa es que la memoria se libero
   printf("Arbol: \n");
    printTree(root);
    printf("\n");
*/

/*
Creo devuelta y veo si imprime y crea bien todo

root = createNodo(0);
insChild(&root, 0, 1);
insChild(&root, 0, 2);
insChild(&root, 1, 3);

   printf("Arbol: \n");
    printTree(root);
    printf("\n");
*/
    return 0; 
}

Nodo *createNodo(int nuevoDato) {

    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));

    if(!nuevoNodo) {
        printf("Error en la creacion del nodo"); 
        exit(1);
    }
nuevoNodo->dato = nuevoDato;
nuevoNodo->parent = NULL;
nuevoNodo->child1 = NULL;
nuevoNodo->child2 = NULL; 

return nuevoNodo; 
}

Nodo *searchNodo(Nodo *currentNodo, int searchedValue){

if (currentNodo == NULL) {
    return NULL; 
}

if (currentNodo->dato == searchedValue) {
    return currentNodo;
}

Nodo* result = searchNodo(currentNodo->child1, searchedValue);
if(result != NULL) {
    return result; 
} 

result = searchNodo(currentNodo->child2, searchedValue);
if(result != NULL) {
    return result; 
} 

return NULL;
}

void insChild(Nodo **root, int parentNodeValue, int newValue) {

Nodo* parent = searchNodo(*root, parentNodeValue);  

if (parent == NULL){
    printf("El nodo padre no existe con el valor %d", parentNodeValue);
}

Nodo *newChild = createNodo(newValue); 

if(parent->child1 == NULL) {
    parent->child1 = newChild; 
    newChild->parent = parent; 
} else if (parent->child2 == NULL) {
    parent->child2 = newChild; 
    newChild->parent = parent; 
} else {
    printf("El nodo padre %d ya tiene dos hijos", parentNodeValue); 
}


}

void printTree(Nodo *root) {
    if (root == NULL) {
       return;
    }
    printf("  %d", root->dato);

printBranch(root->child1, 1);
printBranch(root->child2, 1);

}

void printBranch(Nodo *root, int level) {
if (root == NULL){
    return; /*aca veo si el root es nulo entonces no hay nada*/
}
    printf("\n");

for(int i = 0; i < level; i++) {
    printf("  ");
}
    printf("L %d", root->dato);

printBranch(root->child1, level + 1);
printBranch(root->child2, level + 1);

}

/* Encontar un nodo en particular e imprimir su informacion void printNodeData(Node *RootNode, int searchedValue); */

void printNodeData(Nodo *currentNodo, int searchedValue){

Nodo* result = searchNodo(currentNodo, searchedValue);

if (result != NULL){
    printf("El valor del nodo es: %d\n", result->dato);
    if (result->parent != NULL) {
        printf("El valor del nodo padre es %d\n",result->parent->dato);
    } else {
        printf("Este nodo no tiene padre, ya es la raiz\n");
    } 
    if (result->child1 != NULL){
        printf("El valor del hijo izquierdo es %d\n",result->child1->dato);
    } else {
        printf("Este nodo no tiene hijo izquierdo\n");
    }
    if (result->child2 != NULL){
        printf("El valor del hijo derecho es %d\n",result->child2->dato);
    } else {
        printf("Este nodo no tiene hijo derecho\n");
    }
} else {
    printf("Este nodo: %d no existe\n", searchedValue);
}

}

void freeTree(Nodo *currentNodo){

if(currentNodo == NULL){
    return;
}

freeTree(currentNodo->child1);
freeTree(currentNodo->child2);

free(currentNodo);
}


/*Borrar una rama y liberar la memoria de todos sus hijos*/
void delBranch(Nodo *currentNodo, int searchedValue){

Nodo* result = searchNodo(currentNodo, searchedValue);

if (result ==  NULL) {
    printf("El nodo %d no fue encontrado\n", searchedValue);
    return;
}

/*Si el nodo tiene un padre, lo desvinculo*/
if (result->parent != NULL) {
    if (result->parent->child1 == result) {
        result->parent->child1 = NULL;
    } else if (result->parent->child2 == result) {
    result->parent->child2 = NULL;
    }

}

freeTree(result); /* Uso freetree para liberar la rama entera*/
}


/*Imprimir todos los nodos que no tienen ningun hijo*/
void printLeafs(Nodo *currentNodo){

if (currentNodo ==   NULL) {
    printf("El nodo no fue encontrado\n");
    return;
}


if (currentNodo->child1 == NULL && currentNodo->child2 == NULL){
    printf("Este nodo %d no tiene hijos\n", currentNodo->dato); 
} else {
    if (currentNodo->child1 != NULL) {
        printLeafs(currentNodo->child1);
    }
 if (currentNodo->child2 != NULL) {
        printLeafs(currentNodo->child2);
    }

}
}

