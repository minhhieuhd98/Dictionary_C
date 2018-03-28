#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "inc/btr.h"
void menu()
{
    printf("\n1-Add");
    printf("\n2-Search");
    printf("\n3-Delete");
    printf("\n4-List");
    printf("\n5-Quit");
    printf("\nLua chon cua ban la: ");
}

void add(BTA *bt)
{
    char name[80];
    int size;
    long number;
    while(getchar()!='\n');
    printf("\nNhap vao ten: ");
    gets(name);
    printf("\nNhap so dien thoai: ");
    scanf("%ld",&number);
    btins(bt,name,(char*)&number,sizeof(long));
}

void list(BTA *bt)
{
    char name[80];
    long number;
    int size;
    btsel(bt,"",(char*)&number,sizeof(long),&size);
    while(btseln(bt, name, (char*)&number, sizeof(long), &size) == 0)
    {
        printf("%-20s%ld\n", name, number);
    }
}

void search(BTA *bt)
{
    char name[80];
    long number;
    int size;
    while(getchar()!='\n');
    printf("\nNhap vao ten nguoi can tim: ");
    gets(name);
    if(btsel(bt,name,(char*)&number,sizeof(long),&size)==0)
        {
        printf("\n%-20s%ld",name, number);
        }
    else{
        printf("\n Khong tim thay!!");
        }
}
void del(BTA *bt)
{
    char name[80];
    long number;
    int size;
    while(getchar()!='\n');
    printf("\nNhap vao ten nguoi can tim: ");
    gets(name);
    if(btsel(bt,name,(char*)&number,sizeof(long),&size)==0)
    {
    btdel(bt,name);
    }
    else{
    printf("\n Khong tim thay!!");
    }
}

int main()
{
BTA *bt;
btinit();
bt=btopn("phonebook.dat",0,0);
if(!bt)
{
bt=btcrt("phonebook.dat",0,0);
}
int i,n,p=0;
while(p!=5)
{
menu();
scanf("%d",&p);
switch(p)
    {
    case 1:
    add(bt);
    printf("\n");
    list(bt);
    break;
    case 2:
    search(bt);
    break;
    case 3:
    del(bt);break;
    case 4:
    list(bt);
    break;
    case 5:
    break;

    }
}
}
