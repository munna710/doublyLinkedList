#include<stdio.h>
#include<conio.h>
#include<alloc.h>
typedef struct listnode* listpointer;
struct listnode
{
	int data;
	listpointer next,prev;
};
listpointer fnode=NULL,p,lnode;
int listsize=0;
void create();
void list();
void insert(int,int);
void delv(int);
void delp(int);
void main()
{
	int choice;
	int n,pos;
	do
	{
		clrscr();
		printf("\n\tlinked list operation\n");
		printf("\n\t\t1.create");
		printf("\n\t\t2.list");
		printf("\n\t\t3.insert");
		printf("\n\t\t4.delete by value");
		printf("\n\t\t5.delete by position");
		printf("\n\t\t6.exit");
		printf("\nenter your choice(1-6): ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:create();
				break;
			case 2:list();
				break;
			case 3:printf("\n enter the data: ");
			       scanf("%d",&n);
			       printf("\n enter the position(1-%d): ",listsize+1);
			       scanf("%d",&pos);
			       insert(n,pos);
				break;
			case 4:printf("\nenter the data: ");
			       scanf("%d",&n);
			       delv(n);
				break;
			case 5:printf("\n enter the position(1-%d): ",listsize);
			       scanf("%d",&pos);
			       delp(pos);
				break;
			default:continue;
		 }
		 getch();
	}
	while(choice!=6);
}
void create()
{
	int i;
	if(fnode!=NULL)
	{
		printf("\n list already created");
		return;
	}
	printf("\n enter number of elements ");
	scanf("%d",&listsize);
	if(listsize<1)return;

	printf("\n enter %d elements into the list:\n",listsize);
	fnode=(listpointer)malloc(sizeof(*fnode));
	scanf("%d",&fnode->data);
	fnode->next=fnode->prev=NULL;
	p=fnode;
	for(i=0;i<listsize-1;i++)
	{
		p->next=(listpointer)malloc(sizeof(*p));
		p->next->prev=p;
		p=p->next;
		scanf("%d",&p->data);
	}
	lnode=p;
	lnode->next=NULL;
	printf("\nlist created with %d elements",listsize);
}
void list()
{
	if(fnode==NULL)
	{
		printf("\n list is empty");
		return;
	}
	printf("\nelements in the list:\n");
	printf("\nbackward traversal: ");
	for(p=lnode;p!=NULL;p=p->prev)
	printf("\n\t%d",p->data);
	printf("\nforward traversal: ");
	for(p=fnode;p!=NULL;p=p->next)
	printf("\n\t%d",p->data);
}
void insert(int x,int loc)
{
	int i;
	listpointer node;
	if(loc<1||loc>listsize+1)
	{
		printf("\ninvalid location");
		return;
	}
	node=(listpointer)malloc(sizeof(*node));
	node->data=x;
	node->next=node->prev=NULL;
	if(fnode==NULL)
	fnode=lnode=node;
	else if(loc==1)
	{
		node->next=fnode;
		fnode->prev=node;
		fnode=node;
	}
	else if(loc==listsize+1)
	{
		node->prev=lnode;
		lnode->next=node;
		lnode=node;
	}
	else if(loc<=listsize/2)
	for(i=1,p=fnode;i!=loc-1;i++,p=p->next);
	else
	for(i=listsize-1,p=lnode->prev;i!=loc-1;i--,p=p->prev);
	node->next=p->next;
	node->prev=p;
	p->next=node;

	listsize++;
	printf("\n one element inserted");
}
void delv(int x)
{
	listpointer d;
	if(fnode==NULL)
	{
		printf("\n the list is empty");
		return;
	}
	if(fnode->data==x)
	{
		p=fnode;
		fnode=fnode->next;
		fnode->prev=NULL;
	}
	else if(lnode->data==x)
	{
		p=lnode;
		lnode=lnode->prev;
		lnode->next=NULL;
	}
	else
	{
		for(p=fnode->next;p!=NULL&&p->data!=x;p=p->next);
		if(p==NULL)
		{
			printf("\nelement not found");
			return;
		}
		p->next->prev=p->prev;
		p->prev->next=p->next;
	}
	free(p);
	listsize--;
	printf("\none element deleted..");
}
void delp(int loc)
{
	listpointer d;
	int i;
	if(fnode==NULL)
	{
		printf("\nlist is empty..");
		return;
	}
	if(loc<1||loc>listsize)
	{
		printf("\ninvalid position");
		return;
	}
	if(loc==1)
	{
		p=fnode;
		fnode=fnode->next;
		fnode->prev=NULL;
	}
	else if(loc==listsize)
	{
		p=lnode;
		lnode=lnode->prev;
		lnode->next=NULL;
	}
	else
	{
		for(i=1,p=fnode->next;i!=loc-1;i++,p=p->next);
		p->next->prev=p->prev;
		p->prev->next=p->next;
	}
	free(p);
	listsize--;
	printf("\none element deleted...");
}
