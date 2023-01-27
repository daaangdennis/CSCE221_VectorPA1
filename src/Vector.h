#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() {
        if(_capacity == 0)
        {
            _capacity++;
            T* new_array = new T[_capacity];
            delete[] array;
            array = new_array;
            return;
        }
        _capacity = _capacity * 2;
        T* new_array = new T[_capacity];
        for(size_t index = 0; index < _size; index++)
        {
            new_array[index] = array[index];
        }
        delete[] array;
        array = new_array;
    }

public:
    Vector() noexcept {
        array = nullptr;
        _capacity = 0;
        _size = 0;
    }
    Vector(size_t count, const T& value) {
        array = new T[count];
        _capacity = count;
        _size = count;
        for(size_t index = 0; index < count; index++)
        {
            array[index] = value;
        }
    }
    explicit Vector(size_t count) { 
        array = new T[count];
        _capacity = count;
        _size = count;
    }
    Vector(const Vector& other) {
        _capacity = other._capacity;
        _size = other._size;
        array = new T[_capacity];
        for(size_t index = 0; index < _size; index++)
        {
            array[index] = other.array[index];
        }
        
    }
    Vector(Vector&& other) noexcept {
        array = other.array;
        _capacity = other._capacity;
        _size = other._size;

        other.array = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    ~Vector() {
        delete[] array;
    }

    Vector& operator=(const Vector& other) { /* TODO */ 
        if(this != &other)
        {
            delete[] array;
            this->_capacity = other._capacity;
            this->_size = other._size;
            this->array = new T[other._capacity];

            for(size_t index = 0; index < other._size; index++)
            {
                this->array[index] = other.array[index];
            }
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept { /* TODO */ 
        if(this != &other)
        {
            delete[] array;
            this->_capacity = other._capacity;
            this->_size = other._size;
            this->array = other.array;

            other.array = nullptr;
            other._capacity = 0;
            other._size = 0;
        }
        return *this;
    }

    iterator begin() noexcept {
        if(_size != 0)
        {
            return iterator(&array[0]);
        }
        return nullptr;
    }
    iterator end() noexcept { 
        if(_size != 0)
        {
            iterator temp{array+_size};
            return temp;
        }
        return nullptr;
        
    }

    [[nodiscard]] bool empty() const noexcept {
        if(_size == 0)
        {
            return true;
        }
        return false;
    }
    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }

    T& at(size_t pos) {
        if(pos < 0 || pos >= _capacity)
        {
            throw std::out_of_range("index out of range");
        }
        return array[pos];
    }
    const T& at(size_t pos) const {
        if(pos < 0 || pos >= _capacity)
        {
            throw std::out_of_range("index out of range");
        }
        return array[pos];
     }
    T& operator[](size_t pos) { return array[pos]; }
    const T& operator[](size_t pos) const { return array[pos]; }
    T& front() { return array[0]; }
    const T& front() const { return array[0]; }
    T& back() { return array[_size-1]; }
    const T& back() const { return array[_size-1]; }

    void push_back(const T& value) {
        if(_size == _capacity)
        {
            grow();
            array[_size] = value;
            _size++;
            return;
        }
        array[_size] = value;
        _size++;
    }
    void push_back(T&& value) {
        if(_size == _capacity)
        {
            grow();
            array[_size] = value;
            _size++;
            return;
        }
        array[_size] = value;
        _size++;
    }
    void pop_back() { /* TODO */ }

    iterator insert(iterator pos, const T& value) { /* TODO */ }
    iterator insert(iterator pos, T&& value) { /* TODO */ }
    iterator insert(iterator pos, size_t count, const T& value) { /* TODO */ }
    iterator erase(iterator pos) { /* TODO */ }
    iterator erase(iterator first, iterator last) { /* TODO */ }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
        pointer ptr;

    public:
        iterator() {ptr = nullptr;}
        // Add any constructors that you may need
        iterator(pointer point) {ptr = point;}
        
        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { return *ptr; }
        [[nodiscard]] pointer operator->() const noexcept { return ptr; }

        // Prefix Increment: ++a
        iterator& operator++() noexcept { ptr++; return *this;}
        // Postfix Increment: a++
        iterator operator++(int) noexcept {iterator temp = *this; ptr++; return temp;}
        // Prefix Decrement: --a
        iterator& operator--() noexcept { ptr--; return *this; }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept {iterator temp = *this; ptr--; return temp; }

        iterator& operator+=(difference_type offset) noexcept { ptr += offset; return *this; }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept {iterator temp = *this; temp.ptr += offset; return temp; }
        
        iterator& operator-=(difference_type offset) noexcept { ptr -= offset; return *this; }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { iterator temp = *this; temp.ptr -= offset; return temp; }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept {return (this->ptr - rhs.ptr); }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept { return *(ptr + offset); }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { return this->ptr == rhs.ptr; }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { return this->ptr != rhs.ptr; }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept { return this->ptr < rhs.ptr; }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept { return this->ptr > rhs.ptr; }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept { return this->ptr <= rhs.ptr; }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept { return this->ptr >= rhs.ptr; }
    };


    void clear() noexcept { 
        T* empty_array = new T[_capacity];
        delete[] array;
        _size = 0;
        array = empty_array;
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
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept { _Iterator temp{iterator + offset}; return temp;}

#endif
