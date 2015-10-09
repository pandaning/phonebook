#include <stdlib.h>
#include <string.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    return NULL;
}

void init()
{
	for(int i=0;i<20000;i++)
	{	
		head[i]=malloc(sizeof(HL));
		head[i]->next=NULL;
		ptr[i]=head[i];
	}

}
int HashFunc(char *str,int method)//return pos
{
	int pos=0;
	int strLength =  strlen(str);
	switch(method)
	{
		case 1:
			for(int i=0; i<strLength; i++)
			{
				pos+=str[i];
			}
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		
	}
	return pos;
}
int IsFound(char str[])
{
	int yes=1;
	int no=0;
	int id=HashFunc(str,1);
	for(HL* tmp=head[id] ; tmp!=NULL ; tmp=tmp->next)
	{
		//if(tmp->name==str)
		if(strcmp(tmp->name , str)==0)
		{
			return yes;
		}
	}
	return no;
}
void pushHashTable(char *str,int id)
{
	ptr[id]->next=malloc(sizeof(HL));
	ptr[id]=ptr[id]->next;
	strcpy(ptr[id]->name,str);     //ptr[id]->name=str;
	ptr[id]->next=NULL;
}

void FREE()
{
puts("Free La");
	for(int i=0;i<20000;i++)
	{
		HL *tmp=head[i];
		HL *f=tmp;
		if(tmp->next!=NULL)tmp=tmp->next;
		for(;tmp->next!=NULL;tmp=tmp->next)
		{
			free(f);
			f=tmp;
		}
	}

}