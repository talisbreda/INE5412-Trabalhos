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
	printf("Qual algoritmo deseja utilizar?\n");
	printf("1 - RM\n");
	printf("2 - EDF\n");
	int alg;
	scanf("%d", &alg);
	if (alg == 2) {
		printf("Initializing EDF scheduler\n");
		EDF* edf = new EDF(cpu);
		edf->execute();
		delete edf;
	}	else if (alg == 1){
		printf("Initializing RM scheduler\n");
		RM* rm = new RM(cpu);
		rm->execute();
		delete rm;
	} else {
		printf("Insira apenas 1 ou 2\n");
	}
	delete cpu;
}