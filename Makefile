all:
	mkdir -p build 
	gcc src/main.c -o build/exec
clean:
	rm  build/*.*
run:
	./build/exec