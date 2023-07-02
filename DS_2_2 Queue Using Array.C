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

struct student ar[50];
int soq;
int eoq;

void printMenu(void);
struct student fillStudentData(void);
int push(struct student std);
struct student* pop(void);
void printPopedStudent(struct student *std);
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
      struct student *pStd;
      pStd = pop();
      clrscr();
      printPopedStudent(pStd);
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
 int retval=0;
 if(soq<50)
 {
  ar[eoq]=std;
  eoq++;
  retval=1;
 }
 return retval;
}


struct student* pop(void)
{
 struct student std,*pStd;
 pStd=&std;
 if(eoq>0)
 {
  pStd=&ar[soq];
  soq++;
 }
 return pStd;
}


void printPopedStudent(struct student *pStd)
{
 int i=0;
 printf("Student's ID= %d\n",pStd->id);
 printf("Student's Name= %s\n",pStd->name);
 for(i=0;i<3;i++)
 {
  printf("Student's Subject[%d] Grade= %d\n",i+1,pStd->grades[i]);
 }
}


void freelist(void)
{
 int i;
 if(eoq>0)
 {
  for(i=soq;i<eoq;i++)
  {
   pop();
  }
 }
}



void listStudents(void)
{
 int i,j;
 if(eoq>0)
 {
  for(i=soq;i<eoq;i++)
  {
   printf("Student's ID= %d\n",ar[i].id);
   printf("Student's Name= %s\n",ar[i].name);
   for(j=0;j<3;j++)
   {
    printf("Student's Subject[%d] Grade= %d\n",j+1,ar[i].grades[j]);
   }
   printf("**********************\n");
  }
 }
 if(eoq==0||eoq==soq)
 {
  printf("There's no Students");
 }
}