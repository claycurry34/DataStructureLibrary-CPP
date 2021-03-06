#ifndef __ARRAYCLASS__H
#define __ARRAYCLASS__H
#include "AbstractArrayClass.h"
template<typename DT>
class ArrayClass : public virtual AbstractArrayClass<DT> {
protected:
	DT* paObject = nullptr;
	size_t _size = 0;
	void copy(const ArrayClass<DT>&);
public:
	ArrayClass();
	ArrayClass(size_t);
	ArrayClass(size_t, const DT&);
	ArrayClass(const ArrayClass<DT>&);
	ArrayClass(ArrayClass<DT>&&);
	virtual ~ArrayClass();
	virtual size_t size() const override;
	virtual DT& operator[] (size_t) const override;
	ArrayClass<DT>& operator= (const ArrayClass<DT>&);
	ArrayClass<DT>& operator= (ArrayClass<DT>&&);
};

const int ARRAY_CLASS_DEFAULT_SIZE = 1;

template<typename DT> void ArrayClass<DT>::copy(const ArrayClass<DT>& ac)
{
	paObject = new DT[ac._size];
	_size = ac._size;
	for (size_t i = 0; i < ac._size; i++)
	{
		paObject[i] = ac.paObject[i];
	}
};
template<typename DT> ArrayClass<DT>::ArrayClass() : ArrayClass(ARRAY_CLASS_DEFAULT_SIZE)
{
};
template<typename DT> ArrayClass<DT>::ArrayClass(size_t n) : paObject(new DT[n]), _size(n)
{
};
template<typename DT> ArrayClass<DT>::ArrayClass(size_t n, const DT& val) : paObject(new DT[n]), _size(n)
{
	for (size_t i = 0; i < n; i++)
		paObject[i] = val;	// non-STL types should use a copy constructor
};
template<typename DT> ArrayClass<DT>::ArrayClass(const ArrayClass<DT>& ac)
{
	if (&ac != this)
		copy(ac);
};
template<typename DT> ArrayClass<DT>::ArrayClass(ArrayClass<DT>&& ac)
{
	paObject = ac.paObject;
	ac.paObject = nullptr;
	_size = ac._size;
	ac._size = 0;
};
template<typename DT> ArrayClass<DT>::~ArrayClass()
{
	delete[] paObject; 
	paObject = nullptr;
	_size = 0;
};
template<typename DT> size_t ArrayClass<DT>::size() const 
{
	return _size;
};
template<typename DT> DT& ArrayClass<DT>::operator[] (size_t k) const
{
	if (k >= _size)
		throw ArrayBoundsException();
	return paObject[k];
};
template<typename DT> ArrayClass<DT>& ArrayClass<DT>::operator= (const ArrayClass<DT>& ac)
{
	if (this != &ac) {
		_size = 0;
		delete[] paObject;
		paObject = nullptr;
		copy(ac);
	}
	return *this;
};
template<typename DT> ArrayClass<DT>& ArrayClass<DT>::operator= (ArrayClass<DT>&& ac)
{
	paObject = ac.paObject;
	ac.paObject = nullptr;
	_size = ac._size;
	ac._size = 0;
	return *this;
}
#endif /* __ARRAYCLASS__H */
