#include <STDIO.H>
#include <CONIO.H>
#include <STDLIB.H>
#include <STRING.H>
#define yAdd 1
#define ySortById 2
#define ySortByName 3
#define yBinarySearchById 4
#define yBinarySearchByIdRecursively 5
#define yListStudents 6
#define yExit 7

struct student
{
 int id;
 char name[20];
 int grades[3];
};

struct student ar[10];
int size=10,start=0,end=0;


void printMenu(void);
struct student fillStudentData(void);
int addStudent(struct student std);
void listStudents(void);
void bubbleSort(void);
void mergeSort(int lb,int ub);
void merge(int lb,int mid,int ub);
int binarySearchById(int LB,int UB,int id);
int binarySearchByIdRecursively(int LB,int UB,int id);


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
    if(y<7) y=y+1;
    gotoxy(x,y);
    break;

   case 71:
    y=1;
    gotoxy(x,y);
    break;

   case 79:
    y=7;
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

     case yListStudents:
     {
      clrscr();
      listStudents();
      break;
     }

     case ySortById:
     {
      clrscr();
      bubbleSort();
      listStudents();
      break;
     }

     case ySortByName:
     {
      clrscr();
      mergeSort(start,end-1);
      listStudents();
      break;
     }

     case yBinarySearchById:
     {
      int loc,id,j;
      clrscr();
      printf("Enter Student's Id to search: ");
      scanf("%d",&id);
      loc=binarySearchById(start,end,id);
      if(loc>=0)
      {
       printf("Student's ID= %d\n",ar[loc].id);
       printf("Student's Name= %s\n",ar[loc].name);
       for(j=0;j<3;j++)
       {
	printf("Student's Subject[%d] Grade= %d\n",j+1,ar[loc].grades[j]);
       }
      }
      else
      {
       clrscr();
       printf("Not Available");
      }
      break;
     }

     case yBinarySearchByIdRecursively:
     {
      int loc,id,j;
      clrscr();
      printf("Enter Student's Id to search: ");
      scanf("%d",&id);
      loc=binarySearchById(start,end,id);
      if(loc>=0)
      {
       printf("Student's ID= %d\n",ar[loc].id);
       printf("Student's Name= %s\n",ar[loc].name);
       for(j=0;j<3;j++)
       {
	printf("Student's Subject[%d] Grade= %d\n",j+1,ar[loc].grades[j]);
       }
      }
      else
      {
       clrscr();
       printf("Not Available");
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
 printf("%d- Add a Student\n",yAdd);
 printf("%d- Sort Students By ID\n",ySortById);
 printf("%d- Sort Students By Name\n",ySortByName);
 printf("%d- Search Students By Id\n",yBinarySearchById);
 printf("%d- Search Students By Id Recursively\n",yBinarySearchByIdRecursively);
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


int addStudent(struct student std)
{
 int retval=0;
 if(end<size)
 {
  ar[end]=std;
  end++;
  retval=1;
 }
 return retval;
}


void listStudents(void)
{
 int i,j;
 if(end>0)
 {
  for(i=start;i<end;i++)
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
 else
 {
  printf("There's no students to list");
 }
}


void bubbleSort(void)
{
 int i,j;
 int sorted=1;

 while(sorted)
 {
  sorted=0;
  for(i=0;i<end-1;i++)
  {
   if(ar[i].id>ar[i+1].id)
   {
    struct student temp;
    temp=ar[i];
    ar[i]=ar[i+1];
    ar[i+1]=temp;
    sorted=1;
   }
  }
  j++;
 }
}

void mergeSort(int lb,int ub)
{
 int mid;
 if(lb < ub)
 {
  mid=(lb+ub)/2;
  mergeSort(lb,mid);
  mergeSort(mid+1,ub);
  merge(lb,mid,ub);
 }
}


void merge(int low,int mid,int high)
{
 struct student temp[10];
 int list1,list2,i,compare;
 list1=low;
 list2=mid+1;
 i=low;

 while(list1<=mid&&list2<=high)
 {
  compare=strcmp(ar[list1].name,ar[list2].name);
  if(compare<0)
  {
   temp[i]=ar[list1];
   list1++;
   i++;
  }
  else
  {
   temp[i]=ar[list2];
   list2++;
   i++;
  }
 }

 while(list1<=mid)
 {
  temp[i]=ar[list1];
  list1++;
  i++;
 }

 while(list2<=high)
 {
  temp[i]=ar[list2];
  list2++;
  i++;
 }

 for(i=0;i<=high;i++)
 {
  ar[i]=temp[i];
 }

}


int binarySearchById(int LB,int UB,int id)
{
 int mid,loc;
 loc=-1;

 bubbleSort();

 while(LB<=UB&&loc==-1)
 {
  mid=(LB+UB)/2;

  if(ar[mid].id==id)
  {
   loc=mid;
  }
  else
  {
   if(ar[mid].id<id)
   {
    LB=mid+1;
   }
   else
   {
    UB=mid-1;
   }
  }
 }
 return loc;
}


int binarySearchByIdRecursively(int LB,int UB,int id)
{
 int loc,mid;
 loc=-1;
 mid=(LB+UB)/2;

 bubbleSort();

 if(ar[mid].id==id)
 {
  loc=mid;
 }
 else
 {
  if(LB<=UB)
  {
   if(ar[mid].id<id)
   {
    LB=mid+1;
    loc= binarySearchByIdRecursively(LB,UB,id);
   }
   else
   {
    UB=mid-1;
    loc= binarySearchByIdRecursively(LB,UB,id);
   }
  }
 }
 return loc;
}


