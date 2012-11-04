#ifndef INCLUDED_RTG_CONFIG_H
#define INCLUDED_RTG_CONFIG_H

#include "Defines.h"

#include "Scene.h"

namespace RTG
{
	class Config : public Scene
	{
	private:
		enum ConfigMenu
		{
			CONFIG_MENU_SE_VOLUME		= 0,
			CONFIG_MENU_BGM_VOLUME		= 1,
			CONFIG_MENU_BUTTON			= 100,
			CONFIG_MENU_EXIT			= 2,
		};
		enum ButtonSelect
		{
			BUTTON_SELECT_UP			= 0,
			BUTTON_SELECT_DOWN			= 1,
			BUTTON_SELECT_RIGHT			= 2,
			BUTTON_SELECT_LEFT			= 3,
			BUTTON_SELECT_BARRIER		= 4,
			BUTTON_SELECT_ROT_CW		= 5,
			BUTTON_SELECT_ROT_CCW		= 6,
			BUTTON_SELECT_CANCEL		= 7,
			BUTTON_SELECT_PAUSE			= 8,
			BUTTON_SELECT_ENTER			= 9,
			BUTTON_SELECT_NONE			= 200,
		};
		int		m_CurMenu;
		int		m_CurButtonSelectMenu;
	public:
		Config();
		~Config();
		void Update();
		void Draw();
		void Init();
		bool IsLoading() const;
	};
}

#endif