all: testSorv
	
testSorv:
	g++-4.8 -std=c++11 sorv.cpp test_sorv.cpp -O3 -o testSorv

clean:
	rm testSorv
