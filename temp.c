#include <stdio.h>
#include "queue.h"
int main()
{
	Queue queue;
	queue_initialize(&queue);
	int choice, id, time, t;
	int loop = 1;
	while (loop)
	{
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			scanf("%d%d", &id, &time);
			queue_enqueue(&queue, id, time);
			break;

		case 1:
			queue_dequeue(&queue);
			break;

		case 2:
			queue_peek(&queue);
			break;

		case 3:
			scanf("%d", &t);
			queue_find_person(&queue, t);
			break;

		default:
			queue_destroy(&queue);
			loop = 0;
		}
	}
	return 0;
}



static node *create_node(int id, int time, node *link)
{
	node* temp =  (node*)malloc(sizeof(node));
	temp -> id = id; 
	temp -> link = link;
	temp -> time = time;
	return temp;
}
void list_initialize(List *ptr_list)
{
    ptr_list->head=NULL;
    ptr_list->number_of_nodes=0;
	ptr_list->tail=NULL;	
}
const int node_get_id(node *node_ptr)
{
	return node_ptr->id;
}

const int node_get_time(node *node_ptr)
{
	return node_ptr->time;	
}

void list_insert_rear(List *ptr_list, int id, int time)
{
    node * t=create_node(id,time,NULL);
	if(ptr_list->number_of_nodes==0)
    {
	    ptr_list->tail=t;
		ptr_list->head=t;
    }
    else
    {
        ptr_list->tail->link=t;
        ptr_list->tail=t;
    }
	ptr_list->number_of_nodes++;
}

void list_delete_front(List *ptr_list)
{
	if(ptr_list->number_of_nodes>0)
    {
        ptr_list->head=ptr_list->head->link;
        ptr_list->number_of_nodes--;
    }
	else if(ptr_list->number_of_nodes==1)
	{
		ptr_list->tail=NULL;
	}
}

void list_destroy(List *ptr_list)
{
    node *t, *u=NULL;
	t=ptr_list->head;
	while (t != NULL){
		u=t;
		t=t->link;
		free(u);
	}
	free(ptr_list);
}

void queue_initialize(Queue *queue_list)
{
    List* ptr_list =(List*) malloc(sizeof(List));
    queue_list->ptr_list=ptr_list;
    list_initialize(queue_list->ptr_list);

}

void queue_enqueue(Queue *ptr, int id, int time)
{
    
	list_insert_rear(ptr->ptr_list,id,time);

}

void queue_dequeue(Queue *ptr)
{
	list_delete_front(ptr->ptr_list);
}

int queue_is_empty(Queue *ptr)
{
	if(ptr->ptr_list->number_of_nodes==0)
		return 1;
	else
		return 0;
//TODO		
}

void queue_peek(Queue *ptr)
{
	if(queue_is_empty(ptr))
		printf("Empty Queue\n");
	else
		printf("%d %d\n",ptr->ptr_list->head->id,ptr->ptr_list->head->time);
}

void queue_destroy(Queue *ptr)
{
    list_destroy(ptr->ptr_list);
    free(ptr);
}

const int queue_find_person(Queue *ptr_queue, int t)
{
	int time=0;
	while (time<t &&!queue_is_empty(ptr_queue))
	{
	    time+=ptr_queue->ptr_list->head->time;
		if(time<t)
			queue_dequeue(ptr_queue);
	}
	if (queue_is_empty(ptr_queue))
	{
		printf("Empty Queue\n");
	}
	else
	{
		printf("%d\n",ptr_queue->ptr_list->head->id);
	}
	
	

}

