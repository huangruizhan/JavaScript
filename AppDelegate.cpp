#include "AppDelegate.h"
#include "HelloWorldScene.h"

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

//����Ĭ�Ϸֱ��ʼ����ֳߴ��ֱ��ʣ���������

static cocos2d::Size designResolutionSize = cocos2d::Size(900,600);
/*����*/
static cocos2d::Size smallResolutionSize = cocos2d::Size(900,600);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(3048,2538);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

//���� OpenGL�������������ö�����ƽ̨����Ч
void AppDelegate::initGLContextAttrs()
{
	//����OpenGL context ����,Ŀǰֻ������6������
	//red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}


static int register_all_packages()
{
    return 0;
}

//��Ӧ�ó�������ʱִ��,��Ϸ������������
//���������������˵�һ��scen
bool AppDelegate::applicationDidFinishLaunching() {

	auto director = Director::getInstance();
	/*glview���Ǵ����������Ĵ�Сview*/
	auto glview = director->getOpenGLView();

    if(!glview) {
		/*GLViewImpl::createWithRect������Ļ��С*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("fishingJone", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("fishingJone");
#endif
        director->setOpenGLView(glview);
    }
	/*�Ƿ���ʾ֡*/
    director->setDisplayStats(true);
	/*֡�Ĵ�С*/
    director->setAnimationInterval(1.0f / 60);

	//�ֱ�������
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();

   if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }

    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }

    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

	//����һ��HelloWorld��scene���������еĵ�һ������
    auto scene = HelloWorld::createScene();

    director->runWithScene(scene);

    return true;
}

// �л�����̨
void AppDelegate::applicationDidEnterBackground() {
	//��ͣ��Ϸ
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// �л���ǰ̨
void AppDelegate::applicationWillEnterForeground() {

	//������Ϸ
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
