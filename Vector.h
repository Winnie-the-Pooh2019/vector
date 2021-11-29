//
// Created by ivan on 2021-11-28.
//

#ifndef COMPLEXNUMBER_VECTOR_H
#define COMPLEXNUMBER_VECTOR_H

#include "arraylist.h"
#include "arrayiterator.h"
#include "complex.h"
#include "cmath"

template<typename T>
class Vector : public ArrayList<T> {
public:
    Vector() : ArrayList<T>() {}

    Vector(T* source, int size) : ArrayList<T>(source, size) {}

    explicit Vector(int startSize) {
        this->amount = startSize;
        this->capacity = (BUCKET_SIZE) * (startSize / BUCKET_SIZE + 1);

        this->values = new T[this->capacity];
    }

    explicit Vector(Collection<T>& source) : ArrayList<T>(source) {}

    Vector(const Vector<T>& source) : ArrayList<T>() {}

    Vector<T>& operator = (const Vector<T>& source) {
        if (this == &source)
            return *this;

        this->amount = source.amount;
        this->capacity = source.capacity;
        this->values = new T[this->capacity];

        for (int i = 0; i < this->amount; i++) {
            this->values[i] = source.values[i];
        }

        return *this;
    }

    double length() {
        double result = 0;

        for (int i = 0; i < this->amount; i++) {
            result += (*this)[i] * (*this)[i];
        }

        return sqrt(result);
    }

    bool operator == (Vector<T>& other) {
        if (this == &other)
            return true;

        if (this->amount != other.amount || this->capacity != other.capacity)
            return false;

        for (int i = 0; i < this->amount; i++) {
            if (this->values[i] != other.values[i])
                return false;
        }

        return true;
    }

    bool operator != (Vector<T>& other) {
        return !(*this == other);
    }

    bool operator > (Vector<T>& other) {
        for (int i = 0; i < this->amount; i++) {
            if ((*this)[i] <= other[i])
                return false;
        }

        return true;
    }

    bool operator >= (Vector<T>& other) {
        for (int i = 0; i < this->amount; i++) {
            if ((*this)[i] < other[i])
                return false;
        }

        return true;
    }

    bool operator < (Vector<T>& other) {
        for (int i = 0; i < this->amount; i++) {
            if ((*this)[i] >= other[i])
                return false;
        }

        return true;
    }

    bool operator <= (Vector<T>& other) {
        for (int i = 0; i < this->amount; i++) {
            if ((*this)[i] > other[i])
                return false;
        }

        return true;
    }

    Vector<T>& operator - () {
        for (int i = 0; i < this->amount; i++) {
            (*this)[i] = -((*this)[i]);
        }

        return *this;
    }

    friend Vector<T> operator + (Vector<T>& left, Vector<T>& right) {
        Vector<T> temp;

        cout << "la = " << left.amount << " ra = " << right.amount << endl;

        if (left.amount != right.amount)
            return temp;

        temp = Vector<T>(left.amount);

        for (int i = 0; i < left.amount; i++)
            temp[i] = left[i] + right[i];

        return temp;
    }

    friend Vector<T> operator - (Vector<T>& left, Vector<T>& right) {
        return left + (-right);
    }

    friend T operator * (Vector<T>& left, Vector<T>& right) {
        T result = 0;

        if (left.amount != right.amount)
            return 0;

        for (int i = 0; i < left.amount; i++)
            result += left[i] * right[i];

        return result;
    }
};

template<> double Vector<Complex>::length() {
    return this->size();
}

#endif //COMPLEXNUMBER_VECTOR_H
