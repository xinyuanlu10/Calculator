#include <cstdio>
#include <iostream>
#include <vector>
#include "BigInt.h"
using namespace std;
using namespace rel_ops;

typedef pair <BigInt, BigInt> PII;

class Fraction{
private:
    BigInt gcd(const BigInt &u, const BigInt &v)const{        
        if (v==0) return u;
        else return gcd(v,u%v);
    }

public:
    BigInt a,b;
    Fraction(){ a=0, b=1; }
    Fraction(const BigInt &t){ a=t, b=1; }
    Fraction(const PII &t){
        BigInt tmp=gcd(abs(t.first), abs(t.second));
        a=t.first/tmp;
        b=t.second/tmp;
    }
    Fraction operator +(const Fraction &t)const{
        return PII(a*t.b+t.a*b,b*t.b);
    }
    Fraction operator -(const Fraction &t)const{
        return PII(a*t.b-t.a*b,b*t.b);
    }
    Fraction operator *(const Fraction &t)const{
        return PII(a*t.a,b*t.b);
    }
    Fraction operator /(const Fraction &t)const{
        if (t.a==0) throw("Div Zero");
        return PII(a*t.b,b*t.a);
    }

    Fraction operator +=(const Fraction &t){
        return *this=*this+t;
    }
    Fraction operator -=(const Fraction &t){
        return *this=*this-t;
    }
    Fraction operator *=(const Fraction &t){
        return *this=*this*t;
    }
    Fraction operator /=(const Fraction &t){
        return *this=*this/t;
    }

    bool operator <(const Fraction &t) const{
        Fraction tmp=*this-t;
        if (tmp.a<0) return 1; else return 0;
    }
    bool operator ==(const Fraction &t) const{
        Fraction tmp=*this-t;
        if (tmp.a==0) return 1; else return 0;
    }
};