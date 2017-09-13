// stack::push/pop
#include <iostream>       // std::cout
#include <stack>          // std::stack
using namespace std;

bool isOpening(char a){
    return (a=='[' || a=='(' || a=='[');
}

bool isClosing(char a){
    return (a==']' || a==')' || a=='[');
}

bool isMatched(string code){
    stack<char> codestack;
    for (int i=0; i<code.length(); ++i){
        if (isOpening(code[i]))
            stack.push(code[i]);

        if (isClosing(code[i]))
            stack.pop(); 
    }

    std::cout << "Popping out elements...";
    while (!codestack.empty())
    {
        std::cout << ' ' << codestack.top();
        codestack.pop();
    }
    std::cout << '\n';

    return 0;
}

int main (){

    isMatched("((add 1 2) {def int[] 3})");
    }
