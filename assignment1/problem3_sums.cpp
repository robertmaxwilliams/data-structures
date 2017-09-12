/*
 * Evaluate the following sums:
(a) P∞
i=0
1
4
i
(b) P∞
i=0
i
4
i

 */

#include <iostream>
using namespace std;

int main()
{
    cout << "Sum of 1/4^i from i=0 to inf is 1/(1-1/4) by the sum formula. 1/(1-1/4) = " << 1/(1-0.25) << endl;
    cout << "The sum of i/4^i is vastly more complex to solve. lim as i-> inf of (4^(n+1)-3n-4)/(9*4^n) = " << 9.0/5 << endl;

}
