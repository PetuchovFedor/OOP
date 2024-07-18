#pragma once
#include <string>

class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из 
// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания 
	CMyString(CMyString&& other);

	// конструктор, инициализирующий строку данными из 
// строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength()const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая 
	const char* GetStringData()const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	CMyString& operator =(CMyString const& other);

	CMyString& operator=(CMyString&& other);

	CMyString operator +(CMyString const& other) const;

	CMyString& operator+=(CMyString const& other);

	bool operator==(const CMyString& other) const;

	bool operator!=(const CMyString& other) const;

	bool operator<(const CMyString & other) const;

	bool operator>(const CMyString& other) const;

	bool operator<=(const CMyString& other) const;

	bool operator>=(const CMyString& other) const;

	const char& operator[](size_t index) const;

	char& operator[](size_t index);

private:

	char* m_str;
	size_t m_size = 0;
};

const CMyString operator+(std::string const& stlString, CMyString const& myString);

const CMyString operator+(const char* charString, CMyString const& myString);

std::istream& operator>>(std::istream& input, CMyString& myString);

std::ostream& operator<<(std::ostream& output, CMyString const& myString);
