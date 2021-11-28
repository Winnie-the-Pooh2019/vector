//
// Created by ivan on 2021-11-25.
//
#pragma once
#ifndef COMPLEXNUMBER_COMPLEX_H
#define COMPLEXNUMBER_COMPLEX_H

#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double real;
    double imaginary;

    double nonSqrtLength() {
        return real * real + imaginary * imaginary;
    }
public:
    double length() {
        return sqrt((double) nonSqrtLength());
    }

    Complex() = default;

    Complex(const Complex& source) {
        this->imaginary = source.imaginary;
        this->real = source.real;
    }

    Complex& operator = (const Complex& source) {
        this->imaginary = source.imaginary;
        this->real = source.real;
    }

    Complex(double real, double imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }

    explicit Complex(double real) {
        this->real = real;
        this->imaginary = 0;
    }

    bool operator == (Complex& other) {
        return this->real == other.real && this->imaginary == other.imaginary;
    }

    bool operator != (Complex& other) {
        return !(*this == other);
    }

    bool operator > (Complex& other) {
        return this->nonSqrtLength() > other.nonSqrtLength();
    }

    bool operator >= (Complex& other) {
        return this->nonSqrtLength() >= other.nonSqrtLength();
    }

    bool operator < (Complex& other) {
        return this->nonSqrtLength() < other.nonSqrtLength();
    }

    bool operator <= (Complex& other) {
        return this->nonSqrtLength() <= other.nonSqrtLength();
    }

    Complex& operator - () {
        this->real = -real;
        this->imaginary = -imaginary;

        return *this;
    }

    friend Complex operator + (Complex& left, Complex& right) {
        Complex temp{};

        temp.real = left.real + right.real;
        temp.imaginary = left.imaginary + right.imaginary;

        return temp;
    }

    friend Complex operator - (Complex& left, Complex& right) {
        return left + (-right);
    }

    Complex& operator ++ () {
        this->real++;
        this->imaginary++;

        return *this;
    }

    Complex& operator ++ (int) {
        this->real++;
        this->imaginary++;

        return *this;
    }

    Complex& operator -- () {
        this->real--;
        this->imaginary--;

        return *this;
    }

    Complex& operator -- (int) {
        this->real--;
        this->imaginary--;

        return *this;
    }

    Complex& operator += (Complex& source) {
        this->real += source.real;
        this->imaginary += source.imaginary;

        return *this;
    }

    Complex& operator -= (Complex& source) {
        this->real -= source.real;
        this->imaginary -= source.imaginary;

        return *this;
    }

    friend Complex operator * (Complex& left, Complex& right) {
        Complex temp{};

        temp.real = (left.real * right.real) - (left.imaginary * right.imaginary);
        temp.imaginary = (left.real * right.imaginary) + (left.imaginary * right.real);

        return temp;
    }

    friend Complex operator * (double left, Complex& right) {
        Complex temp{};

        temp.real = left * right.real;
        temp.imaginary = left * right.imaginary;

        return temp;
    }

    friend Complex operator * (Complex& left, double right) {
        return right * left;
    }

    friend Complex operator / (Complex& left, Complex& right) {
        Complex temp{};

        temp.real = left.real * right.real + left.imaginary * right.imaginary;
        temp.imaginary = left.imaginary * right.real - left.real * right.imaginary;

        temp.real /= right.nonSqrtLength();
        temp.imaginary /= right.nonSqrtLength();

        return temp;
    }

    friend Complex operator / (Complex& left, double right) {
        return {left.real / right, left.imaginary / right};
    }

    friend Complex operator / (double left, Complex& right) {
        Complex ll(left, 0);

        return ll / right;
    }

    Complex& operator *= (Complex& source) {
        *this = (*this * source);
        return *this;
    }

    Complex& operator *= (double source) {
        *this = (*this * source);
        return *this;
    }

    Complex& operator /= (Complex& source) {
        *this = (*this / source);
        return *this;
    }

    Complex& operator /= (double source) {
        *this = (*this / source);
        return *this;
    }

    friend ostream& operator << (ostream &out, const Complex &source) {
        out << source.real << ((source.imaginary >= 0) ? "+" : "") << source.imaginary << "i";

        return out;
    }

    friend istream& operator >> (istream& in, Complex& source) {
        in >> source.real >> source.imaginary;

        return in;
    }
};


#endif //COMPLEXNUMBER_COMPLEX_H
