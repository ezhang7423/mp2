#include "../matrix.cpp"
#include "./funcs.cpp"
// copy
// add
// multiply
// const int THREADS_NUMBER = 8;

class im2col {};
class Conv {
public:
  Conv(int numfilters, tupl filtersize, int stride)
      : numfilters(numfilters), filtersize(filtersize), stride(stride) {
    filters =
        mat3(numfilters, filtersize.first, filtersize.second, rand = true);
  }

private:
  int numfilters;
  tupl filtersize;
  int stride;
  mat3 filters;
};
