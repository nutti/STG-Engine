#ifndef INCLUDED_RTG_HISTORY_H
#define INCLUDED_RTG_HISTORY_H

#include "Defines.h"

#include "Scene.h"

namespace RTG
{
	class History : public Scene
	{
	public:
		History();
		~History();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif