#pragma once

#include <cstring>
#include <iostream>
#include "malloc.h"

template <typename T>
struct vector {
public:
    T* values;
    int capacity;

    /*
    *   basic constructor for vector
    *   param CAPACITY is new capacity of created vector
    *   pointer to values will be made of allocated memory
    *   size of multiplication of CAPACITY and size of one T 
    */
    vector(int capacity) {
        this->capacity = capacity;
        values = (T*) malloc(capacity * sizeof(T));
    }

    /*
    *   CAPACITY makes 0 and pointer makes NULL
    */
    vector() {
        capacity = 0;
        values = nullptr;
    }

    /*
    *   copy-constructor
    *   makes CAPACITY same as the CAPACITY of ORIGINAL
    *   and copies data from ORIGINAL to VALUES
    */
    vector(const vector<T>& original) {
        this->capacity = original.capacity;

        values = (T*) malloc(sizeof(T) * original.capacity);
        memcpy(values, original.values, capacity * sizeof(T));
    }

    /*
    *   destructor
    *   frees memory
    */
    ~vector() {
        if (values != nullptr)
            free(values);
    }

    /*
    *   makes a vector from source ARRAY 
    *   sets CAPACITY from arg CAPACITY
    *   if there was data in VALUES, frees it
    */
    static vector<T> fromArray(T* array, int capacity) {
        if (capacity == 0)
            return {0};

        vector<double> result = {capacity};

        for (int i = 0; i < capacity; i++) {
            result.values[i] = array[i];
        }

        return result;
    }

    /*
    *   redefined appropriation operator
    *   frees memory with old data
    *   and copies new data from SOURCE
    */
    vector<T>& operator = (const vector<T>& source) {
        if (this == &source)
            return *this;

        capacity = source.capacity;

        if (values != nullptr)
            free(values);

        values = nullptr;

        if (capacity != 0) {
            values = (T*) malloc(sizeof(T) * source.capacity);
            memcpy(values, source.values, sizeof(T) * source.capacity);
        }

        return *this;
    }

    /*
    *   redefined appropriation-amount operator
    *   checks validity of input data:
    *       capacities of current vector and SOURCE should be the same and not-zero
    *       pointers to data should be not-null
    * 
    *   sums current data with data from SOURCE
    */
    vector<T>& operator += (const vector<T>& source) {
        if (capacity != source.capacity || source.values == nullptr || values == nullptr || capacity == 0)
            return *this;

        for (int i = 0; i < capacity; i++)
            values[i] = values[i] + source.values[i];

        return *this;
    }

    /*
    *   redefined appropriation-subtraction operator
    *   checks validity of input data:
    *       capacities of current vector and SOURCE should be the same and not-zero
    *       pointers to data should be not-null
    *   
    *   substracts current data and data from SOURCE
    */
    vector<T>& operator -= (const vector<T>& source) {
        if (capacity != source.capacity || source.values == nullptr || values == nullptr || capacity == 0)
            return *this;

        for (int i = 0; i < capacity; i++)
            values[i] = values[i] - source.values[i];

        return *this;
    }

    /*
    *   inserts one item to vector to PLACE with replacement
    */
    void insert(T newValue, int place) {
        values[place] = newValue;
    }

    /*
    *   inserts vector with new values to vector to PLACE with replacement
    */
    void insert(vector<T> newValues, int place) {
        for (int i = place; i < capacity; i++)
            values[i] = newValues.get(i - place);
    }

    /*
    *   adds new cell by RESIZE and inserts there new item
    */
    bool add(T newItem) {
        if (resize()) {
            values[capacity - 1] = newItem;

            return true;
        }

        return false;
    }

    /*
    *   adds new cells by RESIZE and inserts there new items from source vector
    */
    bool add(vector<T> newItems) {
        if (resize(newItems.capacity)) {
            insert(newItems, capacity - newItems.capacity);

            return true;
        }

        return false;
    }

    /*
    *   if there are no required cell, RESIZES current vector
    *   to necessary capacity and puts to cell
    *   with PLACE number an item
    */
    bool place(T newItem, int place) {
        if (place >= 0 && (place >= capacity) ? resize(place - capacity + 1) : true) {
            values[place] = newItem;

            return true;
        }
    
        return false;
    }

    /*
    *   if there are no required cells, RESIZES current vector
    *   to necessary capacity and puts data to cells
    *   with PLACE number an item
    */
    bool place(vector<T> newItems, int startPlace) {
        if (startPlace >= 0 && (startPlace + newItems.capacity >= capacity) ? 
        resize(startPlace + newItems.capacity - capacity) : true) {
            insert(newItems, startPlace);

            return true;
        }

        return false;
    }
    
    /*
    *   spreads vector from PLACE by RESIZE and SHIFTRIGHT
    *   and put to specified cell a value
    */
    bool put(T newItem, int place) {
        bool res = resize(), swi = shiftRight(place);
        if (res && swi) {
            values[place] = newItem;

            return true;
        }

        return false;
    }

    /*
    *   spreads vector from PLACE by RESIZE and SHIFTRIGHT
    *   and put to specified cells items
    */
    bool put(vector<T> items, int startPlace) {
        bool res = resize(items.capacity), swi = shiftRight(startPlace, items.capacity);

        if (res && swi) {
            for (int i = startPlace; i < startPlace + items.capacity; i++)
                values[i] = items.get(i - startPlace);

            return true;
        }

        return false;
    }

    /*
    *   returns a new vector including items from current vector
    *   placed on places from START to END inclusively
    */
    vector<T> getProjection(int start, int end) {
        if (start < 0 || end >= capacity)
            return {0};

        vector<T> result = {end - start + 1};

        for (int i = start; i <= end; i++)
            result.insert(values[i], i - start);

        return result;
    }

    /*
    *   returns a new vector including items from current vector
    *   placed on places from vector COORDS
    */
    vector<T> getProjection(vector<int> coords) {
        if (!isAllInSuchPlaces(coords))
            return {0};
        
        vector<T> result(coords.capacity);

        for (int i = 0; i < coords.capacity; i++)
            result.insert(values[coords.get(i)], i);

        return result;
    }

    /*
    *   I don't want to explain what it is
    *   I'm tired too much
    */
    [[deprecated("don't use it, please ._.")]]
    void makeProjection(vector<int> coords) {
        if (!isAllInSuchPlaces(coords))
            return;

        T* newPtr = (T*) malloc(coords.capacity * sizeof(T));

        for (int i = 0; i < coords.capacity; i++) {
            newPtr[i] = values[coords.get(i)];
        }

        free(values);
        values = newPtr;
        capacity = coords.capacity;
    }

    /*
    *   returns an item from cell number PLACE
    */
    T get(int place) {
        if (place < capacity && place >= 0)
            return values[place];
        else
            return values[0];
    }

    /*
    *   returns an item from cell number PLACE
    *   and free this cell by SHIFTLEFT and RESIZE
    */
    T pull(int place) {
        T val = values[place];

        if (shiftLeft(place))
            resize(-1);

        return val;
    }

    /*
    *   returns an item from last cell
    *   and free this cell by SHIFTLEFT and RESIZE
    */
    T pull() {
        T value = values[capacity - 1];

        if (shiftLeft(capacity - 1))
            resize(-1);

        return value;
    }

    /*
    *   deletes an item from cell number PLACE
    *   and free this cell by SHIFTLEFT and RESIZE
    *   returns bool if has worked successfully
    */
    bool del(int place) {
        if (shiftLeft(place))
            return resize(-1);
        else
            return false;
    }

    /*
    *   deletes an item from last cell number PLACE
    *   and free this cell by SHIFTLEFT and RESIZE
    *   returns bool if has worked successfully
    */
    bool delLast() {
        return resize(-1);
    }

    /*
    *   deletes an item from last cells from START to END inclusivly
    *   and free these cells by SHIFTLEFT and RESIZE
    *   returns bool if has worked successfully
    */
    bool delPart(int start, int end) {
        if (shiftLeft(start, end - start + 1)) {
            resize(-(end - start + 1));

            return true;
        } 
        else 
            return false;
    }

    /*
    *   deletes an item from last cells from vector COORDS
    *   and free these cells by SHIFTLEFT and RESIZE
    *   returns bool if has worked successfully
    */
    bool delPart(vector<int> coords) {
        if (!isAllInSuchPlaces(coords) || coords.capacity == 0)
            return false;

        for (int i = 0; i < coords.capacity; i++) {
            if (!shiftLeft(coords.get(i) - i))
                return false;
        }

        resize(-coords.capacity);

        return true;
    }

    /*
    *   deletes first element of vector with similar value
    */
    bool delByValue(T value) {
        return del(indexOf(value));
    }

    /*
    *   deletes all elements with similar value
    */
    bool delAllByValue(T value) {
        return delPart(indexesOfAll(value));
    }

    /*
    *   returns first index of such element
    */
    int indexOf(T value) {
        for (int i = 0; i < capacity; i++) {
            if (value == values[i])
                return i;
        }

        return -1;
    }

    /*
    *   collects all indexes of elements equaling VALUE
    */
    vector<int> indexesOfAll(T value) {
        vector<int> result = {};

        for (int i = 0; i < capacity; i++) {
            if (value == values[i])
                result.add(i);
        }

        return result;
    }

    /*
    *   collects last index of element equaling VALUE
    */
    int lastIndexOf(T value) {
        int place;

        for (int i = 0; i < capacity; i++) {
            if (value == values[i])
                place = i;
        }

        return place;
    }

    /*
    *   returns TRUE if cell number PLACE exists
    */
    bool isInPlace(int place) {
        return (place >= 0 && place < capacity) ? true : false;
    }

    /*
    *   returns TRUE if cells numbered in vector COORDS exist
    */
    bool isAllInSuchPlaces(vector<int> coords) {
        for (int i = 0; i < coords.capacity; i++) {
            if (!isInPlace(coords.get(i))) {
                return false;
            }
        }

        return true;
    }

    /*
    *   returns TRUE if such element exists
    */
    bool isIn(T value) {
        for (int i = 0; i < capacity; i++) {
            if (values[i] == value)
                return true;
        }

        return false;
    }

    /*
    *   returns TRUE if such elements exist
    */
    bool isAllIn(vector<T> neededValues) {
        bool oneItemIn = false;

        for (int i = 0; i < neededValues.capacity; i++) {
            for (int j = 0; j < capacity; j++) {
                if (values[j] == neededValues.get(i))
                    oneItemIn = true;
            }

            if (!oneItemIn) return false;
        }

        return true;
    }

    /*
    *   returns max element in current vector
    *   don't use with incomparable types
    */
    T findMax() {
        T max = values[0];

        for (int i = 1; i < capacity; i++) {
            if (max > values[i]) {
                max = values[i];
            }
        }

        return max;
    }

    /*
    *   returns min element in current vector
    *   don't use with incomparable types
    */
    T findMin() {
        T min = values[0];

        for (int i = 1; i < capacity; i++) {
            if (min < values[i]) {
                min = values[i];
            }
        }

        return min;
    }

    /*
    *   sorts vector by increase order or decrease one by BYINCREASING
    *   don't use with incomparable types
    */
    void sort(bool byIncreasing) {
        for (int i = 0; i < capacity; i++) {
            for (int j = i; j < capacity; j++) {
                if (byIncreasing ? (values[i] > values[j]) : (values[i] < values[j])) {
                    T c = values[j];
                    values[j] = values[i];
                    values[i] = c;
                }
            }
        }
    }

private:

    /*
    *   resizes current vector to DELTA
    *   checks if new capaity is lower than zero
    *   after copies data from old vector
    *   frees memory and changes CAPACITY
    *   returns TRUE if work was successful 
    */
    bool resize(int delta = 1) {
        if (delta == 0 || delta + capacity <= 0)
            return false;

        T* newPtr = (T*) malloc((delta + capacity) * sizeof(T));
        for (int i = 0; i < (delta > 0 ? capacity : delta + capacity); i++)
            newPtr[i] = values[i];

        free(values);
        values = newPtr;
        capacity += delta;

        return true;
    }

    /*
    *   I don't know if this works
    */
    [[deprecated("I don't recomend to use this ;)")]]
    bool swich(int place, int delta = 1) {
        if (!(place + 2 * delta - 1 < capacity) || !(place + 2 * delta + 1 > -1) || delta == 0)
            return false;

        if (delta > 0)
            for (int i = 0; i < delta; i++)
                values[i + place + delta] = values[i + place];
        else
            for (int i = 0; delta > i; i--)
                values[i + place + delta] = values[i + place];

        return true;
    }

    /*
    *   shifts items from PLACE from right side to DELTA
    *   returns TRUE if PLACE is in boarders of current vector
    */
    bool shiftRight(int place, int delta = 1) {
        if (place >= capacity || place < 0)
            return false;

        for (int i = capacity - delta - 1; i >= place; i--)
            values[delta + i] = values[i];

        return true;
    }

    /*
    *   shifts items from PLACE from left side to DELTA
    *   returns TRUE if PLACE is in boarders of current vector
    */
    bool shiftLeft(int place, int delta = 1) {
        if (place >= capacity || place < 0)
            return false;

        for (int i = place + delta; i < capacity; i++)
            values[i - delta] = values[i];

        return true;
    }
};

/*
*   redefined sum operator
*   checks if CAPACITY of both args are the same
*   returns new vector including sums of each elements of args
*/
template<typename T>
vector<T> operator + (vector<T>& l, vector<T>& r) {
    vector<T> result;

    if (l.capacity != r.capacity)
        return result;

    result = {l.capacity};
    for (int i = 0; i < l.capacity; i++)
        result.insert(l.get(i) + r.get(i), i);

    return result;
}

/*
*   redefined substraction operator
*   checks if CAPACITY of both args are the same
*   returns new vector including substractions of each elements of args
*/
template<typename T>
vector<T> operator - (vector<T>& l, vector<T>& r) {
    vector<T> result;

    if (l.capacity != r.capacity)
        return result;

    result = {l.capacity};
    for (int i = 0; i < l.capacity; i++)
        result.insert(l.get(i) - r.get(i), i);

    return result;
}

/*
*   defines scalar product
*   checks if CAPACITY of both args are the same
*   returns a scalar product of vector
*   don't use with non-numeric T param
*/
template<typename T>
double operator * (vector<T>& l, vector<T>& r) {
    double result = 0;

    if (l.capacity != r.capacity)
        return result;

    for (int i = 0; i < l.capacity; i++)
        result += l.get(i) * r.get(i);

    return result;
}

/*
*   defines an equality operator
*   returns TRUE if CAPACITY if both args are the same
*   and related elements are equal 
*/
template<typename T>
bool operator == (vector<T>& l, vector<T>& r) {
    if (l.capacity != r.capacity)
        return false;

    for (int i = 0; i < l.capacity; i++) {
        if (l.get(i) != r.get(i)) {
            return false;
        }
    }

    return true;
}

/*
*   defines an non-equality operator
*   returns TRUE if CAPACITY if both args are not the same
*   or related elements are not equal 
*/
template<typename T>
bool operator != (vector<T>& l, vector<T>& r) {
    if (l.capacity != r.capacity)
        return true;

    for (int i = 0; i < l.capacity; i++) {
        if (l.get(i) != r.get(i))
            return true;
    }

    return false;
}