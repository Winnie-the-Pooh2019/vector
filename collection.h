//
// Created by ivan on 2021-11-25.
//
#pragma once
#ifndef COMPLEXNUMBER_COLLECTION_H
#define COMPLEXNUMBER_COLLECTION_H

#include "iterable.h"

template<typename T>
class Collection : public Iterable<T> {
public:

    Collection() {}

    virtual bool add(T e) = 0;

    virtual bool add(Collection<T>& c) = 0;

    virtual void clear() = 0;

    virtual bool contains(T e) = 0;

    virtual bool contains(Collection<T>& c) = 0;

    virtual bool isEmpty() = 0;

    virtual bool remove(int index) = 0;

    virtual bool remove(T e) = 0;

    virtual bool remove(Collection<T>& c) = 0;

    virtual bool removeIf(bool predicate(T)) = 0;

    virtual Collection<T>& filter(bool predicate(T)) = 0;

    virtual int size() = 0;

    virtual T *toArray() = 0;

    virtual T& operator[](int index) = 0;
};

#endif //COMPLEXNUMBER_COLLECTION_H
