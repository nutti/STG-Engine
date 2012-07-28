#ifndef INCLUDED_VM_VALUE_H
#define INCLUDED_VM_VALUE_H

#include <iostream>
#include <exception>
#include <string>

namespace VM
{

	// String class with reference counter.
	class string
	{
	public:
		int				m_Ref;
		std::string		m_Str;
	public:
		string() : m_Ref( 0 )
		{
		}
		string( const std::string& str ) : m_Ref( 1 ), m_Str( str )
		{
		}
		void AddRef()
		{
			++m_Ref;
		}
		void Release()
		{
			if( --m_Ref == 0 ){
				delete this;
			}
		}
	};

	class Value
	{
		enum
		{
			TYPE_INTEGER,
			TYPE_STRING,
		};
	public:
		union
		{
			string*		m_pString;
			int			m_Integer;
		};
		char	m_Type;
	public:
		Value()
		{
			m_pString = 0;
			m_Type = TYPE_INTEGER;
		}
		Value( int iVal )
		{
			m_Integer = iVal;
			m_Type = TYPE_INTEGER;
		}
		Value( const std::string& str )
		{
			m_pString = new string( str );
			m_Type = TYPE_STRING;
		}
		Value( string* p )
		{
			m_pString = p;
			m_Type = TYPE_STRING;
		}
		~Value()
		{
			Clear();
		}
		Value( const Value& v )
		{
			Copy( v );
		}
		Value& operator=( const Value& v )
		{
			if( this == &v ){
				return *this;
			}
			Clear();
			Copy( v );
			return *this;
		}
		void Clear()
		{
			if( m_Type == TYPE_STRING ){
				m_pString->Release();
			}
		}
		void Copy( const Value& v )
		{
			m_Type = v.m_Type;
			m_pString = v.m_pString;
			if( m_Type == TYPE_STRING ){
				m_pString->AddRef();
			}
		}
	};

	class StackOverflow : public std::exception
	{
	public:
		const char* what() const throw()
		{
			return "Stack Overflow!!";
		}
	};

	template < typename T, int SIZE >
	class Stack
	{
	protected:
		char		m_Data[ SIZE ][ sizeof( T ) ];
		int			m_Size;
	public:
		Stack() : m_Size( 0 )
		{
		}
		~Stack()
		{
			Resize( 0 );
		}
		void Push( const T& v )
		{
			if( SIZE <= m_Size ){
				throw StackOverflow();		// Stack overflow.
			}
			*( ::new( m_Data[ m_Size++ ]) T ) = v;
		}
		void Pop()
		{
			( (T*)m_Data[ --m_Size ] )->~T();
		}
		void Pop( int count )
		{
			Resize( m_Size - count );
		}
		void Resize( int newSize )
		{
			int oldSize = m_Size;
			if( oldSize > newSize ){
				for( int i = newSize; i < oldSize; ++i ){
					( (T*)m_Data[ i ] )->~T();
				}
			}
			if( oldSize < newSize ){
				if( SIZE < newSize ){
					throw StackOverflow();
				}
				for( int i = oldSize; i < newSize; ++i ){
					::new( m_Data[ i ] ) T;
				}
			}
			m_Size = newSize;
		}
		const T& Top() const { return *( const T* ) m_Data[ m_Size - 1 ]; }
		T& Top() { return *( T* )m_Data[ m_Size - 1 ]; }
		bool Overflow() const { return m_Size >= SIZE; }
		bool Empty() const { return m_Size == 0; }
		int Size() const { return m_Size; }
		const T& operator[]( int index ) const { return *( const T* ) m_Data[ index ]; }
		T& operator[]( int index ) { return *( T* ) m_Data[ index ]; }
	};

}



#endif
