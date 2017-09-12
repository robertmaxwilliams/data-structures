/*
 * Write a template 3
 * class Collection, that stores a collection of Objects (in an array), along
 * with the current size of the collection. Provide public functions isEmpty, makeEmpty, insert,
 * remove, and contains. contains(x) returns true if and only if an Object that is equal to x is
 * present in the collection.
 */

#include <cstring>
#include <iostream>
#include <sstream>      // std::stringstream

using namespace std;

template <typename Object>
class Collection
{

    public:

        Collection(){
            makeEmpty(); 
        }

        Object at(int i){
            if (i >= size){
                throw invalid_argument("out of range");
            }
            else if (i < 0){
                throw invalid_argument("negative index");
            }
            else
                return collection[i];
        }
            

        bool isEmpty(){
            return (size == 0);
        }

        void makeEmpty(){
            size = 0;
            collection = new Object[size];
        }

        string tostring(){
            stringstream buf;
            buf << "[";

            for (int i = 0; i < size; i++){
                buf << collection[i];

                if (i != size-1)
                    buf << ", ";
            }
            buf << "]";

            return buf.str();
        }

        void append(Object x){
           insert(x, size);
        }

        void insert(Object x, int i){
            Object * temp;
            temp = new Object[size+1];
            memcpy(temp, collection, i*sizeof(Object));
            memcpy(temp+i+1, collection+i, (size-i)*sizeof(Object));            
            temp[i] = x;
            delete [] collection;
            collection = temp;
            size += 1;
        }

        void remove(int i){
            Object * temp;
            temp = new Object[size-1];
            memcpy(temp, collection, i*sizeof(Object));
            memcpy(temp+i, collection+i+1, (size-i-1)*sizeof(Object));            
            delete [] collection;
            collection = temp;
            size -= 1;
        }

        bool contains(Object x){
            for (int i = 0; i < size; i++){
                if (collection[i] == x)
                    return true;
            }
            return false;
        }

    private:
        Object* collection;
        int size;

};

int main()
{
    Collection<char> foo;
    foo.append('a');
    cout << foo.tostring() << endl;

    foo.append('b');
    cout << foo.tostring() << endl;

    foo.append('c');
    cout << foo.tostring() << endl;
    
    foo.insert('x', 1);
    cout << foo.tostring() << endl;

    foo.remove(1);
    cout << foo.tostring() << endl;

    cout << "foo.contains('b') = " << foo.contains('b') << endl;
    cout << "foo.contains('x') = " << foo.contains('x') << endl;

    cout << endl;

    Collection<int> bar;
    bar.append(10);
    cout << bar.tostring() << endl;

    bar.append(20);
    cout << bar.tostring() << endl;

    bar.append(30);
    cout << bar.tostring() << endl;

    bar.insert(99, 1);
    cout << bar.tostring() << endl;

    bar.remove(1);
    cout << bar.tostring() << endl;

    cout << "bar.contains(20) = " << bar.contains(20) << endl;
    cout << "bar.contains(99) = " << bar.contains(99) << endl;
    cout << "bar.isEmpty() = " << bar.isEmpty() << endl;
    

   
}



