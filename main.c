#include <stdio.h>

typedef unsigned short word;

struct CPU {
    word pc;         
    int regs[16];    
};

word program_memory[65536];
unsigned char data_memory[65536];

void run_cpu(struct CPU *cpu) {
    int running = 1;
    while (running) {
        word instr = program_memory[cpu->pc];

        
        int p1 = (instr >> 12) & 0xF;
        int p2 = (instr >> 8)  & 0xF;
        int p3 = (instr >> 4)  & 0xF;
        int p4 = instr & 0xF;

        switch (p1) {
            case 0x0:
                cpu->regs[p2] = cpu->regs[p3] + cpu->regs[p4];
                cpu->pc++;
                break;

            case 0x2:
                cpu->regs[p2] = data_memory[cpu->regs[p3] + p4];
                cpu->pc++;
                break;

            case 0x4:
                if (cpu->regs[p2] == cpu->regs[p3]) {
                    cpu->pc = p4;
                } else {
                    cpu->pc++;
                }
                break;

            case 0xE:
                cpu->pc = p2;
                break;

            default:
                running = 0;
                break;
        }
    }
}

int main (){}