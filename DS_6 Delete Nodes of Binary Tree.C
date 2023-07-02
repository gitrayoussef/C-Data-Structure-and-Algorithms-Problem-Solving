#include <STDIO.H>
#include <CONIO.H>
#include <STDLIB.H>
#include <STRING.H>
#define yAdd 1
#define ySum 2
#define yFree 3
#define yExit 4

struct node
{
 int data;
 struct node* pPrev;
 struct node* pNext;

};

struct node* rNode;
int sum;

void printMenu(void);
struct node* createNode(int data);
struct node* insertNode(struct node* ptr,int data);
int calcSum(struct node* rNode);
int freeTree(struct node* root);


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
    if(y<4) y=y+1;
    gotoxy(x,y);
    break;

   case 71:
    y=1;
    gotoxy(x,y);
    break;

   case 79:
    y=4;
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

     case ySum:
     {
      clrscr();
      sum=calcSum(rNode);
      printf("%d",sum);
      break;
     }

     case yFree:
     {
      int success=0;
      clrscr();
      success=freeTree(rNode);
      if(success)
      {
       sum=0;
       rNode=NULL;
       printf("Tree deleted successfully");
      }
      else
      {
       printf("Failed to delete Tree");
      }
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
 printf("%d- Calculate Sum\n",ySum);
 printf("%d- Free Tree\n",yFree);
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


int calcSum(struct node* ptr)
{
 if(ptr!=NULL)
 {
  calcSum(ptr->pPrev);
  sum+=ptr->data;
  calcSum(ptr->pNext);
 }

 return sum;
}


int freeTree(struct node* root)
{
 int success=0;
 if(root!=NULL)
 {
  freeTree(root->pPrev);
  freeTree(root->pNext);
  printf("Done\n");
  free(root);
  success=1;
 }
 return success;
}

