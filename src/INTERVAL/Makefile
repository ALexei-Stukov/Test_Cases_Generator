BIN=g++
CPP=g++ -c
INCLUDE=-I./ -I../../google_test/include/ 
LD=-L../../google_test/lib -lgtest

folder=$(notdir $(CURDIR))
OBJ=interval.o

all:$(OBJ)

interval.o:interval.cpp
	$(CPP) -o $@ $^ $(INCLUDE)

run_test:$(OBJ)
	cd ./$(folder)_test; make execute_test; cd ..;

remove_all_xml:
	cd ./$(folder)_test; make xml_clean; cd ..;

clean:
	rm ./*.bin -rf
	rm ./*.o -rf
	cd ./$(folder)_test;make clean;cd ..;