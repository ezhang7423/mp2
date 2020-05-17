main:
	g++ main.cpp -o gobang
optimized:
	g++ -march=native -Ofast -frename-registers -fopenmp -D_GLIBCXX_PARALLEL main.cpp -o gobang
dev:
	nodemon -x "make main && ./gobang || exit 1" main.cpp