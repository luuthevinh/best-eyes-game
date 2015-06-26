#ifndef __CALL_CSHARP_H__
#define __CALL_CSHARP_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

namespace cocos2d
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class ICallback
	{
	public:
		//the virtual method that will be implemented in your .cs file
		virtual void shareGame(Platform::String ^str);
		virtual void sharePhoto(Platform::String ^path);
		virtual void rateGame();
		virtual void likePage();
	};

	public ref class BroswerEventHelper sealed
	{
	public:
		BroswerEventHelper(void);
		static void SetCallback(ICallback ^Callback);
		static void shareGame(Platform::String ^str);
		static void sharePhoto(Platform::String ^path);
		static void rateGame();
		static void likePage();
	};

}

#endif

#endif //__CALL_CSHARP_H__