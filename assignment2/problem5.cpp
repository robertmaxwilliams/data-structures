#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <new>

template <class T>
class cVector
{
public:
    typedef typename std::size_t size_type;
private:
    size_type _size;
    size_type _capacity;
    T* _data;

    static T*
    allocate(size_type size)
    {
        return static_cast<T*>(malloc(sizeof(T) * size));
    }
    static void
    copyRange(T* begin, T* end, T* dest)
    {
        while(begin != end)
        {
            new((void*)dest) T(*begin);
            ++begin;
            ++dest;
        }
    }
    static void
    deleteRange(T* begin, T* end)
    {
        while(begin != end)
        {
            begin->~T();
            ++begin;
        }
    }

public:
    typedef T* iterator;
    typedef T value_type;

    cVector()
    {
        _size = 0;
        _capacity = 0;
        _data = 0;
    }
    ~cVector()
    {
        deleteRange(_data, _data + _size);
        free(_data);
    }

    // needs some other constructors
    // size(), empty() and a bunch of other methods!

    void push_back(const T& value)
    {
        if(_size != _capacity)
        {
            new((void*)(_data + _size)) T(value);
            ++_size;
            return;
        }
        size_type newCapacity = _capacity ? _capacity * 2 : 1;
        T* newData = allocate(newCapacity);
        copyRange(_data, _data + _size, newData);
        new((void*)(newData + _size)) T(value);
        deleteRange(_data, _data + _size);
        free(_data);
        _data = newData;
        _capacity = newCapacity;
        ++_size;
    }
    T&
    operator[](size_type index)
    {
        if (index >= _size){
            throw std::invalid_argument("not enough long");
        }
        return _data[index];
    }
    const T&
    operator[](size_type index) const
    {
        return _data[index];
    }
    T*
    begin() const
    {
        return _data;
    }
    T*
    end() const
    {
        return _data + _size;
    }
};

int main(){
    cVector<int> lottery;
    lottery.push_back(3);
    lottery.push_back(5);
    lottery.push_back(9);
    lottery.push_back(1);
    lottery.push_back(7);
    lottery.push_back(10);
    
    std::cout << lottery[2] << std::endl;
    std::cout << lottery[200] << std::endl;
}
