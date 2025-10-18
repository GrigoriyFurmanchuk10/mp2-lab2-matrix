// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector<T>& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      if (!pMem)
          delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (*this == v)
          return *this;
      if (pMem)
          delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (*this == v)
          return *this;
      if (pMem)
          delete[] pMem;
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }

  size_t size() const noexcept 
  {
      return sz; 
  }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];

  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Индекс за границей");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return true;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return true;
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] += val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] -= val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] *= val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.zs)
          trow length_error("Разные длины векторов");
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          rex.pMem[i] += v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.zs)
          trow length_error("Разные длины векторов");
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          rex.pMem[i] -= v.pMem[i];
      }
      return res;
  }
   T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
       T sum = 0;
       for (size_t = 0; i < res.size(); i++) {
           sum = pMem[i] * v.pMem[i];
       }
       return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicMatrix& m) :sz(m.sz)
  {
      pMem = new T[m.sz];
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(m.pMem[i]);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          pMem[i] *= val;
      }
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.sz != sz)
          throw length_error("Разные длины ветора и строки матрицы");
      TDynamicVector res(v.sz);
      T sum = 0;
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              sum += pMem[j][i] * v.pMem[j]
          }
          res[i] = sum;
          sum = 0;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("Разные длины ветора и строки матрицы");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + m.pMem[i];
      }
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("Разные длины ветора и строки матрицы");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("Разные длины ветора и строки матрицы");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem * m.pMem[i];
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < sz; i++) {
          ostr << v.pMem[i];
      }
      return ostr;
  }
};

#endif
