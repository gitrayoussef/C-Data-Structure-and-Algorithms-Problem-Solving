#include <STDIO.H>
#include <CONIO.H>
#include <STDLIB.H>
#include <STRING.H>
#define yPush 1
#define yPop 2
#define yFreelist 3
#define yListStudents 4
#define yExit 5


struct student
{
 int id;
 char name[20];
 int grades[3];
};

struct node
{
 struct student std;
 struct node *pNext;
};

struct node *pHead;
struct node *pTail;

void printMenu(void);
struct student fillStudentData(void);
int push(struct student std);
struct node* pop(void);
void printPopedStudent(struct node* ptr);
void freelist(void);
void listStudents(void);

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
     case yPush:
     {
      struct student std;
      int retval;
      std =fillStudentData();
      retval=push(std);
      if(retval)
      {
       printf("Student inserted successfully");
      }
      else
      {
       printf("Not Found");
      }
      break;
     }

     case yPop:
     {
      struct node* ptr;
      ptr =pop();
      clrscr();
      if(ptr)
      {
       printPopedStudent(ptr);
      }
      else
      {
       printf("Students' List is empty");
      }
      break;
     }

     case yFreelist:
      freelist();
      clrscr();
      printf("Students' List deleted successfully");
      break;

     case yListStudents:
     {
      clrscr();
      listStudents();
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
 printf("%d- Add a Student\n",yPush);
 printf("%d- Pop a Student\n",yPop);
 printf("%d- Free Students' List\n",yFreelist);
 printf("%d- List all Students\n",yListStudents);
 printf("%d- Exit\n",yExit);
}


struct student fillStudentData()
{
 struct student std;
 int i;
 clrscr();
 printf("Insert Student's ID: ");
 scanf("%d",&std.id);
 printf("Insert Student's Name: ");
 scanf("%s",std.name);
 for(i=0;i<3;i++)
 {
  printf("Insert Student's Grade at Subject[%d]: ",i+1);
  scanf("%d",&std.grades[i]);
 }
 return std;
}


int push(struct student std)
{
 struct node *ptr;
 int i=0,retval=0;
 ptr = (struct node*)malloc(sizeof(struct node));
 if(ptr)
 {
  ptr->std.id=std.id;
  strcpy(ptr->std.name,std.name);
  for (i=0;i<3;i++)
  {
   ptr->std.grades[i]=std.grades[i];
  }
  ptr->pNext=NULL;
  if(!pHead)
  {
   pHead=pTail=ptr;
  }
  else
  {
   pTail->pNext=ptr;
   pTail=ptr;
  }
  retval=1;
 }
 return retval;
}


struct node* pop(void)
{
 struct node* ptr=NULL;
 if(pHead)
 {
  ptr=pHead;
  if(pHead==pTail)
  {
   pHead=pTail=NULL;
  }
  else
  {
   while(ptr->pNext!=pTail)
   {
    ptr=ptr->pNext;
   }
   pTail=ptr;
   ptr=pTail->pNext;
   pTail->pNext=NULL;
  }
 }
 return ptr;
}


void printPopedStudent(struct node* ptr)
{
 int i=0;
 printf("Student's ID= %d\n",ptr->std.id);
 printf("Student's Name= %s\n",ptr->std.name);
 for(i=0;i<3;i++)
 {
  printf("Student's Subject[%d] Grade= %d\n",i+1,ptr->std.grades[i]);
 }
}


void freelist(void)
{
 struct node* ptr;
 while(pHead)
 {
  ptr=pHead;
  pHead=ptr->pNext;
  free(ptr);
 }
 pTail=NULL;
}



void listStudents(void)
{
 struct node* ptr;
 int i;
 ptr=pHead;
 if(!pHead)
 {
  printf("No Available Students");
 }
 else
 {
  while(ptr)
  {
   printf("Student's ID= %d\n",ptr->std.id);
   printf("Student's Name= %s\n",ptr->std.name);
   for(i=0;i<3;i++)
   {
    printf("Student's Subject[%d] Grade= %d\n",i+1,ptr->std.grades[i]);
   }
   printf("**********************\n");
   ptr= ptr->pNext;
  }
 }
}