#include <cstdio>
#include "Vector.h"
#include <algorithm>
#include <cmath>
#include <ostream>

using namespace std;
Vector::Vector(const Value *rawArray, const size_t size, float coef) {
    _size = size;
    _capacity = size * (size_t) coef;
    _data = new Value[_capacity];
    for (size_t i = 0; i < size; ++i) {
        _data[i] = rawArray[i];
    }
    _multiplicativeCoef = coef;
}

Vector::Vector(const Vector &other) {
    _data = new Value[other._capacity];
    for (size_t i = 0; i < other._size; ++i) {
        _data[i] = other._data[i];
    }
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
}

Vector &Vector::operator=(const Vector &other) {
    reserve(other._capacity);
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    for (int i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
    return *this;
}

Vector::Vector(Vector &&other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 0;
}

Vector &Vector::operator=(Vector &&other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 0;
    return *this;
}

Vector::~Vector() {
    delete[] _data;
}

void Vector::pushBack(const Value &value) {
    if (loadFactor() == 1) {
        reserve(_capacity * (size_t)_multiplicativeCoef);
    }
    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const Value &value) {
    if (loadFactor() == 1) {
        reserve(_capacity * (size_t)_multiplicativeCoef);
    }
    for (size_t i = _size; i > 0; --i) {
        _data[i] = _data[i - 1];
    }
    _data[0] = value;
    _size++;
}

void Vector::insert(const Value &value, size_t pos) {
    if (loadFactor() == 1) {
        reserve(_capacity * (size_t)_multiplicativeCoef);
    }
    for (size_t i = _size; i >= pos + 1; --i) {
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    _size++;
}

void Vector::insert(const Value *values, size_t size, size_t pos) {
    _size += size;
    while (loadFactor() >= 1) {
        reserve(_capacity * (size_t)_multiplicativeCoef);
    }
    for (size_t i = _size; i >= pos + size; --i) {
        _data[i] = _data[i - size];
    }
    for (size_t i = 0; i < size; ++i) {
        _data[i + pos] = values[i];
    }
}

void Vector::insert(const Vector &vector, size_t pos) {
    insert(vector._data, vector._size, pos);
}

void Vector::popBack() {
    if (_size == 0) {
        return;
    }
    _size--;
    _data[_size].~Value();
}

void Vector::popFront() {
    if (_size == 0) {
        return;
    }
    for (size_t i = 0; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
    }
    popBack();
}

void Vector::erase(size_t pos, size_t count) {
    for (size_t i = pos; i < max(pos + count, _size); ++i) {
        _data[i] = _data[i + count];
    }
    size_t size = _size;
    for (size_t i = 0; i < min((int)count, abs((int)size - (int)pos)); ++i) {
        popBack();
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}

double Vector::loadFactor() const {
    return _size / _capacity;
}

Value &Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value &Vector::operator[](size_t idx) const {
    return _data[idx];
}

long long Vector::find(const Value &value) const {
    for (int i = 0; i < _size; ++i){
        if (_data[i] == value){
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        Value *v1 = new Value[capacity];
        for (int i = 0; i < _size; i++)
            v1[i] = _data[i];
        _data = new Value[capacity];
        for (int i = 0; i < _size; i++)
            _data[i] = v1[i];
        delete[] v1;
        _capacity = capacity;
    }
}

void Vector::shrinkToFit() {
    Value *v = new Value[_size];
    for (size_t i = 0; i < _size; ++i) {
        v[i] = _data[i];
    }
    _data = new Value[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = v[i];
    }
    _capacity = _size;
    delete[] v;
}

ostream &operator<<(ostream &out, const Vector &v) {
    out << "Size: " << v._size << endl;
    out << "Capacity: " << v._capacity << endl;
    out << "Vector: ";
    for (size_t i = 0; i < v._size; ++i) {
        out << v._data[i] << " ";
    }
    return out;
}
