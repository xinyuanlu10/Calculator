////////////////////////////////////////////////////////////////////////////
//2014.05.20 version by 钱彦良
//重载+,-,*,+=,-=,*=,%,%=等运算符，支持矩阵与单个数的运算
//矩阵大小不匹配会丢出异常，“Unmatched Matrix!”
//需要以这种形式: vector<vector< Type>> 传入值
////////////////////////////////////////////////////////////////////////////
#include <vector>
using namespace std;

template <class Type>
class Matrix{
public:
    typedef vector <vector <Type>> M_Type;
    typedef pair <int, int> PII;
    typedef Matrix <Type> Mat;
    M_Type t;

    Matrix(){};
    Matrix(const M_Type &a){ t=a; }

    PII size()const { return PII(t.size(),t[0].size()); }

    M_Type vec()const { return t; }

    Mat getM(int &row, int &col)const{
        Mat rst;
        vector <Type> ept(col);
        for (int i=0; i<row; i++) rst.t.push_back(ept);
        return rst;
    }

    bool operator ==(const Mat &a)const{
        if (t.size()!=a.t.size() || t[0].size()!=a.t[0].size()) return 0;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++)
                if (t[i][j]!=a.t[i][j]) return 0;
        return 1;
    }

    Mat operator +(const Mat &a)const{
        if (t.size()!=a.t.size() || t[0].size()!=a.t[0].size()) throw("Unmatched matrix!");
        Mat rst=*this;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++) rst.t[i][j]+=a.t[i][j];
        return rst;
    }
    Mat operator -(const Mat &a)const{
        if (t.size()!=a.t.size() || t[0].size()!=a.t[0].size()) throw("Unmatched matrix!");
        Mat rst=*this;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++) rst.t[i][j]-=a.t[i][j];
        return rst;
    }
    Mat operator *(const Mat &a)const{
        if (t[0].size()!=a.t.size()) throw("Unmatched matrix!");
        int row=t.size(), col=a.t[0].size();
        Mat rst=getM(row,col);
        for (int i=0; i<row; i++)
            for (int j=0; j<col; j++)
                for (int k=0; k<t[0].size(); k++)
                    rst.t[i][j]+=t[i][k]*a.t[k][j];
        return rst;
    }

    Mat operator +(const Type &a)const{
        Mat rst=*this;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++) rst.t[i][j]+=a;
        return rst;
    }

    Mat operator -(const Type &a)const{
        Mat rst=*this;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++) rst.t[i][j]-=a;
        return rst;
    }

    Mat operator *(const Type &a)const{
        Mat rst=*this;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++) rst.t[i][j]*=a;
        return rst;
    }

    Mat operator %(const Type &a)const{
        Mat rst=*this;
        for (int i=0; i<t.size(); i++)
            for (int j=0; j<t[0].size(); j++) rst.t[i][j]%=a;
        return rst;
    }

    Mat& operator +=(const Mat &a){ return *this=*this+a; }
    Mat& operator -=(const Mat &a){ return *this=*this-a; }
    Mat& operator *=(const Mat &a){ return *this=*this*a; }
    Mat& operator +=(const Type &a){ return *this=*this+a; }
    Mat& operator -=(const Type &a){ return *this=*this-a; }
    Mat& operator *=(const Type &a){ return *this=*this*a; }
    Mat& operator %=(const Type &a){ return *this=*this%a; }
};
