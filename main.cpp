#include <process_control_block.h>
#include <file.h>
#include <process.h>
#include <bits/stdc++.h>

#include <cpu.h>
#include <RM.h>
#include <EDF.h>

int main(int argc, char **argv)
{
	CPU* cpu = new CPU();
	if (strcmp(argv[1], "edf") == 0) {
		printf("Initializing EDF scheduler\n");
		EDF* edf = new EDF(cpu);
		edf->execute();
	}	else {
		printf("Initializing RM scheduler\n");
		RM* rm = new RM(cpu);
		rm->execute();
	}
}