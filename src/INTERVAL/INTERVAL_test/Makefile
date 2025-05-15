BIN=g++
CPP=g++ -c
INCLUDE=-I./ -I../ -I../../../google_test/include/ 
LD=-L../../../google_test/lib -lgtest

test_name=$(notdir $(CURDIR))
DATE=$(shell date +"%Y-%m-%d %H:%M:%S")

test.bin:../interval.o function_test.cpp test.cpp
	$(BIN) -o $@ $^ $(INCLUDE) $(LD)

execute_test:test.bin
	./test.bin --gtest_catch_exceptions --gtest_output="xml:$(test_name)_$(DATE).xml" || true

xml_clean:
	rm -f ./.xml
	rm -f ./*.xml

clean:
	rm ./*.bin -rf
	rm ./*.o -rf