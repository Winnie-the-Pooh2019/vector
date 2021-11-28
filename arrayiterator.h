//
// Created by ivan on 2021-11-28.
//

#ifndef COMPLEXNUMBER_ARRAYITERATOR_H
#define COMPLEXNUMBER_ARRAYITERATOR_H

#include "iterable.h"

template<typename T>
class ArrayIterator : public Iterator<T> {
private:
    int counter = 0;

public:
    explicit ArrayIterator(ArrayList<T>& arrayList) : Iterator<T>(arrayList) {
        this->counter = 0;
    }

    ArrayIterator(const ArrayIterator<T>& source) : Iterator<T>(source) {
        this->counter = source.counter;
    }

    ArrayIterator<T>& operator = (const ArrayIterator<T>& source) {
        this->counter = source.counter;
        this->collection = source.collection;

        return *this;
    }

    bool operator == (ArrayIterator<T>& other) {
        return this->counter == other.counter && this->collection == other.collection;
    }

    bool operator != (ArrayIterator<T>& other) {
        return this->counter != other.counter || this->collection != other.collection;
    }

    void begin() {
        counter = 0;
    }

    void end() {
        counter = this->collection.size() - 1;
    }

    bool hasNext() override {
        return counter + 1 < this->collection.size();
    }

    bool hasPrevious() {
        return counter >= 0;
    }

    T next() override {
        counter++;
        return this->collection[counter];
    }

    T previous() {
        counter--;
        return this->collection[counter];
    }

    T get() override {
        return this->collection[counter];
    }

    void forEachRemaining(void consumer(T)) override {
        while (hasNext()) {
            consumer(next());
        }
    }
};

#endif //COMPLEXNUMBER_ARRAYITERATOR_H
