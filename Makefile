all::
	gcc main.c -o simulator handoff_simulator.h -lm

test::
	gcc test.c -o test handoff_simulator.h -lm

clean::
	rm ./simulator
	rm ./*.txt

clean_test::
	rm ./test
	rm ./*.txt

clean_data::
	rm ./*.txt