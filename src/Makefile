BIN=g++
CPP=g++ -c
INCLUDE=-I./DAG/ -I./INTERVAL/
OBJ=generator.o interval.o enum_type.o range_type.o

build:$(OBJ)
	$(BIN) -o generator.bin $^ $(INCLUDE)

interval.o:interval.cpp
	$(CPP) -o $@ $^ $(INCLUDE)

generator.o:generator.cpp
	$(CPP) -o $@ $^ $(INCLUDE)

enum_type.o:enum_type.cpp
	$(CPP) -o $@ $^ $(INCLUDE)

range_type.o:range_type.cpp
	$(CPP) -o $@ $^ $(INCLUDE)

run:build
	./generator.bin input_file

clean:
	rm ./*.bin -rf
	rm ./*.o -rf