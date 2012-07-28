#ifndef INCLUDED_RTG_SCENE_H
#define INCLUDED_RTG_SCENE_H

#include "Defines.h"

namespace RTG
{
	class Scene
	{
		Scene*			m_pNextScene;
	public:
		Scene();
		virtual ~Scene();
		virtual void Update() = 0;
		virtual void Draw() = 0;
		//virtual void Draw3D() = 0;
		void SetNextScene( Scene* pNextScene );
		Scene* GetNextScene() const;
		bool HasNextScene() const;
		virtual void Init() = 0;
		virtual bool IsLoading() const = 0;
	};
}

#endif