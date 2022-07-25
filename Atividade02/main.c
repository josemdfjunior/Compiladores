#include <stdio.h>
#include <stdlib.h>

struct Cpu
{
  uint16_t pc;
  uint8_t a;
  uint8_t x;
  uint8_t y;
  uint8_t s;
  uint8_t p;
  uint8_t flags;
};

uint8_t memoria[0xFFFF];

// main
int main(int argc, char **argv)
{
  struct Cpu cpu;

  while (1)
  {
    uint8_t opcode = memoria[cpu.pc];
    switch (opcode)
    {
    // LDA
    case 0xA9:
      uint8_t valor = memoria[cpu.pc++];
      cpu.a = valor;
      cpu.pc++;
      break;
    // TAX
    case 0xAA:
      cpu.x = cpu.a;
      cpu.pc++;
      break;

    default:
      break;
    }
  }

  return EXIT_SUCCESS;
}
