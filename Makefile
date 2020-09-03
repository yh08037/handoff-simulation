all::
	gcc main.c -o handoff_simulator handoff_simulator.h -lm

clean::
	rm ./handoff_simulator