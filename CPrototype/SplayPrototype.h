struct node* initTree();
void clearTree(struct node*);
void showTree(struct node*, char* (*)(void*));
struct node* insert(struct node*, void*, enum order (*)(void*, void*));

