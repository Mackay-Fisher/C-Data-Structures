#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same
using namespace std;
template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() {
        int i;
        int new_capacity=0;
            if (_capacity==0)
            {
               new_capacity=1;
            }else
            {
                new_capacity=_capacity*2;
            }
            T* temp = new T[new_capacity];
            for ( i = 0; i < _capacity; i++)
            {
            temp[i]=std::move(array[i]);
            }
            _capacity=new_capacity;
            delete array;
            array=temp;
    }

public:
    Vector() noexcept { 
        _capacity=0;
        _size=0;
        array=nullptr;
    }
    Vector(size_t count, const T& value) {
        _capacity=count;
        _size=count;
        array=new T[_capacity];
        for (int i = 0; i < count; i++)
        {
            array[i]=value;
        }
    }
    explicit Vector(size_t count) { 
        _capacity = count;
        _size=count;
        array= new T[_capacity]();
    }
    Vector(const Vector& other) { 
        _size=other._size;
        _capacity=other._size;
        array = new T[other._size];
        for ( unsigned int i = 0; i < other._size; i++)
        {
            array[i]=other.array[i];
        }
    }
    Vector(Vector&& other) noexcept { 
        _size=other._size;
        _capacity=other._capacity;
        array=other.array;
        other.array=nullptr;
        other._size=0;
        other._capacity=0;
    }

    ~Vector() 
    { 
    delete [] array;
    _size=0;
    _capacity=0; 
    }

    Vector& operator=(const Vector& other) { 
        if (this==&other)
        {
            return *this;
        }
        if (array)
        {
            delete array;
        }
        array = new T[other._capacity];
        for (int i = 0; i < other._size; i++)
        {
            array[i]=other.array[i];
        }
        _size=other._size;
        _capacity=other._capacity;
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept { 
        if (this==&other)
        {
            return *this;
        }
        if(array){
            delete array;
        }
        _size=other._size;
        _capacity=other._capacity;
        array=other.array;
        other.array=nullptr;
        other._size=0;
        other._capacity=0;
        return * this;        

    }

    iterator begin() noexcept { 
        if(this->_size==0){
            return nullptr;
        }
        return{&array[0]};
    }
    iterator end() noexcept { 
        if(this->_size==0){
            return nullptr;
        }
        else return{array+_size};
    }

    [[nodiscard]] bool empty() const noexcept { 
        if (_size==0)
        {
            return true;
        }
        else return false;
    }
    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }

    T& at(size_t pos) 
    { 
        if (pos>=_size)
        {
            throw std::out_of_range ("The postion requested is outside the scope of the vector");
        }
        else{
            return array[pos];
        }
    }
    const T& at(size_t pos) const 
    { 
        if (pos>=_size)
        {
            throw std::out_of_range ("The postion requested is outside the scope of the vector");
        }
        else{
            return array[pos];
        }
    }
    T& operator[](size_t pos) 
    { 
    return array[pos];
    }
    const T& operator[](size_t pos) const { return array[pos]; }
    T& front() { return array[0]; }
    const T& front() const { return array[0]; }
    T& back() {return array[_size-1];}
    const T& back() const {return array[_size-1];}

    void push_back(const T& value) { 
        int i;
        if (_size>=_capacity)
        {
            int new_capacity=0;
            if (_capacity==0)
            {
               new_capacity=1;
            }else
            {
                new_capacity=_capacity*2;
            }
            T* temp = new T[new_capacity];
            for ( i = 0; i < _capacity; i++)
            {
            temp[i]=array[i];
            }
            _capacity=new_capacity;
            delete array;
            array=temp;
            array[_size]=value;
            _size++;
            
        }
        else{
        array[_size]=value;
        _size++;
        } 
    }
    void push_back(T&& value) { 
        int i;
        if (_size>=_capacity)
        {
            int new_capacity=0;
            if (_capacity==0)
            {
               new_capacity=1;
            }else
            {
                new_capacity=_capacity*2;
            }
            T* temp = new T[new_capacity];
            for ( i = 0; i < _capacity; i++)
            {
            temp[i]=std::move(array[i]);
            }
            _capacity=new_capacity;
            delete array;
            array=temp;
            array[_size]=std::move(value);
            _size++;
            
        }
        else{
        array[_size]=std::move(value);
        _size++;
        } 
    }
    void pop_back() { 
        _size--;
    }

    iterator insert(iterator pos, const T& value) { 
        int index=pos-begin();
        while (_size+1>=_capacity)
        {
            grow();
        }
        for (int i = _size-1; i >= index; i--)
        {
            array[i+1]=std::move(array[i]);
        }
        array[index]=value;
        _size++;
        return (begin()+index);
        
    }
    iterator insert(iterator pos, T&& value) { 
        int index=pos-begin();
        while (_size+1>=_capacity)
        {
            grow();
        }
        for (int i = _size-1; i >= index; i--)
        {
            array[i+1]=std::move(array[i]);
        }
        array[index]=std::move(value);
        _size++;
        return (begin()+index);
    }
    iterator insert(iterator pos, size_t count, const T& value) { 
        int index=pos-begin();
        while (_size+count>=_capacity)
        {
            grow();
        }
        for (int i = _size+count-1; i >= index+count; i--)
        {
            array[i]=std::move(array[i-count]);
        }
        for (int i = index; i < index+count; i++)
        {
            
            array[i]=value;
        }
        _size+=count;
        return (begin()+index);
    }
    iterator erase(iterator pos) { 
        int index = pos-begin();
        for (int i = index; i < _size-1; i++)
        {
            array[i]=std::move(array[i+1]);
        }
        _size--;
        return(begin()+index);
    }
    iterator erase(iterator first, iterator last) { 
        int index = first-begin();
        int count = (last - first);
        for (int i = index; i < _size-count; i++)
        {
            array[i]=std::move(array[i+count]);
        }
        _size-=count;
        return(begin()+index);
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        T* spec;
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
    public:
        iterator() { 
            spec=nullptr;
        }
        // Add any constructors that you may need
        iterator(T* other){
            spec=other;
        }
        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { 
            return *spec;
        }
        [[nodiscard]] pointer operator->() const noexcept { 
            return spec;
        }

        // Prefix Increment: ++a
        iterator& operator++() noexcept { 
            ++(this->spec);
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept { 
            T* temp= this->spec;
            ++(this->spec);
            return iterator(temp);
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept { 
            --(this->spec);
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept { 
            T* temp= this->spec;
            --(this->spec);
            return iterator(temp);
        }

        iterator& operator+=(difference_type offset) noexcept { 
           spec+= offset;
           return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept { 
            return iterator (this->spec+offset);
        }
        iterator& operator-=(difference_type offset) noexcept { 
            spec-= offset;
           return *this;
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { 
            return iterator (this->spec-offset);    
        }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept { 
           return (spec-rhs.spec); 
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept { 
            return spec[offset];
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { 
            if(spec==rhs.spec){
                return true;
            }
            else return false;
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { 
            if(spec!=rhs.spec){
                return true;
            }
            else return false;
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept {
            if(spec<rhs.spec){
                return true;
            }
            else return false;
        }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept {
            if(spec>rhs.spec){
                return true;
            }
            else return false;
        }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept {
            if(spec<=rhs.spec){
                return true;
            }
            else return false;
        }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept {
            if(spec>=rhs.spec){
                return true;
            }
            else return false;
        }
    };


    void clear() noexcept { 
    delete [] array;
    array=nullptr;
    _size=0;
    }
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept { 
    return _Iterator (iterator+offset);
}

#endif