#include <stdint.h>
#include <stdbool.h>

//4/2/2019

//Flag bit positions
#define FLAG_S_8080 7
#define FLAG_Z_8080 6
#define FLAG_P_8080 2
#define FLAG_C_8080 0
#define FLAG_AC_8080 4

//Register_orders
//These are used to shorten the code for emulating MOV instructions
#define REG_B_8080 0
#define REG_C_8080 1
#define REG_D_8080 2
#define REG_E_8080 3
#define REG_H_8080 4
#define REG_L_8080 5
//6 is used for the "M" destination, which isn't a register.
#define REG_A_8080 7

typedef struct cpu_8080 cpu_8080;

struct cpu_8080{
	//Memory I/O callbacks
	uint8_t (*read)(uint16_t);
	void (*write)(uint16_t, uint8_t);
	//Registers
	uint8_t registers[8];//Index 6 is unused
	uint16_t reg_SP;
	uint16_t reg_PC;
	//Number of clock cycles passed
	uint64_t cycles;

	bool halted;
};

