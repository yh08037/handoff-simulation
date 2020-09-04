all::
	gcc main.c -o simulator handoff_simulator.h -lm

test::
	gcc test.c -o test handoff_simulator.h -lm

clean::
	rm ./simulator
	rm ./data.txt
	rm ./data_d.txt
	rm ./data_r.txt
	rm ./data_s.txt
	rm ./data_t.txt

clean_test::
	rm ./test
	rm ./data.txt