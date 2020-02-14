all: poisson_test analysis

poisson_test: poisson_test.cpp poisson.cpp
	g++ -O3 -std=c++11 -pthread -g3 -o $@ $^
	
analysis: analysis.cpp poisson.cpp
	g++ -O3 -std=c++11 -pthread -g3 -o $@ $^

clean:
	rm *.o poisson_test analysis

