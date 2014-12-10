all: hello

hello:  gcdriver.o gc.o su.o 
	g++ lpdriver.o  gc.o su.o -o hello

gcdriver.o: lpdriver.cpp
	g++ -c lpdriver.cpp

gc.o: LabelPropagation.cpp
	g++ -c  LabelPropagation.cpp -o gc.o

su.o: StringUtilities.cpp
	g++ -c StringUtilities.cpp -o su.o

clean:
	rm -rf *o hello
