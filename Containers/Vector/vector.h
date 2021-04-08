#pragma once
#include <iostream>
#include <exception>

template <class Type>
class Vector
{
private:
    Type* _data;
    size_t _size;
    size_t _capacity;
    static const size_t kDefCapacity = 10;
    const double kDefMultiplier = 1.5;

public:
    struct iterator
    {
        Type* _ptr;
        iterator(Type* ptr = nullptr) : _ptr(ptr){}

        Type const& operator*() const
        {
            if(!_ptr)
                throw std::runtime_error("empty iterator");
            return *_ptr;
        }

        bool operator==(iterator const& it)
        {
            return _ptr == it._ptr;
        }

        bool operator!=(iterator const& it)
        {
            return !(*this == it);
        }

        iterator& operator++()
        {
            if(!_ptr)
                throw std::runtime_error("empty iterator");
            ++_ptr;
            return *this;
        }

        iterator operator++(int)
        {
            if (!_ptr)
                throw std::runtime_error("empty iterator");
            Type* tmp = _ptr;
            ++_ptr;
            return iterator(tmp);
        }

        iterator& operator--()
        {
            if(!_ptr)
                throw std::runtime_error("empty iterator");
            --_ptr;
            return *this;
        }

        iterator operator--(int)
        {
            if (!_ptr)
                throw std::runtime_error("empty iterator");
            Type* tmp = _ptr;
            --_ptr;
            return iterator(tmp);
        }
    };

    ~Vector();
    Vector(Vector const& vec) :Vector(vec._data, vec._size) {}
    Vector& operator=(Vector const& vec);

    Vector();
    Vector(size_t capacity = 0);
    Vector(Type* data, size_t size);

    Type& operator[](int idx);
    Type const& operator[](int idx)const;

    void push_back(Type const& val);
    void erase(iterator to_die);
    //void insert(Type const& val, iterator it_after);

    void resize(size_t new_size);
    void clear();
    iterator find(Type const& to_find)
    {
        for (auto it = begin(); it != end(); ++it)
            if (*it == to_find)
                return it;
        return end();
    }


    iterator begin() { return iterator(_data); }
    iterator end() { return iterator(_data + _size); }
};

template <class Type>
Vector<Type>::Vector() :_data(nullptr),
                        _size(0),
                        _capacity(kDefCapacity) {}

template <class Type>
Vector<Type>::Vector(size_t capacity) : _capacity(capacity), _data(nullptr)
{
    if (_capacity != 0)
        //_data = new Type[_capacity];
        _data = (Type*)::operator new(_capacity * sizeof(Type));
    _size = 0;
}

template <class Type>
Vector<Type>::Vector(Type* data, size_t size) : _capacity(kDefCapacity)
{
    if (size > _capacity)
        _capacity *= kDefMultiplier;

    _size = size;
    //_data = new Type[_capacity];
    _data = (Type*)::operator new(_capacity * sizeof(Type));
    for (size_t idx = 0; idx < _size; ++idx)
        new(_data + idx) Type(data[idx]);
        //_data[idx] = data[idx];
}

template <class Type>
Vector<Type>::~Vector()
{
    clear();    
}



template<class Type>
Vector<Type>& Vector<Type>::operator=(Vector<Type> const& vec)
{
    if (_capacity < vec._capacity)
    {
        _data = reinterpret_cast<Type*>(::operator new(vec._capacity * sizeof(Type)));
        _capacity = vec._capacity;
    }

    for (size_t idx = 0; idx < vec.size; ++idx)
        new(_data + idx) Type(vec._data[idx]);

    _size = vec.size;
    return *this;
}

template<class Type>
Type const& Vector<Type>::operator[](int idx) const
{
    if (idx < 0 || idx >= _size)
        throw std::exception("index out of bounds");

    return _data[idx];
}

template<class Type>
Type& Vector<Type>::operator[](int idx)
{
    if (idx < 0 || idx >= _size)
        throw std::exception("index out of bounds");

    return _data[idx];
}



template <class Type>
void Vector<Type>::push_back(Type const& val)
{
    if (_capacity <= 1)
    {
        _capacity = kDefCapacity;
        /*_data = new Type[_capacity];
       _data[0] = val;*/
        _data = reinterpret_cast<Type*>(::operator new(_capacity * sizeof(Type)));
        new(_data) Type(val);       
        _size = 1;
        return;
    }

    if (_size == _capacity)
    {
        _capacity *= kDefMultiplier;
        Type* tmp_data = reinterpret_cast<Type*>(::operator new(_capacity * sizeof(Type)));
        for (size_t idx = 0; idx < _size; ++idx)
            new(tmp_data+idx) Type( _data[idx]);
        clear();
        _data = tmp_data;
    }

    new(_data + (_size++)) Type(val);
}

template <class Type>
void Vector<Type>::erase(iterator to_die)
{   
    for (auto it = to_die; it != --end(); ++it)
    {
        //TODO
    }

    --_size;
       
    /*for (size_t idx = erase_idx; idx < _size - 1; ++idx)
    {
        _data[idx].~Type();
        new(_data + idx) Type(_data[idx + 1]);
    }

    tmp.~Type();
    --_size;*/
}

/*template <class Type>
void Vector<Type>::insert(Type const& val, iterator it_after)
{
    //TODO!!!
    if (ptr_after >= _size)
        throw std::out_of_range;

    _capacity *= kDefMultiplier;
    Type* tmp_data = new Type[_capacity];
    for (size_t idx = 0; idx < ptr_after; ++idx)
        tmp_data[idx] = _data[idx];

    tmp_data[ptr_after] = val;
    for (size_t idx = ptr_after + 1; idx < _size + 1; ++idx)
        tmp_data[idx] = _data[idx - 1];

    delete[] _data;
    _data = tmp_data;
    ++_size;
}*/

template<class Type>
void Vector<Type>::resize(size_t new_size)
{
    if (new_size > _capacity)
    {
        _capacity *= kDefMultiplier;
        Type* tmp_data = reinterpret_cast<Type*>(::operator new(_capacity * sizeof(Type)));
        for (size_t idx = 0; idx < _size; ++idx)
            new(tmp_data[idx]) Type(_data[idx]);
        clear();
        _data = tmp_data;
    }

    _size = new_size;
}

template<class Type>
void Vector<Type>::clear()
{
    if (_capacity != 0)
    {
        for (size_t idx = 0; idx < _size; ++idx)
            _data[idx].~Type();

        ::operator delete[](_data);
        _size = _capacity = 0;
    }
}

