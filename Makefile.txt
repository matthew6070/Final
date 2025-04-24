#This is the makefile that runs the directives
#Author: Error 404
#CPSC1070 - Spring 2025
#Final Project
compile:
	g++ -Wall final.cpp -o final.out

run:
	./final.out

clean:
	rm *.out
