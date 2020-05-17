#include <iostream>
using namespace std;
int main(){
    int **arr = new int *[300];
    cout <<  arr[0] << endl;
    for (int i = 0; i < 300; i++){
        arr[i] = new int[300];
    }
    for (int i = 0; i < 300; i++){
        for (int j = 0 ; j < 300; j++){
            arr[i][j] = 3 * i + j;
        }
    }
    for (int i = 0; i < 300; i++){
        for (int j = 0 ; j < 300; j++){
            cout << arr[i][j] << " ";
        }
    }
    
}