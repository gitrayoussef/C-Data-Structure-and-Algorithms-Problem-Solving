#include <STDIO.H>
#include <CONIO.H>
#include <STDLIB.H>
#include <STRING.H>
#define yAdd 1
#define ySearchById 2
#define ySearchByName 3
#define yDeleteById 4
#define yFreelist 5
#define yInsertByLoc 6
#define yUpdateById 7
#define yListStudents 8
#define yExit 9

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
 struct node *pPrev;
};

struct node *pHead;
struct node *pTail;

void printMenu(void);
struct student fillStudentData(void);
struct node* createStudent(struct student std);
int addStudent(struct student std);
int fillRequiredId(void);
struct node* searchById(int id);
char* fillRequiredName(void);
struct node* searchByName(char name[20]);
int deleteById(int id);
void freelist(void);
int insertStudentByLoc(struct student std,int loc);
int updateStudentById(int id);
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
    if(y<9) y=y+1;
    gotoxy(x,y);
    break;

   case 71:
    y=1;
    gotoxy(x,y);
    break;

   case 79:
    y=9;
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
      struct student std;
      int retval;
      std =fillStudentData();
      retval=addStudent(std);
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

     case ySearchById:
     {
      struct node* ptr;
      int id,i;
      id=fillRequiredId();
      ptr=searchById(id);
      if(ptr)
      {
       printf("Student's Id= %d\n",ptr->std.id);
       printf("Student's Name= %s\n",ptr->std.name);
       for(i=0;i<3;i++)
       {
	printf("Student's Grade at Subject[%d] = %d\n",i+1,ptr->std.grades[i]);
       }
      }
      else
      {
       printf("Not Found");
      }
      break;
     }

     case ySearchByName:
     {
      struct node* ptr;
      char name[20];
      int i;
      strcpy(name,fillRequiredName());
      ptr=searchByName(name);
      if(ptr)
      {
       printf("Student's Id= %d\n",ptr->std.id);
       printf("Student's Name= %s\n",ptr->std.name);
       for(i=0;i<3;i++)
       {
	printf("Student's Grade at Subject[%d] = %d\n",i+1,ptr->std.grades[i]);
       }
      }
      else
      {
       printf("Not Found");
      }
      break;
     }

     case yDeleteById:
     {
      int id,retval;
      id=fillRequiredId();
      retval=deleteById(id);
      if(retval)
      {
       printf("Student deleted successfully");
      }
      else
      {
       printf("Not Found");
      }
      break;
     }

     case yFreelist:
      freelist();
      clrscr();
      printf("Students' List deleted successfully");
      break;

     case yInsertByLoc:
     {
      struct student std;
      int loc,retval;
      std =fillStudentData();
      printf("Enter Location to Insert Data In: ");
      scanf("%d",&loc);
      insertStudentByLoc(std,loc);
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

     case yUpdateById:
     {
      int id,retval;
      clrscr();
      printf("Enter Student's Id to update: ");
      scanf("%d",&id);
      retval=updateStudentById(id);
      if(retval)
      {
       printf("Student's Data updated successfully");
      }
      else
      {
       printf("Not Found");
      }
      break;
     }

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
 printf("%d- Add Student\n",yAdd);
 printf("%d- Search Student by ID\n",ySearchById);
 printf("%d- Search Student by Name\n",ySearchByName);
 printf("%d- Delete Student by ID\n",yDeleteById);
 printf("%d- Free Students' List\n",yFreelist);
 printf("%d- Insert Student by Location\n",yInsertByLoc);
 printf("%d- Update Student by ID\n",yUpdateById);
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


struct node* createStudent(struct student std)
{
 struct node* ptr;

 ptr=(struct node*)malloc(sizeof(struct node));

 if(ptr)
 {
  int i;
  strcpy(ptr->std.name,std.name);
  ptr->std.id=std.id;
  for(i=0;i<3;i++)
  {
   ptr->std.grades[i]=std.grades[i];
  }
  ptr->pNext=ptr->pPrev=NULL;
 }
 return ptr;

}


int addStudent(struct student std)
{
 struct node *ptr;
 int retval=0;
 ptr = createStudent(std);
 if(ptr)
 {
  if(!pHead)
  {
   pHead=pTail=ptr;
  }
  else
  {
   pTail->pNext=ptr;
   ptr->pPrev=pTail;
   pTail=ptr;
  }
  retval=1;
 }
 return retval;
}


int fillRequiredId(void)
{
  int id;
  clrscr();
  printf("Insert Student Id: ");
  scanf("%d",&id);
  return id;
}


struct node* searchById(int id)
{
 struct node* ptr;
 ptr=pHead;
 while(ptr && ptr->std.id != id)
 {
  ptr=ptr->pNext;
 }
 return ptr;
}


char* fillRequiredName(void)
{
  char name[20];
  clrscr();
  printf("Insert Student Name: ");
  scanf("%s",name);
  return name;
}


struct node* searchByName(char name[20])
{
 struct node* ptr;
 ptr=pHead;
 while(ptr && strcmp(ptr->std.name,name)!=0)
 {
  ptr=ptr->pNext;
 }
 return ptr;
}


int deleteById(int id)
{
 struct node* ptr;
 int retval=0;
 if(pHead)
 {
  ptr=pHead;
  if(pHead->std.id==id)
  {
   pHead=pHead->pNext;
   if(pHead!=NULL)
   {
    pHead->pPrev=NULL;
   }
   else
   {
    pTail=NULL;
   }
   retval=1;
  }
  else
  {
   while(ptr && ptr->std.id!=id)
   {
    ptr=ptr->pNext;
   }
   if(ptr)
   {
    if(ptr==pTail)
    {
     pTail=pTail->pPrev;
     pTail->pNext=NULL;
    }
    else
    {
     if(ptr==pTail)
     {
      pTail=pTail->pPrev;
     }
     else
     {
      ptr->pPrev->pNext=ptr->pNext;
      ptr->pNext->pPrev=ptr->pPrev;
     }
    }
   }
   retval=1;
  }
  free(ptr);
 }
 return retval;
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


int insertStudentByLoc(struct student std,int loc)
{
 struct node* ptr;
 int retval=0;
 ptr = createStudent(std);
 if(ptr)
 {
  if(!pHead)
  {
   pHead=pTail=ptr;
  }
  else
  {
   if(loc==0)
   {
    pHead->pPrev=ptr;
    ptr->pNext=pHead;
    pHead=ptr;
   }
   else
   {
    int i;
    struct node* temp;
    temp=pHead;
    for(i=0;(i<loc-1)&&temp;i++)
    {
     temp=temp->pNext;
    }
    if(temp==pTail || !temp)
    {
     pTail->pNext=ptr;
     ptr->pPrev=pTail;
     pTail=ptr;
    }
    else
    {
     ptr->pNext=temp->pNext;
     temp->pNext->pPrev=ptr;
     ptr->pPrev=temp;
     temp->pNext=ptr;
    }
   }
  }
  retval=1;
 }
 return retval;
}


int updateStudentById(int id)
{
 struct node* ptr;
 int retval=0;
 ptr=pHead;
 while(ptr && ptr->std.id != id)
 {
  ptr=ptr->pNext;
 }
 if(ptr && ptr->std.id == id)
 {
  int i;
  clrscr();
  printf("Old Values\n*******************\n");
  printf("Student's Id= %d\n",ptr->std.id);
  printf("Student's Name= %s\n",ptr->std.name);
  for(i=0;i<3;i++)
  {
   printf("Student's Grade at Subject[%d] = %d\n",i+1,ptr->std.grades[i]);
  }
  printf("\n\nNew Values\n*******************\n");
  printf("Student's Name= ");
  scanf("%s",ptr->std.name);
  for(i=0;i<3;i++)
  {
   printf("Insert Student's Grade at Subject[%d]= ",i+1);
   scanf("%d",&ptr->std.grades[i]);
  }
  retval=1;
 }
 return retval;
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
 while(ptr)
 {
  printf("Student's Id= %d\n",ptr->std.id);
  printf("Student's Name= %s\n",ptr->std.name);
  for(i=0;i<3;i++)
  {
   printf("Student's Grade at Subject[%d] = %d\n",i+1,ptr->std.grades[i]);
  }
  printf("**********************\n");
  ptr= ptr->pNext;
 }
}