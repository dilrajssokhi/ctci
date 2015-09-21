/*
3.7
An animal shelter holds only dogs and cats, and operates on a strictly "first in, first
out" basis. People must adopt either the "oldest" (based on arrival time) of all animals
at the shelter, or they can select whether they would prefer a dog or a cat (and will
receive the oldest animal of that type). They cannot select which specific animal they
would like. Create the data structures to maintain this system and implement opera-
tions such as enqueue, dequeueAny, dequeueDog and dequeueCat. You may
use the built-in L inkedL ist data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 10

/* Linked List Implementation*/
struct node {
	int animalOrder;
        char animal[MAX_LEN]; /* payload */
        struct node *next;
};

struct node *headDog = NULL;
struct node *endDog = NULL;
struct node *headCat = NULL;
struct node *endCat = NULL;
int order = 0;

struct node * newNode(char *str) {
        struct node *newNode =(struct node *) malloc(sizeof(struct node));
        if (newNode != NULL) {
                strcpy(newNode->animal,str);
		newNode->animalOrder = order++;
                newNode->next = NULL;
        }

        return newNode;
}

struct node * appendNode(struct node *end, char *str) {
        struct node *newEnd = newNode(str);
        if (newEnd != NULL && end != NULL) {
                end->next = newEnd;
        }

        return newEnd;
}

struct node * addNodetoFront(struct node *head, char *str) {
        struct node *newHead = newNode(str);
        if (newHead != NULL) {
                newHead->next = head;
        }

        return newHead;
}

void iterateNodes(struct node *start) {
        printf("\nIterating over Linked List:\n");
        for (struct node *p = start; p!=NULL;p=p->next) {
                printf("Animal: %s, Order: %d, Address: %p, Next Address: %p\n",p->animal,p->animalOrder,p,p->next);
        }
        printf("\n");
}

bool enqueueDog(char *str) {
	if (endDog == NULL && headDog == NULL) {
		headDog = newNode(str);
		endDog = headDog;
	}
	else {
		endDog = appendNode(endDog,str);
	}

	if (headDog != NULL) 
		return true;
	else
		return false;
}

bool enqueueCat(char *str) {
	if (endCat == NULL && headCat == NULL) {
		headCat = newNode(str);
		endCat = headCat;
	}
	else {
		endCat = appendNode(endCat,str);
	}

	if (headCat != NULL) 
		return true;
	else
		return false;
}

bool enqueue(char *str) {
	bool enqStatus = false;

	if (strstr(str,"Dog")) 
		enqStatus = enqueueDog(str);
	else if(strstr(str,"Cat"))
		enqStatus = enqueueCat(str);

	return enqStatus;
}

char * dequeueDog(char *str) {
	struct node *temp = NULL;
	//static char str[MAX_LEN];           /*defining as a static increases local variable longevity*/

	if (endDog == NULL && headDog == NULL) {
		printf("Dog Queue empty\n");
		return false;
	}
	else {
		strcpy(str,headDog->animal);
		if (headDog != endDog) {
			temp = headDog;
			headDog = headDog->next;
			free(temp);
		}
		else {
			temp = headDog;
			free(temp);

			headDog = NULL;
			endDog = NULL;
		}
		return str;
	}
}

char * dequeueCat(char *str) {
	struct node *temp = NULL;

	if (endCat == NULL && headCat == NULL) {
		printf("Cat Queue empty\n");
		return false;
	}
	else {
		strcpy(str,headCat->animal);
		if (headCat != endCat) {
			temp = headCat;
			headCat = headCat->next;
			free(temp);
		}
		else {
			temp = headCat;
			free(temp);

			headCat = NULL;
			endCat = NULL;
		}
		return str;
	}
}

char * dequeueAny(char *str) {
	if (headDog->animalOrder < headCat->animalOrder) 
		str = dequeueDog(str);
	else 
		str = dequeueCat(str);

	return str;
}

int main(int argc, char *argv[]) {
	/*
	printf("Argument count: %d\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("Argument vector values:%s at %p memory\n", argv[i], argv[i]);
		for (char *j=argv[i]; *j!='\0'; j++) {
			printf("Another way to print argument vector values: "
                               "%c at %p memory\n", *j, j);
		}
	}
	*/

        //int num[MAX_LEN] = {1,2,3,4,5,6,7,8,9,10};
	char *str;

        enqueue("Dog1");
        enqueue("Cat1");
        enqueue("Cat2");
        enqueue("Dog2");
        enqueue("Cat3");
        enqueue("Dog4");
        enqueue("Cat4");
        iterateNodes(headDog);
        iterateNodes(headCat);

        //printf("Dequeue any animal: %s\n",dequeueAny(str));
        printf("Dequeue any: %s\n",dequeueAny(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue cat: %s\n",dequeueCat(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue dog: %s\n",dequeueDog(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue dog: %s\n",dequeueDog(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        enqueue("Dog5");
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue any: %s\n",dequeueAny(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        enqueue("Cat5");
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue cat: %s\n",dequeueCat(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue any: %s\n",dequeueAny(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue any: %s\n",dequeueAny(str));
        iterateNodes(headDog);
        iterateNodes(headCat);
        printf("Dequeue dog: %s\n",dequeueDog(str));
        iterateNodes(headDog);
        iterateNodes(headCat);

        printf("\nFreeing Linked List:\n");
        struct node *temp;
        while (headDog != NULL) {
                printf("Animal: %s, Order: %d, Address: %p, Next Address: %p\n",headDog->animal,headDog->animalOrder,headDog,headDog->next);
                temp = headDog;
                headDog = headDog->next;
                free(temp);
        }

        while (headCat != NULL) {
                printf("Animal: %s, Order: %d, Address: %p, Next Address: %p\n",headCat->animal,headCat->animalOrder,headCat,headCat->next);
                temp = headCat;
                headCat = headCat->next;
                free(temp);
        }
	return 0;
}