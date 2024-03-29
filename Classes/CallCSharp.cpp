#include "CallCSharp.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

namespace cocos2d {
	ICallback ^CSCallback = nullptr;

	BroswerEventHelper::BroswerEventHelper(void)
	{

	}

	void BroswerEventHelper::SetCallback(ICallback ^Callback)
	{
		CSCallback = Callback;
	}

	void BroswerEventHelper::shareGame(Platform::String ^str)
	{
		if (CSCallback != nullptr){
			CSCallback->shareGame(str);
		}
	}

	void BroswerEventHelper::sharePhoto(Platform::String ^path)
	{
		if (CSCallback != nullptr)
		{
			CSCallback->sharePhoto(path);
		}
	}

	void BroswerEventHelper::rateGame()
	{
		if (CSCallback != nullptr)
		{
			CSCallback->rateGame();
		}
	}

	void BroswerEventHelper::likePage()
	{
		if (CSCallback != nullptr)
		{
			CSCallback->likePage();
		}
	}

	void BroswerEventHelper::showAds(bool isshow)
	{
		if (CSCallback != nullptr)
		{
			CSCallback->showAds(isshow);
		}
	}

	void BroswerEventHelper::removeAds()
	{
		if (CSCallback != nullptr)
		{
			CSCallback->removeAds();
		}
	}

	bool BroswerEventHelper::isBuyRemoveAds()
	{
		if (CSCallback != nullptr)
		{
			return CSCallback->isBuyRemoveAds();
		}
	}
}
#endif