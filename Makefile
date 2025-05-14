all:generator doc

generator:
	mkdir -p build
	cd src; make build; cd ..
	cp ./src/*.bin ./build
	cp ./src/input_file ./build

run:
	cd src; make run; cd ..
	
doc:
	doxygen Doxyfile
clean:
	rm ./build -rf
	rm ./doc/ -rf