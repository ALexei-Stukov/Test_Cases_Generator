generator.bin:generator.cpp enum_type.cpp
	g++ -o $@ $^ -I./DAG/
run:
	./generator.bin input_file
clean:
	rm ./*.bin