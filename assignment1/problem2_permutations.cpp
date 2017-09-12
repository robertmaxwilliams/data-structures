/*
 * Write the routines with the following declarations:
 * void permute( const string & str );
 * void permute( const string & str, int low, int high );
 * The first routine is a driver that calls the second and prints all the permutations of the characters
 * in string str. If str is "abc", then the strings that are output are abc, acb, bac, bca, cab, and
 * cba. Use recursion for the second routine. 2
 * How many permutations for a string of length l?
 */


#include <iostream>
using namespace std;

int permutations = 0;
int calls = 0;
int steps = 0;

void permute(const string &str, int high, int low){
    calls++;

    if (low == high-1)
    {
        cout << str << endl;
        permutations++;
        return;
    }
        
    for (int i = 0; i < high-low; i++)
    {
        steps++;

        string front = str.substr(0, low);
        string letter = str.substr(i+low, 1);
        string before_letter = str.substr(low, i);
        string after_letter = str.substr(low+i+1);

        permute(front + letter + before_letter + after_letter, high, low+1);

    }

}


void permute(const string &str){
    permute(str, str.length(), 0);
}

int main(){
    permute("abcdefghij");
    cout << "permutations: " << permutations << endl;
    cout << "calls: " << calls << endl;
    cout << "steps: " << steps << endl;
}
