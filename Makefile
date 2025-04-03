build:generator.cpp enum_type.cpp range_type.cpp
	g++ -o generator.bin $^ -I./DAG/
run:
	./generator.bin input_file
clean:
	rm ./*.bin