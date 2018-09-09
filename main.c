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
  switch(instr) {
    case HLT:
      running = 0;
      break;

  }
}
