#include <process_control_block.h>
#include <file.h>
#include <process.h>
#include <bits/stdc++.h>

#include <cpu.h>
#include <RM.h>

int main()
{
	CPU* cpu = new CPU();
	RM* rm = new RM(cpu);
	rm->execute();
}