generator.bin:generator.cpp enum_type.cpp
	g++ -o $@ $^
clean:
	rm ./*.bin