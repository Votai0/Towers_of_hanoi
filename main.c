// C Program for  Tower of Hanoi
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define STACK_BLOCK_SIZE 10
// A structure to represent a stack
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
	char s = '1', d = '3', a = '2';

	printf ("Enter Tower size: ");
  scanf ("%d", &tsize);

	stack *first, *third, *second;

	// Create three stacks of size 'tsize' to hold the disks
	//first=init_return();
  //second=init_return();
  //third=init_return();
  init(first);
  init(second);
  init(third);
#include <limits.h>
	//If number of disks is even, then interchange thirdination pole and secondiliary pole
	if (tsize % 2 == 0){
		d='2';
		a='3';
	}

	//Larger disks will be pushed first
	for (i = tsize; i >= 1; i--)
		push(first, i);

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

// function to create a stack of given maxsize.
stack * init_return(){
	int i;
  stack * rod = malloc (STACK_BLOCK_SIZE* sizeof(int));
  rod->array = malloc (STACK_BLOCK_SIZE* sizeof(int));

  for (i=0; i<STACK_BLOCK_SIZE; i++) rod->array[i] = 0;
  rod->currentsize = -1;
  rod->maxsize = STACK_BLOCK_SIZE;

  return rod;
}

int init (stack * s) {
  s = init_return ();
  return 1;
}

// Function to add an item to stack. It increases currentsize by 1
void push(stack *stack, int item){
	if ((stack->currentsize == stack->maxsize - 1)) return;
	stack -> array[++stack -> currentsize] = item;
}

// Function to remove an item from stack. It decreases currentsize by 1
int pop(stack* stack){
	if ((stack->currentsize == -1))	return -31;
	return stack -> array[stack -> currentsize--];
}

// Function to implement legal movement between two poles
void move_disk(stack *rod1_stack, stack *rod2_stack, char s, char d){
	int rod1 = pop(rod1_stack);
	int rod2 = pop(rod2_stack);

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
