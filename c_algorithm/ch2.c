//

char* files[10];


typedef int ElementType;

struct Node 
{
    ElementType Data; //data
    struct Node NextNode;
};

struct Node MyNode;

typedef struct tNode
{
    ElementType Data;
    struct tNode NextNode;
}Node;