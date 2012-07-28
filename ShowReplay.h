#ifndef INCLUDED_RTG_SHOWREPLAY_H
#define INCLUDED_RTG_SHOWREPLAY_H

#include "Defines.h"

#include "Scene.h"

namespace RTG
{
	class Keyboard;
	class ShowReplay : public Scene
	{
		char						m_Name[ 16 ];
		int							m_FileNo;
		char						m_EntryStr[ 25 ][ 256 ];
	public:
		ShowReplay();
		~ShowReplay();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif