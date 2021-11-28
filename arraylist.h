//
// Created by ivan on 2021-11-25.
//
#pragma once
#ifndef COMPLEXNUMBER_ARRAYLIST_H
#define COMPLEXNUMBER_ARRAYLIST_H

#define BUCKET_SIZE 16

#include "collection.h"
#include "iterable.h"

template<typename T>
class ArrayIterator;

template<typename T>
class ArrayList : public Collection<T> {
protected:
    T* values;
    int capacity{};
    int amount{};

public:
    ArrayList() : Collection<T>() {
        this->capacity = BUCKET_SIZE;
        this->amount = 0;
        this->values = new T[capacity];
    }

    explicit ArrayList(int startSize) {
        this->amount = startSize;
        this->capacity = (BUCKET_SIZE) * (startSize / BUCKET_SIZE + 1);

        this->values = new T[capacity];
    }

    ArrayList(T* source, int size) : Collection<T>() {
        this->amount = size;
        this->capacity = (BUCKET_SIZE) * (size / BUCKET_SIZE + 1);

        this->values = new T[capacity];

        for (int i = 0; i < size; i++) {
            this->values[i] = source[i];
        }
    }

    explicit ArrayList(Collection<T>& source) : Collection<T>() {
        this->amount = source.size();
        this->capacity = (BUCKET_SIZE) * (source.size() / BUCKET_SIZE + 1);

        this->values = new T[capacity];

        Iterator<T>& iterator = source.iterator();

        int i = 0;
        do {
            values[i] = iterator.get();

            iterator.next();
            i++;
        } while (iterator.hasNext());
        values[i] = iterator.get();
    }

    ArrayList(const ArrayList<T>& source) : Collection<T>() {
        this->values = new T[source.capacity];
        this->amount = source.amount;
        this->capacity = source.capacity;

        for (int i = 0; i < amount; i++) {
            this->values[i] = source.values[i];
        }
    }

    virtual ~ArrayList() {
        delete[] values;
    }

    ArrayList<T>& operator = (const ArrayList<T>& source) {
        if (this == &source)
            return *this;

        this->amount = source.amount;
        this->capacity = source.capacity;
        this->values = new T[capacity];

        for (int i = 0; i < amount; i++) {
            values[i] = source.values[i];
        }

        return *this;
    }

    bool operator == (ArrayList<T>& other) {
        if (amount != other.amount || capacity != other.capacity)
            return false;

        for (int i = 0; i < amount; i++) {
            if (values[i] != other.values[i])
                return false;
        }

        return true;
    }

    bool operator != (ArrayList<T>& other) {
        return !(*this == other);
    }

    Iterator<T>& iterator() override {
        ArrayIterator<T>* it = new ArrayIterator<T>(*this);
        return *it;
    }

    bool add(T e) override {
        if (capacity <= amount) {
            if (!resize())
                return false;

            values[amount - 1] = e;
        } else {
            values[amount] = e;
            amount++;
        }

        return true;
    }

    virtual bool add(T e, int index) {
        if (capacity <= amount) {
            if (!resize())
                return false;
        }

        if (!shift(index, 1))
            return false;

        amount++;
        values[index] = e;

        return true;
    }

    bool add(Collection<T>& c) override {
        int i = 0;
        for (; i < c.size(); i++) {
            if (!add(c[i]))
                return false;
        }

        return true;
    }

    void clear() override {
        amount = 0;
        capacity = BUCKET_SIZE;

        delete values;
        values = new T[capacity];
    }

    bool contains(T e) override {
        return indexOf(e) != -1;
    }

    bool contains(Collection<T>& c) override {
        for (int i = 0; i < c.size(); i++) {
            if (!contains(c[i]))
                return false;
        }

        return true;
    }

    virtual int indexOf(T e) {
        for (int i = 0; i < amount; i++)
            if (values[i] == e)
                return i;

        return -1;
    }

    virtual int lastIndexOf(T e) {
        for (int i = amount - 1; i >= 0; i--)
            if (values[i] == e)
                return i;

        return -1;
    }

    bool isEmpty() override {
        return amount == 0;
    }

    bool remove(int index) override {
        if (index >= amount || index < 0)
            return false;

        return shift(index, -1);
    }

    bool remove(T e) override {
        int index = indexOf(e);

        return remove(index);
    }

    bool remove(Collection<T>& c) override {
        for (int i = 0; i < c.size(); i++) {
            if (!remove(c[i]))
                return false;
        }

        return true;
    }

    bool removeIf(bool predicate(T)) override {
        for (int i = 0; i < amount; i++) {
            if (predicate(values[i])) {
                if (!remove(i))
                    return false;
            }
        }

        return true;
    }

    virtual bool removeRange(int begin, int end) {
        if (begin < 0 || begin > end || end >= amount)
            return false;

        return shift(begin, -(end - begin + 1));
    }

    T* toArray() override {
        T* array = new T[size()];

        for (int i = 0; i < size(); i++) {
            array[i] = values[i];
        }

        return array;
    }

    int size() override{
        return amount;
    }

    virtual ArrayList<T> subList(int begin, int end) {
        if (begin < 0 || begin > end || end >= amount)
            return ArrayList<T>();

        T* newValues = new T[end - begin + 1];

        for (int i = begin; i <= end; i++) {
            newValues[i - begin] = values[i];
        }

        return ArrayList<T>(newValues, end - begin + 1);
    }

    virtual bool set(int index, T e) {
        if (index >= amount || index < 0)
            return false;

        values[index] = e;

        return true;
    }

    T& operator [] (int index) override {
        return values[index];
    }

    void forEach(void consumer(T&)) {
        for (int i = 0; i < amount; i++) {
            consumer(values[i]);
        }
    }

    Collection<T>& filter(bool predicate(T)) override {
        ArrayList<T>* newArray = new ArrayList<T>();

        for (int i = 0; i < amount; i++) {
            if (predicate(values[i]))
                newArray->add(values[i]);
        }

        return *newArray;
    }

private:

    bool resize(int bucketCount = 1) {
        if (capacity + BUCKET_SIZE * bucketCount < 1)
            return false;

        capacity += BUCKET_SIZE * bucketCount;

        amount = ((bucketCount >= 0) ? amount : capacity);

        T* newValues = new T[capacity];

        for (int i = 0; i < amount; i++)
            newValues[i] = values[i];

        delete[] values;
        values = newValues;

        return true;
    }

    bool shift(int place, int delta = 1) {
        if (delta + amount <= 0)
            return false;

        if (delta + amount > capacity)
            resize();
        else
            amount += delta;

        if (delta >= 0) {
            for (int i = amount - delta - 1; i >= place; i--)
                values[delta + i] = values[i];
        } else {
            for (int i = place; i < amount; i++)
                values[i] = values[i - delta];
        }

        return true;
    }
};

#endif //COMPLEXNUMBER_ARRAYLIST_H
