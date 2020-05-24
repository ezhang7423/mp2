#include "./funcs.cpp"
#include <string>
// copy
// add
// multiply
// const int THREADS_NUMBER = 8;

struct im2col {

  static mat3 indices(mat3 &in, int h, int w, int s, int p) {
    mat3 *res = new mat3(in.depth, in.row_size + p, in.col_size + p);
    int d = 0;
    for (auto &&m : res->arr) {
      // for each matrix
      for (int i = p; i < in.row_size + p; i++) {
        for (int j = p; j < in.col_size + p; j++) {
          m->arr[i][j] = in.arr[d]->arr[i - p][j - p];
        }
      }
      d++;
    }
    mat3 col = cols(in, h, w, s, p);
  }
  static mat3 cols(mat3 &shape, int h, int w, int s, int p) {
    int channels = shape.depth;
    int row = shape.row_size;
    int col = shape.col_size;
    int outputsize = (26 - h + 2 * p) / s + 1;
    list i0 = repeat(arange(0, h), w);
    i0 = tile(i0, channels);
    list i1 = repeat(arange(0, outputsize), outputsize);
    for (auto &&i : i1) {
      i *= s;
    }
    list j0 = tile(arange(0, w), h * channels);
    list j1 = tile(arange(0, outputsize), outputsize);
    for (auto &&i : j1) {
      i *= s;
    }
    mat i = broadcast(i1, i0);
    mat j = broadcast(j1, j0);
    mat k = reshape(repeat(arange(0, channels), h * w), -1, 1);
    mat3 *res = new mat3(3, i.row_size, i.col_size);
    res->arr[0] = &k;
    res->arr[1] = &i;
    res->arr[2] = &j;
    return *res;
  }
};
class Conv {
public:
  Conv(int numfilters, tupl filtersize, int stride = 1, int padding = 2)
      : numfilters(numfilters), filtersize(filtersize), stride(stride),
        padding(padding) {
    filters = mat3(numfilters, filtersize.first, filtersize.second, 0, true);
    // assuing square filter and matrix
    int outputsize = (26 - filtersize.first + 2 * padding) / stride + 1;
    bias = mat(outputsize, outputsize, 0, true);
  }
  mat3 forwardP(mat3 in){
      // forward propagation
      mat3 X = im2col.indices(in, filters.row_size, filters.col_size, stride,
                              padding)};
  void setWeights() {} // for existing model
  mat3 backP(){
      // backward prop

  };

private:
  int padding;
  int numfilters;
  tupl filtersize;
  int stride;
  mat3 filters;
  mat bias;
};
