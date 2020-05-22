main:
	g++ -pthread main.cpp -o gobang
optimized:
	g++ -pthread -march=native -Ofast -frename-registers -fopenmp -D_GLIBCXX_PARALLEL main.cpp -o gobang
dev:
	nodemon -x "make main && PROD=FALSE ./gobang || exit 1" main.cpp
deploy:
	./deploy.sh