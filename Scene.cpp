#include "Scene.h"

namespace RTG
{
	Scene::Scene() : m_pNextScene( NULL )
	{
	}

	Scene::~Scene()
	{
	}


	void Scene::SetNextScene( Scene* pNextScene )
	{
		m_pNextScene = pNextScene;
	}

	Scene* Scene::GetNextScene() const
	{
		return m_pNextScene;
	}

	bool Scene::HasNextScene() const
	{
		return m_pNextScene ? true : false;
	}
}