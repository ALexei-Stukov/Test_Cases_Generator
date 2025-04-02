generator.bin:generator.cpp enum_type.cpp range_type.cpp dag.hpp
	g++ -o $@ generator.cpp enum_type.cpp range_type.cpp -I./DAG/
run:
	./generator.bin input_file
clean:
	rm ./*.bin

dag.hpp: