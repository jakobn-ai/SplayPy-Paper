struct boolStack {
  // -1 for empty, array index otherwise
  int height;
  // position in char
  unsigned char frameIdx;
  // array of chars, each of which hold 8 bools
  unsigned char* payload;
};

struct boolStack* initBoolStack();
void clearBoolStack(struct boolStack*);
enum boolean isEmptyBool(struct boolStack*);
void pushBool(struct boolStack*, enum boolean);
enum boolean popBool(struct boolStack*);

