#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define STACK_BLOCK_SIZE 10

typedef struct {
	int * array;
	int currentsize;
	int maxsize;
} stack;

stack * init_return();
int init(stack * s);
void push(stack * stack, int item);
int pop(stack * stack);
void move_disk(stack *rod1_stack, stack *rod2_stack, char s, char d);

int main(){
	int tsize, i;
	char s = '1', a = '2', d = '3';/*rods*/

	printf ("Enter Tower size: ");
  scanf ("%d", &tsize);

	stack *first, *third, *second;/*stacks*/

	/*create stacks STACK_BLOCK_SIZE size and controls if it is initilasiton*/
	first=init_return();
  second=init_return();
  third=init_return();

	/*if disk size is even number changes rods*/
	if (tsize % 2 == 0){
		d='2';
		a='3';
	}

	/*inserting disks in to first rod*/
	for (i = tsize; i >= 1; i--)
		push(first, i);


	/*#################################################################################################################
	# pow(2,tsize)-1=operation number. We must change disks between rods this time 																		#
	# We do operations according to operation number because my algorithm is according to rods not according to disks	#
	#################################################################################################################*/
	for (i = 1; i <= (pow(2, tsize) - 1); i++){
		int option=i % 3;
		switch (option) {
			case 0:move_disk(second, third, a, d); break;

			case 1:move_disk(first, third, s, d); break;

			case 2:move_disk(first, second, s, a); break;
		}
	}
	return 0;
}

stack * init_return(){
	int i,cont;
  stack * rod = malloc (sizeof(int));/*reversing place for rod*/
  rod->array = malloc (STACK_BLOCK_SIZE* sizeof(int));/*reversing place for rods array*/

  for (i=0; i<STACK_BLOCK_SIZE; i++) rod->array[i] = 0;/*making array items 0*/
  rod->currentsize = -1;/*we do currentsize -1 because we start before the disk when disk is inserted it comes to 'array[0]' */
  rod->maxsize = STACK_BLOCK_SIZE;/*it is for start initilasize*/

	cont=init(rod);
	if (cont==-31) {/*if rod is not successfully initilasited*/
		printf("Error! Stack can not be placed successfully. Please restart application.\n");
	}
	else{/*if rod is successfully initilasited*/
  return rod;
	}
}

int init (stack *s) {
  if (s==NULL) {/*if rod is not initilasiton returns -31 as a error code*/
  	return -31;
  }
	return 1;
}

void push(stack *stack, int item){
	if (stack->currentsize == stack->maxsize - 1) return;/*if the rod is full returns*/
	stack -> array[++stack -> currentsize] = item;/*if rod is not full insert the disk in to rod*/
}

int pop(stack* stack){
	int if_empty=stack->currentsize;
	if (if_empty== -1)	return -31;/*if rod is empty returns -31 as a error code*/
	return stack -> array[stack -> currentsize--];/*if rod is not empty pops the disk*/
}

void move_disk(stack *rod1_stack, stack *rod2_stack, char s, char d){
	int rod1 = pop(rod1_stack);
	int rod2 = pop(rod2_stack);

	/*below if blocks are controls which rod has the bigger disk*/

	// When pole 1 is empty
	if (rod1 == -31)
	{
		push(rod1_stack, rod2);
		printf("Move the disk %d from \'%c\' to \'%c\'\n", rod2, d, s);
	}

	// When pole2 pole is empty
	else if (rod2 == -31)
	{
		push(rod2_stack, rod1);
		printf("Move the disk %d from \'%c\' to \'%c\'\n", rod1, s, d);
	}

	// When currentsize disk of pole1 > currentsize disk of pole2
	else if (rod1 > rod2)
	{
		push(rod1_stack, rod1);
		push(rod1_stack, rod2);
		printf("Move the disk %d from \'%c\' to \'%c\'\n", rod2, d, s);
	}

	// When currentsize disk of pole1 < currentsize disk of pole2
	else
	{
		push(rod2_stack, rod2);
		push(rod2_stack, rod1);
		printf("Move the disk %d from \'%c\' to \'%c\'\n", rod1, s, d);
	}
}
