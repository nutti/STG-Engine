#include "Compiler.h"

int main( int argc, char** argv )
{
	for( int i = 1; i < argc; ++i ){
		Compiler compiler;
		VM::Data data;
		compiler.Compile( argv[ i ], data );
		std::string str = argv[ i ];
		str += ".bin";
		char s[ 4 ];
		std::fstream fOut( str.c_str(), std::ios::binary | std::ios::out );
		MAPIL::TransformInt32IntoChar( data.m_CommandSize, s, MAPIL::BYTE_ORDER_LITTLE );
		fOut.write( s, sizeof( s ) );
		fOut.write( reinterpret_cast < char* > ( data.m_Command ), sizeof( char ) * data.m_CommandSize );
		MAPIL::TransformInt32IntoChar( data.m_EntryPoint, s, MAPIL::BYTE_ORDER_LITTLE );
		fOut.write( s, sizeof( s ) );
		MAPIL::TransformInt32IntoChar( data.m_TextSize, s, MAPIL::BYTE_ORDER_LITTLE );
		fOut.write( s, sizeof( s ) );
		fOut.write( data.m_TextBuffer, sizeof( char ) * data.m_TextSize );
		MAPIL::TransformInt32IntoChar( data.m_ValueSize, s, MAPIL::BYTE_ORDER_LITTLE );
		fOut.write( s, sizeof( s ) );
		fOut.close();
	}

	return 0;
}