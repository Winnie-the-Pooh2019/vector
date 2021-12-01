//
// Created by ivan on 2021-11-25.
//
#pragma once
#ifndef COMPLEXNUMBER_ITERATOR_H
#define COMPLEXNUMBER_ITERABLE_H

#include <cstring>

template<typename T>
class Collection;

template<typename T>
class Iterator {
protected:
    Collection<T>& collection;

public:
    virtual bool hasNext() = 0;

    virtual T next() = 0;

    virtual T get() = 0;

    virtual void forEachRemaining(void consumer(T)) = 0;

    Iterator(Collection<T> &collection) : collection(collection) {}

    Iterator() {}
};

template<typename T>
class Iterable {
public:

    virtual Iterator<T>& iterator() = 0;

    virtual void forEach(void consumer(T&)) = 0;

    virtual string toString() = 0;
};



#endif //COMPLEXNUMBER_ITERATOR_H
