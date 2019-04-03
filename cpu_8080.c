#include <stdlib.h>
#include "cpu_8080.c"

cpu_8080 create_cpu_8080(uint8_t (*read)(uint16_t), void (*write)(uint16_t, uint8_t)){
	return (cpu_8080) {.read = read, .write = write, .reg_A = 0, .reg_B = 0, .reg_C = 0, .reg_D = 0, .reg_E = 0, .reg_H = 0, .reg_L = 0, .reg_SP = 0, .reg_PC = 0, .cycles = 0, .halted = 0};
}

void execute_8080(cpu_8080 *cpu){
	unsigned char source_reg;
	unsigned char dest_reg;
	unsigned char source_value;
	
	opcode = cpu->read(cpu->reg_PC);

	if(!(opcode&0xC0) && (opcode&0x40)){//MOV
		source_reg = opcode&0x38;
		dest_reg = opcode&0x07;
		if(source_reg != 6 && dest_reg != 6){//If source or destination is not M
			cpu->registers[dest_reg] = cpu->registers[source_reg];
			cpu->cycles += 5;
		} else if(source_reg == 6 && dest_reg != 6){//If source is M
			source_value = cpu->read((((uint16_t) cpu->registers[REG_H_8080])<<8) | cpu->registers[REG_L_8080]);
			cpu->registers[dest_reg] = source_value;
			cpu->cycles += 7;
		} else if(source_reg != 6 && dest_reg == 6){//If destination is M
			source_value = cpu->registers[source_reg];
			cpu->write((((uint16_t) cpu->registers[REG_H_8080])<<8) | cpu->registers[REG_L_8080], source_value);
			cpu->cycles += 7;
		} else {//Halt instruction
			cpu->halted = true;
			cpu->cycles += 7;
		}
	} else if(!(opcode&0x40) && (opcode&0x80)){//Arithmetic/logical
		source_reg = opcode&0x07;
		if(source_reg == 6){//If source is M
			source_value = cpu->read((((uint16_t) cpu->registers[REG_H_8080])<<8) | cpu->registers[REG_L_8080]);
		} else {
			source_value = cpu->registers[source_regs];
		}
		if((opcode&0x38) == 0x00){//Add
			cpu->registers[REG_A_8080] += source_value;
		}
}
