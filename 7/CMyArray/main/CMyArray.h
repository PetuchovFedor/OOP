#pragma once
#include <new>
#include <iostream>
#include <stdexcept>

template<typename T>
class CMyArray
{
	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		using MyType = IteratorBase< IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
		IteratorBase() = default;

		IteratorBase(const IteratorBase<false>& other)
			: m_ptr(other.m_ptr)
		{
		}

		IteratorBase(T* item)
			: m_ptr(item)
		{
		}

		T* getPtr() const
		{
			return m_ptr;
		}

		const T* getConstPtr()const
		{
			return m_ptr;
		}

		MyType& operator=(const MyType& iter)
		{
			m_ptr = iter.m_ptr;
			return *this;
		};

		MyType& operator=(MyType* ptr)
		{
			m_ptr = ptr->m_ptr;
			return (*this);
		}

		operator bool() const
		{
			if (m_ptr)
				return true;
			else
				return false;
		}

		bool operator==(const MyType& iter)const
		{
			return (m_ptr == iter.getConstPtr());
		}

		bool operator!=(const MyType& iter)const
		{
			return (m_ptr != iter.getConstPtr());
		}

		reference& operator*() const
		{
			return *m_ptr;
		}

		MyType& operator++()
		{
			++m_ptr;
			return (*this);
		}

		MyType& operator--()
		{
			--m_ptr;
			return (*this);
		}

		MyType operator++(int)
		{
			auto newPtr(*this);
			++m_ptr;
			return newPtr;
		}

		MyType operator--(int)
		{
			auto newPtr(*this);
			--m_ptr;
			return newPtr;

		}
		MyType& operator+=(difference_type offset)
		{
			m_ptr += offset;
			return *this;
		}

		MyType& operator-=(difference_type offset)
		{
			m_ptr -= offset;
			return *this;
		}
		MyType operator+(const difference_type& movement)
		{
			auto oldPtr = m_ptr;
			m_ptr += movement;
			auto newPtr(*this);
			m_ptr = oldPtr;
			return newPtr;
		}

		difference_type operator-(const MyType& iter)
		{
			return std::distance(iter.getPtr(), this->getPtr());
		}

		MyType operator-(const difference_type& movement)
		{
			auto oldPtr = m_ptr;
			m_ptr -= movement;
			auto newPtr(*this);
			m_ptr = oldPtr;
			return newPtr;
		}

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}
		

	private:
		T* m_ptr = nullptr;
	};

public:
	CMyArray() = default;
	CMyArray(CMyArray const& other)
	{
		if (other.GetSize() != 0)
		{
			T* newBegin = MemoryAlloc(other.GetSize());
			T* newEnd = newBegin;
			try
			{
				CopyElems(other.m_begin, other.m_end, newBegin, newEnd);
				m_begin = newBegin;
				m_end = newEnd;
				m_endOfCapacity = m_begin + other.GetSize();
			}
			catch (...)
			{
				DeleteElems(newBegin, newEnd);
				throw;
			}
		}
	}

	CMyArray(CMyArray&& other) noexcept
	{
		if (other.GetSize() != 0)
		{
			m_begin = other.m_begin;
			m_end = other.m_end;
			m_endOfCapacity = other.m_endOfCapacity;
			other.m_begin = nullptr;
			other.m_end = nullptr;
			other.m_endOfCapacity = nullptr;
		}
	}

	CMyArray& operator=(CMyArray const& other)
	{

		if (std::addressof(other) != this)
		{
			CMyArray tmpArr(other);
			//неопределенное поведенеи при разрушении tmpArr
			std::swap(m_begin, tmpArr.m_begin);
			std::swap(m_end, tmpArr.m_end);
			std::swap(m_endOfCapacity, tmpArr.m_endOfCapacity);
		}
		return *this;
	}
	//Выпиить
	//template <typename T1>
	//CMyArray<T>& operator=(CMyArray<T1> const& other)
	//{
	//	T* newBegin = MemoryAlloc(other.GetSize());
	//	//утечка памяти если Init  выьросит искл
	//	SetInitValues(newBegin, 0, other.GetSize());
	//	int countDeleteElem = 0;
	//	try
	//	{		
	//		// лучше size_t
	//		for (unsigned i = 0; i < other.GetSize(); ++i)
	//		{
	//			countDeleteElem++;
	//			newBegin[i] = static_cast<T>(other[i]);
	//		}
	//		if (m_endOfCapacity)
	//		{
	//			DeleteElems(m_begin, m_end);
	//		}
	//		m_begin = newBegin;
	//		m_end = m_begin + other.GetSize();
	//		m_endOfCapacity = m_end;
	//	}
	//	catch (...)
	//	{
	//		DeleteElems(newBegin, newBegin + countDeleteElem);
	//		throw;
	//	}

	//	return *this;
	//}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			//тоже что в копирующем
			//сразу с other
			/*CMyArray tmpArr(std::move(other));
			if (m_endOfCapacity)
			{
				DeleteElems(m_begin, m_end);
			}*/
			std::swap(m_begin, other.m_begin);
			std::swap(m_end, other.m_end);
			std::swap(m_endOfCapacity, other.m_endOfCapacity);
		}
		return *this;
	}

	~CMyArray()
	{
		DeleteElems(m_begin, m_end);
	}

	void PushBack(const T& value)
	{
		if (m_end == m_endOfCapacity)
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = MemoryAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyElems(m_begin, m_end, newBegin, newEnd);
				new (newEnd) T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteElems(newBegin, newEnd);
				throw;
			}
			DeleteElems(m_begin, m_end);
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	void Resize(size_t newSize)
	{
		if (GetSize() > newSize)
		{
			//SetInitValues(m_begin, GetSize(), newSize);
			DestroyElems(m_begin + newSize, m_end);
			m_end = m_begin + newSize;
		}
		else if (GetSize() < newSize)
		{
			size_t temporarySize = newSize;
			if (GetCapacity() < newSize)
			{
				T* newBegin = MemoryAlloc(newSize);
				T* newEnd = newBegin;
				try
				{
					CopyElems(m_begin, m_end, newBegin, newEnd);
					//Если выбросится исключение в init bvalue
					SetInitValues(newBegin, GetSize(), temporarySize);
					//SetInitValues(newEnd, newEnd + newSize);
					DeleteElems(m_begin, m_end);
					m_begin = newBegin;
					m_end = newBegin + newSize;
					m_endOfCapacity = m_begin + newSize;
				}
				catch (...)
				{
					if (temporarySize == newSize)
					{
						temporarySize = 0;
					}
					DeleteElems(newBegin, newEnd + temporarySize);
					throw;
				}
			}
			else
			{
				//тоже сaмое
				try
				{
					SetInitValues(m_begin, GetSize(), temporarySize);
					m_end = m_begin + temporarySize;
				}
				catch (...)
				{
					DestroyElems(m_begin + GetSize(), m_begin + GetSize() + temporarySize);
					throw;
				}
			}
		}
	}

	void Reserve(size_t newCapacity)
	{
		//если болше или равна
		if (GetCapacity() >= newCapacity)
			return;
		T* newBegin = MemoryAlloc(newCapacity);
		T* newEnd = newBegin;
		try
		{
			CopyElems(m_begin, m_end, newBegin, newEnd);
			DeleteElems(m_begin, m_end);
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		catch (...)
		{
			DeleteElems(newBegin, newEnd);
		}
	}

	void Clear()
	{
		DestroyElems(m_begin, m_end);
		m_end = m_begin;
	}

	const T& operator[](size_t index) const
	{
		if (index >= GetSize())
			throw std::out_of_range("Index out of array range");
		return *(m_begin + index);
	}

	T& operator[](size_t index)
	{
		if (index >= GetSize())
			throw std::out_of_range("Index out of array range");
		return *(m_begin + index);
	}

	bool IsEmpty() const
	{
		return m_begin == m_end;
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}
	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	iterator begin()
	{
		return iterator(m_begin);
	}

	iterator end()
	{
		return iterator(m_end);
	}

	const_iterator begin() const
	{
		return const_iterator(m_begin);
	}

	const_iterator end() const
	{
		return const_iterator(m_end);
	}

	const_iterator cbegin() const
	{
		return const_iterator(m_begin);
	}

	const_iterator cend() const
	{
		return const_iterator(m_end);
	}

	reverse_iterator rbegin() const
	{
		return reverse_iterator(m_end);
	}

	reverse_iterator rend() const
	{
		return reverse_iterator(m_begin);
	}

private:
	static void DeleteElems(T* begin, T* end)
	{
		DestroyElems(begin, end);
		MemoryDealloc(begin);
	}

	static void SetInitValues(T* begin, size_t fromSize, size_t& size)
	{
		//T* newBegin = end;
		/*for (end = begin; end != newEnd; ++end)
		{
			new (end) T();
		}*/
		size_t countDeleted = 0;
		for (size_t i = fromSize; i < size; i++)
		{
			try
			{
				countDeleted++;
				new (begin + i) T();
			}
			catch (...)
			{
				size = countDeleted;
				throw std::runtime_error("Error with initialization init values");
			}
		}
		size += 1;
	}


	static void CopyElems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyElems(T* from, T* to)
	{
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T* MemoryAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void MemoryDealloc(T* p)
	{
		free(p);
	}

private:
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};