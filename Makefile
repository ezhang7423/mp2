optimized:
	g++ -march=native -Ofast -frename-registers -fopenmp -D_GLIBCXX_PARALLEL main.cpp