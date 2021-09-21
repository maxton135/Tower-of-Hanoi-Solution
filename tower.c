#include "stack.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "srn:"
int rcount = 0;
int scount = 0;

/* Recursion function
 * int x      = number of disks
 * char from  = peg to take from
 * char to    = destination peg
 * char extra = non destination peg */
void move(int x, char from, char to, char extra) {
  if (x == 1) {
    printf("Move disk 1 from peg %c to peg %c\n", from, to);
    rcount++;
  } else {
    move(x - 1, from, extra, to);
    printf("Move disk %d from peg %c to peg %c\n", x, from, to);
    rcount++;
    move(x - 1, extra, to, from);
  }
  return;
}

/* Pop and Push disks from stack function
 * Between two pegs peg1 and peg2,
 * Move smaller top disk to other peg or empty peg */
void pegCompare(Stack *peg1, Stack *peg2) {
  int peg1top = stack_pop(peg1);
  int peg2top = stack_pop(peg2);

  if (peg1top == -1) {
    stack_push(peg1, peg2top);
    printf("Move disk %d from peg %c to peg %c\n", peg2top, peg2->name,
        peg1->name);
  } else if (peg2top == -1) {
    stack_push(peg2, peg1top);
    printf("Move disk %d from peg %c to peg %c\n", peg1top, peg1->name,
        peg2->name);
  } else if (peg1top > peg2top) {
    stack_push(peg1, peg1top);
    stack_push(peg1, peg2top);
    printf("Move disk %d from peg %c to peg %c\n", peg2top, peg2->name,
        peg1->name);
  } else {
    stack_push(peg2, peg2top);
    stack_push(peg2, peg1top);
    printf("Move disk %d from peg %c to peg %c\n", peg1top, peg1->name,
        peg2->name);
  }
  return;
}

int main(int argc, char **argv) {
  /* Initialize varibales for getopt() and switch cases */
  int c = 0;
  int x = 5;
  bool solveRecursion = false;
  bool solveStack = false;

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'n': // Set number of disks
      sscanf(optarg, "%d", &x);
      break;
    case 'r': // Recursion option
      solveRecursion = true;
      break;
    case 's': // Stack option
      solveStack = true;
      break;
    }
  }

  // Solve using recursion
  if (solveRecursion) {
    printf("\n================================");
    printf("\n--------   RECURSION   ---------");
    printf("\n================================\n");
    move(x, 'A', 'B', 'C');
    printf("\nNumber of moves: %d\n", rcount);
  }

  // Solve using stacks
  if (solveStack) {
    printf("\n================================");
    printf("\n----------   STACKS   ----------");
    printf("\n================================\n");
    // Initialize three empty stacks
    struct Stack *pa, *pb, *pc;
    pa = stack_create(x, 'A');
    pb = stack_create(x, 'B');
    pc = stack_create(x, 'C');

    // Push all disks onto peg A stack
    for (int i = x; i >= 1; i--) {
      stack_push(pa, i);
    }

    // If number of disks is even, switch peg b and c
    if (x % 2 == 0) {
      pb->name = 'C';
      pc->name = 'B';
    }

    // Start iteration
    // Number of moves = 2^x + 1
    int numMoves = 1;
    for (int i = 0; i < x; i++) {
      numMoves = numMoves * 2;
    }
    numMoves = numMoves - 1;

    // Repeat three move solution pattern for numMoves
    for (int i = 1; i <= numMoves; i++) {
      if (i % 3 == 1) {
        pegCompare(pa, pb);
      } else if (i % 3 == 2) {
        pegCompare(pa, pc);
      } else if (i % 3 == 0) {
        pegCompare(pb, pc);
      }
    }
    printf("\nNumber of moves: %d\n", numMoves);
    stack_delete(pa);
    stack_delete(pb);
    stack_delete(pc);
  }
  return 0;
}
