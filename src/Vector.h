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
    void grow() { /* TODO */ }

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

    iterator begin() noexcept { /* TODO */ }
    iterator end() noexcept { /* TODO */ }

    [[nodiscard]] bool empty() const noexcept { /* TODO */ }
    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }

    T& at(size_t pos) { /* TODO */ }
    const T& at(size_t pos) const { /* TODO */ }
    T& operator[](size_t pos) { return array[pos]; }
    const T& operator[](size_t pos) const { return array[pos]; }
    T& front() { /* TODO */ }
    const T& front() const { /* TODO */ }
    T& back() { /* TODO */ }
    const T& back() const { /* TODO */ }

    void push_back(const T& value) { /* TODO */ }
    void push_back(T&& value) { /* TODO */ }
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
    public:
        iterator() { /* TODO */ }
        // Add any constructors that you may need

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { /* TODO */ }
        [[nodiscard]] pointer operator->() const noexcept { /* TODO */ }

        // Prefix Increment: ++a
        iterator& operator++() noexcept { /* TODO */ }
        // Postfix Increment: a++
        iterator operator++(int) noexcept { /* TODO */ }
        // Prefix Decrement: --a
        iterator& operator--() noexcept { /* TODO */ }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept { /* TODO */ }

        iterator& operator+=(difference_type offset) noexcept { /* TODO */ }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept { /* TODO */ }
        
        iterator& operator-=(difference_type offset) noexcept { /* TODO */ }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { /* TODO */ }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept { /* TODO */ }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept { /* TODO */ }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { /* TODO */ }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { /* TODO */ }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept { /* TODO */ }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept { /* TODO */ }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept { /* TODO */ }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept { /* TODO */ }
    };


    void clear() noexcept { /* TODO */ }
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept { /* TODO */ }

#endif
