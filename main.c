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

typedef enum {
  A,
  B,
  C,
  D,
  E,
  IP,
  SP,
  REGN
} Registers;

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  SET, A, 5,
  HLT
};

int running = 1;
int stack[100];
int registers[REGN];

#define sp (registers[SP])
#define ip (registers[IP])

int main()
{
  sp = -1;
  ip = 0;
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

    case SET:
      x = program[++ip];
      y = program[++ip];
      registers[x] = y;
      break;
  }
}
