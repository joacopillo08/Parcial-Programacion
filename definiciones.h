typedef struct Nodo {
    int dato; 
    struct Nodo *parent; 
    struct Nodo *child1;
    struct Nodo *child2;  
}Nodo; 

Nodo *searchNodo(Nodo *currentNodo, int searchedValue); 

Nodo *createNodo(int nuevoDato) ;

void insChild(Nodo **rootNodo, int parentNodeValue, int newValue);

void printTree(Nodo *root); 

void printBranch(Nodo *root, int level);

void printNodeData(Nodo *currentNodo, int searchedValue);

void freeTree(Nodo *currentNodo);

void delBranch(Nodo *currentNodo, int searchedValue);

void printLeafs(Nodo *currentNodo);

