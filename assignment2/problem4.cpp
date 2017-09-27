//Given two sorted lists, L1 and L2, return their intersection i.e. elements in L2 not found in L1
#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> L1 = {2, 4, 6, 8, 10};
    list<int> L2 = {1, 2, 3, 4, 5};

    auto iter1 = L1.begin(), end1 = L1.end();
    auto iter2 = L2.begin(), end2 = L2.end();

    while(iter2 != end2 && iter1 != end1){
        if (*iter1 == *iter2){
            iter2++;
            iter1++;
        }
        else{
            cout << *iter2 << endl;
            iter2++;
        }
    }
}
