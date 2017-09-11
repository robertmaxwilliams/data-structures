/*
 * Write a template 3
 * class Collection, that stores a collection of Objects (in an array), along
 * with the current size of the collection. Provide public functions isEmpty, makeEmpty, insert,
 * remove, and contains. contains(x) returns true if and only if an Object that is equal to x is
 * present in the collection.
 */

template <typename Object>
class Collection
{
    public:

        InitCell(){
            collection = {};
            size = 0;
        }

            

        bool isEmpty(){
            return this.size == 0;
        }

        void makeEmpty(){
            this.size = 0;
            this.collection = {};
        }

        void insert(Object x){
            Object * temp;
            temp = new Object [++size];
            memcpy(temp, 


    private:
        Object collection[];
        int size = 0;
