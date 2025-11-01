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
    if (sz > MAX_VECTOR_SIZE)
        throw length_error("Too large size for vector");
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
      //std::copy(v.pMem, v.pMem + sz, pMem);
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      if (pMem != nullptr)
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
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v)
          return *this;
      /*sz = 0;
      pMem = nullptr;*/
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept 
  {
      return sz; 
  }

  // индексация
  T& operator[](size_t ind)
  {
      if (pMem == nullptr) {
          throw length_error("pMem is deleted");
      }
      if (ind > sz) {
          throw out_of_range("Invalid index");
      }
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (pMem == nullptr) {
          throw length_error("pMem is deleted");
      }
      if (ind > sz) {
          throw out_of_range("Invalid index");
      }
      return pMem[ind];

  }
  bool isempt() {
      if (pMem == nullptr)
          return true;
      else
          return false;
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
  TDynamicVector delmem() {
      TDynamicVector res(*this);
      res.pMem = nullptr;
      return res;
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
      if (sz != v.sz)
          throw length_error("Разные длины векторов");
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] += v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw length_error("Разные длины векторов");
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] -= v.pMem[i];
      }
      return res;
  }
   T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
       T sum = 0;
       if (sz != v.sz) {
           throw length_error("Different lenght of vectors");
       }
       for (size_t i = 0; i < v.size(); i++) {
           sum += pMem[i] * v.pMem[i];
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
      if (s > MAX_MATRIX_SIZE)
          throw length_error("Too large matrix");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicMatrix<T>& m):  TDynamicVector<TDynamicVector<T>>(m.sz)
  {
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
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return true;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return true;
      }
      return false;
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
      /*if (v.sz != sz)
          throw length_error("Разные длины ветора и строки матрицы");
      TDynamicVector res(v.sz);
      T sum = 0;
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              sum += pMem[j][i] * v.pMem[j]
          }
          res[i] = sum;
          sum = 0;
      }*/
      return TDynamicVector::operator*(v);
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
      return res;
      //return TDynamicVector::operator+(m);
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




  /*TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw length_error("Разные длины ветора и строки матрицы");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
          res.pMem[i] = pMem[i] * m.pMem[i];
      }
      return res;
  }*/

  // ввод/вывод
  using TDynamicVector<TDynamicVector<T>>::size;

  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size(); i++) {
          istr >> v[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.size();i++) {
          ostr << v[i];
      }
      return ostr;
  }
};

#endif
