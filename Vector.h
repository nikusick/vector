#pragma once

#include <cstdio>

using Value = double;

class Vector
{
public:
    // All c-tors and "=" operators make vectors
    // where _capacity is equal to _size
    Vector() = default;
    Vector(const Value* rawArray, const size_t size, float coef = 2.0f);

    explicit Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    explicit Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    /*!
        \brief Add element to the end of vector

        Complexity is amort(O(1))

        \param value: value which must be added
    */
    void pushBack(const Value& value);

    /*!
        \brief Add element to the begin of vector

        \param value: value which must be added
    */
    void pushFront(const Value& value);

    /*!
        \brief Insert item(s) to vector at passed index
    */
    void insert(const Value& value, size_t pos);
    void insert(const Value* values, size_t size, size_t pos);
    void insert(const Vector& vector, size_t pos);

    /*!
        \brief Remove element from the end of vector

        Complexity is amort(O(1))
    */
    void popBack();

    /*!
        \brief Remove element from the begin of vector
    */
    void popFront();

    /*!
        \brief Remove item(s) from vector

        \param pos: position of removing begin
        \param count: count of elements which must be removed

        if (pos + count) > size then [pos, size) should be removed
    */
    void erase(size_t pos, size_t count = 1);

    /*!
        \brief Remove item(s) from vector

        \param beginPos: position of removing begin
        \param endPos: position of removing end

        All items in interval [beginPos, endPos) should be removed:
            [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]

        if endPos > size then [beginPos, size) should be removed
    */
    void eraseBetween(size_t beginPos, size_t endPos);

    /*!
        Returns size of vector
    */
    size_t size() const;

    /*!
        Returns capacity of vector
    */
    size_t capacity() const;

    /*!
        Returns load factor (size / capacity)
    */
    double loadFactor() const;

    /*!
        Access to item by index
    */
    Value& operator[](size_t idx);
    const Value& operator[](size_t idx) const;

    /*!
        Returns index of first
    */
    long long find(const Value& value) const;

    /*!
        Changes current capacity and allocate new memory if capacity > _capacity.
        Else do nothing
    */
    void reserve(size_t capacity);

    /*!
        Decreases _capacity to _size.
    */
    void shrinkToFit();

    class Iterator
    {
        Value* _ptr;
    public:
        explicit Iterator(Value * ptr);

        Value& operator*();

        const Value& operator*() const;

        Value* operator->();

        const Value* operator->() const;

        Iterator operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
private:
    Value* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float _multiplicativeCoef = 2.0f;
};
