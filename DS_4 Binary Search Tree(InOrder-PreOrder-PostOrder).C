#include <STDIO.H>
#include <CONIO.H>
#include <STDLIB.H>
#include <STRING.H>
#define yAdd 1
#define yPrintInOrder 2
#define yPrintPreOrder 3
#define yPrintPostOrder 4
#define yExit 5

struct node
{
 int data;
 struct node* pPrev;
 struct node* pNext;

};

struct node* rNode;

void printMenu(void);
struct node* createNode(int data);
struct node* insertNode(struct node* ptr,int data);
void printInOrder(struct node* rNode);
void printPreOrder(struct node* rNode);
void printPostOrder(struct node* rNode);


int main()
{
 int x=1 , y=1 , app=1 , character;

 clrscr();

 printMenu();

 gotoxy(x,y);

 while(app)
 {
  character=getch();

  if(character==0) character=getch();

  switch(character)
  {
   case 72:
    if(y>1) y=y-1;
    gotoxy(x,y);
    break;

   case 80:
    if(y<5) y=y+1;
    gotoxy(x,y);
    break;

   case 71:
    y=1;
    gotoxy(x,y);
    break;

   case 79:
    y=5;
    gotoxy(x,y);
    app=0;
    break;

   case 27:
    x=1;
    y=1;
    clrscr();
    printMenu();
    gotoxy(x,y);
    break;

   case 13:
    switch(y)
    {
     case yAdd:
     {
      int data;
      clrscr();
      printf("Enter Node Data: ");
      scanf("%d",&data);
      rNode=insertNode(rNode,data);
      printf("Node created successfully");
      break;
     }

     case yPrintInOrder:
     {
      clrscr();
      printInOrder(rNode);
      break;
     }

     case yPrintPreOrder:
     {
      clrscr();
      printPreOrder(rNode);
      break;
     }

     case yPrintPostOrder:
     {
      clrscr();
      printPostOrder(rNode);
      break;
     }

     case yExit:
      app=0;
      break;
    }
    break;
  }
 }

 return 0;
}


void printMenu(void)
{
 printf("%d- Add Node\n",yAdd);
 printf("%d- Order Nodes InOrder\n",yPrintInOrder);
 printf("%d- Order Nodes PreOrder\n",yPrintPreOrder);
 printf("%d- Order Nodes PostOrder\n",yPrintPostOrder);
 printf("%d- Exit\n",yExit);
}


struct node* createNode(int data)
{
 struct node* ptr;
 ptr=(struct node*)malloc(sizeof(struct node));
 if(ptr)
 {
  ptr->data=data;
  ptr->pPrev=ptr->pNext=NULL;
 }
 return ptr;
}


struct node* insertNode(struct node* ptr,int data)
{

 if(ptr==NULL)
 {
  return createNode(data);
 }
 else
 {
  if(ptr->data < data)
  {
   ptr->pNext=insertNode(ptr->pNext,data);

  }
  else
  {
   ptr->pPrev=insertNode(ptr->pPrev,data);
  }
 }
 return ptr;
}


void printInOrder(struct node* ptr)
{
 if(ptr == NULL)return;
 printInOrder(ptr->pPrev);
 printf("%d",ptr->data);
 printInOrder(ptr->pNext);
}


void printPreOrder(struct node* ptr)
{
 if(ptr == NULL)return;
 printf("%d",ptr->data);
 printPreOrder(ptr->pPrev);
 printPreOrder(ptr->pNext);
}

void printPostOrder(struct node* ptr)
{
 if(ptr == NULL)return;
 printPostOrder(ptr->pPrev);
 printPostOrder(ptr->pNext);
 printf("%d",ptr->data);
}