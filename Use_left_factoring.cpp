#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
using namespace std;

struct list                        
{
	char value[100];
	struct list *next;
};

struct list* getNode(char str[])        
{
	struct list *node;
	node = (struct list *)malloc(sizeof(struct list));
	strcpy(node->value,str);
	node->next = NULL;
	return node;
}

int listLength(struct list *head)	
{
	int n = 0;
	struct list *temp = head->next;
	while(temp!=NULL)
	{
		n++;
		temp = temp->next;
	}
	return n;
}

void sort(struct list *head)			// sorting of list
{
	int n = listLength(head); 		// length of list helps in sorting
	//printf("%d\n",n);
	struct list *previous,*current;
	while(--n)
	{
		previous = head->next;
		current = previous->next;
		while(previous->next!=NULL)
		{
			char pre[100];
			strcpy(pre,previous->value);
			char cur[100];
			strcpy(cur,current->value);
			if(strcmp(pre,cur)>0)
			{
				strcpy(previous->value,cur);
				strcpy(current->value,pre);
			}
			previous = previous->next;
			current = current->next;
		}
	}
	
}

int common(struct list *current,struct list *temp)	// finds length of common substring in node
{
	char str1[100];
	char str2[100];
	strcpy(str1,current->value);
	strcpy(str2,temp->value);
	int length = 0,i;
	for(i=0;i<strlen(str1);i++)
	{
		if(str1[i]==str2[i])
			length++;
		else
			return length;	
	}
	return length;
	
}

int main()
{
	cout<<"Note::Here for replacing string after prefix i am using z1 and z2 new non terminal. \n ";
	FILE *fp = fopen("input.txt","r");
	if(fp==NULL)
	{
		printf("Input file not found\n");
		return 1;
	}
	
	struct list *head[10];
	int count = 0;
	int i;
	// Here grammar from file is stored in list
	char temp[100],last[5];
	struct list *traverse;
	fscanf(fp,"%s",temp);
	while(!feof(fp))
	{
		if(!strcmp(temp,"\0"))
			break;
		if(isalnum(temp[0]))
		{
			struct list *node = getNode(temp);
			if(strlen(temp)==1)
			{
				if(!strcmp(last,"|") || !strcmp(last,"->")) // means single non-terminal/terminal on right side
				{
					traverse->next = node;
					traverse = node;
				}
				else                  // else non-terminal on left side
				{
					head[count] = node;
					traverse = node;
					count++;
				}
			}
			else
			{
				traverse->next = node;
				traverse = node;
			}	
		}
		strcpy(last,temp);
		fscanf(fp,"%s",temp);
	}
	fclose(fp);
	
	int m = count-1;
	// Here changes are done in grammar (left factoring method)
	for(i=0;i<count;i++)
	{
		sort(head[i]);
		struct list *current,*temp,*newCurrent;
		current = head[i]->next;
		temp = current->next;
		int min = strlen(current->value);
		bool change = false;
		while(current!=NULL)// || current!=NULL)
		{
			int length;
			if(temp!=NULL)
			{
				length = common(current,temp);
				if(length)
					change = true;
				else 
					change = false;	
			}		
			else 
			{
				length = 0;
				change = false;
			}		
			if(min>=length && change)
			{
				//change = true;
				min = length;
			}	
			if(length && temp!=NULL)
			{
				temp = temp->next;
			}
			else
			{
				char str[100];
				if(min>0 && current->next!=temp)
				{
					m++;
					str[0] = 'Z';        // for the naming of new variable
					str[1] = m-count+1+48;
					str[2] = '\0';
					head[m] = getNode(str);
					newCurrent = head[m];
					struct list *traverse = current;
					char cstr[100];
					strcpy(cstr,current->value);
					while(traverse!=temp)
					{
						if(min == strlen(traverse->value))
						{
							newCurrent->next = getNode((char *)"NULL");
						}	
						else
						{
							newCurrent->next = getNode(traverse->value+min);
						}
						newCurrent = newCurrent->next;
						traverse = traverse->next;
					}
					strcpy(cstr+min,str);
					strcpy(current->value,cstr);
				}
				current->next = temp;
				current = temp;
				if(temp!=NULL)
				{
					temp = temp->next;
					min = strlen(current->value);
				}
				else
					break;	
			}
		}
		
		
	}
	
	
	// loop to print all the list (modified grammar)
	for(i=0;i<=m;i++)
	{
		traverse = head[i];
		printf("%s->",traverse->value);
		while(traverse->next!=NULL)
		{
			traverse = traverse->next;
			printf("%s|",traverse->value);
		}
		printf("\n");
	}
	return 0;
}



//Mahesh Nagarwal 
//id 2015kucp1043
//cd lab assignment 2 for implementing left factoring meythod to convert non deterministic grammer into deterministic
