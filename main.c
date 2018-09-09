#include <stdio.h>

/*
 * A simple virtual machine with instructions:
 *  PSH x     : push into the stack an int
 *  POP       : pops from the stack and print for debugging
 *  ADD       : pops tow ints from the stack, adds them and pushes
 *              the result onto the stack
 *  SET REG x : sets register REG to x
 *  HLT       : ends execution
 */
int fetch();
void eval(int);

typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT
} InstructionSet;

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  HLT
};

int ip = 0, sp = -1;
int running = 1;
int stack[100];

int main()
{
  while (running) {
    eval(fetch());
    ip++;
  }
  return 0;
}


int fetch()
{
  return program[ip];
}


void eval(int instr)
{
  int x;
  int y;

  switch(instr) {
    case HLT:
      running = 0;
      break;

    case PSH:
      sp++;
      stack[sp] = program[++ip];
      break;

    case POP:
      x = stack[sp--];
      printf("debug: popped %d\n", x);
      break;
    case ADD:
      x = stack[sp--];
      y = stack[sp--];
      stack[sp] = x + y;
      break;
  }
}
