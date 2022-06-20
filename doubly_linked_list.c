#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int size=0;
struct node{
    int int_v,pos;
    struct node *next;
    struct node *parent;
};
struct node *insert(struct node *,int,int);
void delete(struct node *,int);
struct node *find(struct node *,int);
int delete_helper(struct node*,int);
void position_reload_insert(struct node*);
void position_reload_delete(struct node*);
void display_reverse(struct node*);
struct node *gettail(struct node*);
//void swap(struct node*,struct node*);
void display(struct node*);
struct node *insert(struct node *root,int position,int value){
	if(position==0){
		struct node *duplicate_head=(struct node*)malloc(sizeof(struct node));
		struct node *copy_next=(*root).next;
		(*duplicate_head).int_v=(*root).int_v;
		(*duplicate_head).pos=2;
        (*duplicate_head).parent=root;
		(*root).int_v=value;
		(*root).next=duplicate_head;
		(*duplicate_head).next=copy_next;
		return root;
	}
    struct node *selected_trv=root;
    struct node *store_parent;
    //going to position-1, or the parent of the node to be inserted.
	while((*selected_trv).pos!=position-1){
		selected_trv=(*selected_trv).next;
	}
    store_parent=selected_trv;
	if((*selected_trv).next==NULL){
		(*selected_trv).next=(struct node*)malloc(sizeof(struct node));
		selected_trv=(*selected_trv).next;
		(*selected_trv).int_v=value;
		size++;
		(*selected_trv).pos=size;
        (*selected_trv).parent=store_parent;
		(*selected_trv).next=NULL;
		return selected_trv;
	}
	struct node *temp=(*selected_trv).next; //storing the next of npos-1
    struct node *selected_trv_store=selected_trv; //for parent assignation of new node
	(*selected_trv).next=(struct node*)malloc(sizeof(struct node)); //new node, clearing next
	selected_trv=(*selected_trv).next; //now selected_trv is pointing to new node
	(*selected_trv).int_v=value; //assigning int
	(*selected_trv).next=temp; //repairing link to next
    (*selected_trv).parent=selected_trv_store; //parent assignation
    (*temp).parent=selected_trv; //parent assignation for node after new node
	size++; //increment size for position
	(*selected_trv).pos=size; //assigning position
	position_reload_insert(selected_trv); //reloading position(incrementing all the positions after new node)
	return selected_trv; //returning new node
}
void delete(struct node *head, int pos){
    //algorithm for deleting head of a linked list.
	if(pos==0){
		struct node *copy_next_next=(*(*head).next).next;
		(*head).int_v=(*(*head).next).int_v;
		free((*head).next);
		(*head).next=copy_next_next;
        (*copy_next_next).parent=head;
		return;
	}
	struct node *n1=head;
	while((*n1).pos!=pos-1){
		n1=(*n1).next;
	}
	struct node *save_nd=(*n1).next;
	(*n1).next=(*save_nd).next;
	free(save_nd);
    (*(*n1).next).parent=n1;
    size--;
}
struct node *find(struct node *head, int value){
	struct node *selected=head;
	while(selected!=NULL){
		if((*selected).int_v==value){
			return selected;
		}
		selected=(*selected).next;
	}
	return NULL;
}
void position_reload_insert(struct node *new){
	struct node *trv=(*new).next;
	while(trv!=NULL){
		(*trv).pos++;
		trv=(*trv).next;
	}
}
void position_reload_delete(struct node *deleted){
	struct node *trv=(*deleted).next;
	while(trv!=NULL){
		(*trv).pos--;
		trv=(*trv).next;
	}
}
void display_reverse(struct node *from){
    struct node *selected=from;
    while(selected!=NULL){
        printf(" %d",(*selected).int_v);
        selected=(*selected).parent;
    }
    printf("\n");
}
/*void swap(struct node *node1,struct node *node2,struct node *node1_prev,struct node *node2_forw){
	(*node2).next=node1;
    (*node1_prev).next=node2;
    (*node1).next=node2_forw;
}*/
/*void swap(struct node *node1,struct node *node2){
	int temp_data=(*node1).int_v;
	(*node1).int_v=(*node2).int_v;
	(*node2).int_v=temp_data;
}*/
void display(struct node *head){
	struct node *selected=head;
	while(selected!=NULL){
		printf("%d ",(*selected).int_v);
		selected=(*selected).next;
	}
}
struct node *gettail(struct node *head){
    struct node *selected=head;
    while((*selected).next!=NULL){
        selected=(*selected).next;
    }
    return selected;
}
int main(void){
    struct node *head;
    head=(struct node*)malloc(sizeof(struct node));
	(*head).pos=size;
	(*head).next=NULL;
    int user_in,user_choice_in,insert_pos=0;
    printf("\nEnter head value:");
    scanf("%d",&user_in);
    (*head).int_v=user_in;
    printf("\nEnter 1 to insert data\nEnter 2 to see if a value exists in the linked list.\nEnter 3 to display the linked list\nEnter 4 to delete with position.\nEnter 5 to print from tail to parent.\nEnter 6 to exit.\n");
	while(user_choice_in!=6){
		printf("Choice:");
		scanf("%d",&user_choice_in);
		switch(user_choice_in){
			case 1:
			 printf("\nEnter value:");
			 scanf("%d",&user_in);
			 printf("\nenter position:");
			 scanf("%d",&insert_pos);
			 insert(head,insert_pos-1,user_in);
			 break;
			case 2:
			 printf("\nValue:");
			 scanf("%d",&user_in);
			 printf("\n%s\n",find(head,user_in)?"Yes.":"No.");
			 break;
			case 3:
			 display(head);
			 printf("\n");
			 break;
			case 4:
			 printf("\nEnter position:");
			 scanf("%d",&user_in);
			 delete(head,user_in-1);
             break;
            case 5:
             display_reverse(gettail(head));
		}
	}
	return 0;
}