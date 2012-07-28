#include <Windows.h>
#include <crtdbg.h>


#include <MAPIL/MAPIL.h>

#include <MAPIL/Input/Keyboard.h>

#include <MAPIL/Sound/ALSoundFactory.h>
#include <MAPIL/Sound/SoundDevice.h>

#include <MAPIL/IO/Console.h>
#include <MAPIL/Util/FPSManager.h>

#include <MAPIL/Util/Singleton.hpp>

#include <MAPIL/IO/TTFFile.h>

#include <MAPIL/Util/Allocator.hpp>

#include <MAPIL/Math/Vector.hpp>

#pragma comment( lib, "MAPIL.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment ( lib, "OpenAL32.lib" )


#pragma warning ( disable : 4996 )		// 4996 warning Çè¡Ç∑