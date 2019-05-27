all: app compiler

app: app.o
	gcc -o TextMiningApp app.o

app.o: ./src/app/main.c
	gcc -o app.o -c ./src/app/main.c -Wall -O3

compiler: compiler.o
	gcc -o TextMiningCompiler compiler.o

compiler.o: ./src/compiler/main.c
	gcc -o compiler.o -c ./src/compiler/main.c -Wall -O3

clean:
	rm -f *.o

mrproper: clean
	rm -f TextMiningApp TextMiningCompiler
