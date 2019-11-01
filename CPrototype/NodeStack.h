struct nodeStack {
  // -1 for empty, array index otherwise
  int height;
  // array of pointers to nodes
  struct node** node;
};

struct nodeStack* initNodeStack();
void clearNodeStack(struct nodeStack*);
enum boolean isEmptyNode(struct nodeStack*);
void pushNode(struct nodeStack*, struct node*);
struct node* popNode(struct nodeStack*);

