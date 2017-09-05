/*
 * . Write a recursive function that returns the number of 1 in the binary representation of N. Use the
 * fact that this is equal to the number of 1 in the representation of N/2, plus 1, if N is odd. 1
 */

#include <iostream>
using namespace std;

int count_ones(int x){
    if (x == 0)
        return 0;
    return (x%2) + count_ones(x/2);
}
int main(){
    cout << count_ones(7) << endl;
    return 0;
}

