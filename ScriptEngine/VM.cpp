#include <exception>
#include "VM.h"

void VM::VCPU::Init()
{
	m_pCommand = m_pData->m_Command;
	m_pTextBuffer = m_pData->m_TextBuffer;
	m_CommandSize = m_pData->m_CommandSize;
	m_TextSize = m_pData->m_TextSize;

	m_GlobalValue.resize( m_pData->m_ValueSize );
	m_pCommandPtr = m_pCommand + m_pData->m_EntryPoint;

	// Call main
	Push( 0 );		// Arguments count of main
	Push( 0 );		// Initial stack base
	Push( 0 );		// Exit point
	m_StackBase = m_Stack.Size();
}

void VM::VCPU::Init( Data* pData )
{
	m_pData = pData;
	Init();
}



bool VM::VCPU::Terminated() const
{
	return m_Terminated;
}

int VM::VCPU::Run()
{
	try{
		int op;
		while( ( op = *m_pCommandPtr++ ) != VM_HALT ){
			switch( op ){
				#define VM_SWITCHTABLE
				#include "VMCode.h"
				#undef VM_SWITCHTABLE
			}
			// アップデート要求が生じた場合はその場所で一度停止する。
			if( m_HasUpdateReq ){
				m_HasUpdateReq = false;
				return -1;
			}
		}
	}
	catch( const std::exception& e )
	{
		std::cerr << "VM Error : " << e.what() << std::endl;
		return -1;
	}
	m_Terminated = true;
	return Top().m_Integer;		// Return value of main function.
}
