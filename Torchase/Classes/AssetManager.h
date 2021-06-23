

#ifndef __ASSETMANAGER__
#define __ASSETMANAGER__

#include "cocos2d.h"
#include "AudioEngine.h"
#include <string>
class AssetManager 
{
private:
	static AssetManager* mInstancePtr;
public:
	
	
	AssetManager();
	void PlayMusic(std::string name);
	static AssetManager* getInstance() {
		return mInstancePtr;
	}
 
};

#endif // __SPLASH_SCENE_H__
