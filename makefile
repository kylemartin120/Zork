main: main.cpp
	g++ -o main -Iinclude main.cpp source/*
	./main
	rm main
