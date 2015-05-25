#include "MineshineTheatre.h"

#pragma region Base Method
//--------------------------------------------------------------
void MineshineTheatre::setupTheatre()
{
	_Director.SetStageSize(ofGetWindowWidth(), ofGetWindowHeight());

#pragma region Scenes
	//-------------------------------------------------
	//Scenes
	//-------------------------------------------------
	_Director.AddScenes(NAME_MGR::S_MAIN);
	_Director.AddScenes(NAME_MGR::S_TYPE);
	_Director.AddScenes(NAME_MGR::S_MV);
	_Director.AddScenes(NAME_MGR::S_KV);
#pragma endregion

#pragma region Actor
	//-------------------------------------------------
	//Actor
	//-------------------------------------------------
	//S_MAIN
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_MAIN_BG, "images/main_bg.jpg"));
	_Director.AddActor(new ofxDynamicImageActor(NAME_MGR::A_QR));

	//S_TYPE
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_TYPE_BG, "images/type_bg.jpg"));
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_TYPE_HOT, "images/type_1.jpg"));
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_TYPE_WARM, "images/type_2.jpg"));
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_TYPE_FRESH, "images/type_3.jpg"));
		
	//S_MV
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_1, "mv/1.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_2, "mv/2.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_3, "mv/3.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_4, "mv/4.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_5, "mv/5.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_6, "mv/6.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_7, "mv/7.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_8, "mv/8.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_9, "mv/9.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_10, "mv/10.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_11, "mv/11.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_12, "mv/12.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	_Director.AddActor(new ofxVideoActor(NAME_MGR::A_MV_13, "mv/13.mp4", ofPtr<ofGstVideoPlayer>(new ofGstVideoPlayer)));
	
	//S_KV
	_Director.AddActor(new ofxImageActor(NAME_MGR::A_KV, "images/kv.jpg"));

#pragma endregion

#pragma region Plane
	//-------------------------------------------------
	//Plane
	//-------------------------------------------------
	_Director.AddPlane(NAME_MGR::S_MAIN, NAME_MGR::P_MAIN, 0);
	_Director.AddPlane(NAME_MGR::S_TYPE, NAME_MGR::P_TYPE, 0);
	_Director.AddPlane(NAME_MGR::S_MV, NAME_MGR::P_MV, 0);
	_Director.AddPlane(NAME_MGR::S_KV, NAME_MGR::P_KV, 0);
#pragma endregion

#pragma region Element
	//-------------------------------------------------
	//Element
	//-------------------------------------------------
	//S_MAIN
	_Director.AddElement(NAME_MGR::E_MAIN_BG, NAME_MGR::P_MAIN, NAME_MGR::A_MAIN_BG);
	_Director.AddElement(NAME_MGR::E_QR, NAME_MGR::P_MAIN, NAME_MGR::A_QR, 1, ofPoint(515, 256));

	//S_TYPE
	_Director.AddElement(NAME_MGR::E_TYPE_BG, NAME_MGR::P_TYPE, NAME_MGR::A_TYPE_BG);
	_Director.AddElement(NAME_MGR::E_TYPE_HOT, NAME_MGR::P_TYPE, NAME_MGR::A_TYPE_HOT, 2, ofPoint(0, 0), false);
	_Director.AddElement(NAME_MGR::E_TYPE_WARM, NAME_MGR::P_TYPE, NAME_MGR::A_TYPE_WARM, 3, ofPoint(0, 0), false);
	_Director.AddElement(NAME_MGR::E_TYPE_FRESH, NAME_MGR::P_TYPE, NAME_MGR::A_TYPE_FRESH, 4, ofPoint(0, 0), false);

	//S_MV
	_Director.AddElement(NAME_MGR::E_MV, NAME_MGR::P_MV, NAME_MGR::A_MV_1);
	
	//S_KV
	_Director.AddElement(NAME_MGR::E_KV, NAME_MGR::P_KV, NAME_MGR::A_KV);
#pragma endregion

#pragma region Translate Element
	
#pragma endregion
	
#pragma region Element setting
	//-------------------------------------------------
	//Element Setting
	//-------------------------------------------------	
	//Video
	ofxVideoElement* pVideoElement_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_MV, pVideoElement_);
	pVideoElement_->StartEvent();
	pVideoElement_->SetVideoAutoPlay(true);
#pragma endregion

	_bWaitQRCode = true;
	this->setupTimerTrigger();

	ofAddListener(ofxTheatreEventArgs::TheatreEvent, this, &MineshineTheatre::onTheatreEvent);
	_Director.Play();
}

//--------------------------------------------------------------
void MineshineTheatre::updateTheatre(float fDelta)
{
	this->updateTimerTrigger(fDelta);
	_Director.update();
}

//--------------------------------------------------------------
void MineshineTheatre::drawTheatre()
{
	ofPushStyle();
	{
		ofSetColor(255);
		_Director.draw();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void MineshineTheatre::resetTheatre()
{
	_bWaitQRCode = true;

	_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
}

//--------------------------------------------------------------
void MineshineTheatre::nextScence()
{
	if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_MAIN)
	{
		_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
	}
	else if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_TYPE)
	{
		_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
	}
	else if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_MV)
	{
		_Director.TransitTo(TRANSITION_TYPE::eTRANSITION_NONE);
	}
	else if(_Director.GetNowScenes()->GetScenesName() == NAME_MGR::S_KV)
	{
		this->resetTheatre();
	}
}

//--------------------------------------------------------------
void MineshineTheatre::TheatreAnimInit(string strName)
{
	ofxBaseElement* pElementPtr_ = nullptr;
	if(strName == NAME_MGR::AS_HotTypeEnter)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_HOT, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_TYPE, 0, new ofxEnterAnimation(NAME_MGR::ANIM_HotTypeEnter, pElementPtr_, eEnterType::eENTER_FROM_UP, cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_WarmTypeEnter)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_WARM, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_TYPE, 0, new ofxEnterAnimation(NAME_MGR::ANIM_WarmTypeEnter, pElementPtr_, eEnterType::eENTER_FROM_UP, cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_FreshTypeEnter)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_FRESH, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_TYPE, 0, new ofxEnterAnimation(NAME_MGR::ANIM_FreshTypeEnter, pElementPtr_, eEnterType::eENTER_FROM_UP, cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_HotTypeExit)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_HOT, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_TYPE, 0, new ofxExitAnimation(NAME_MGR::ANIM_HotTypeExit, pElementPtr_, eExitType::eEXIT_TO_UP, cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_WarmTypeExit)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_WARM, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_TYPE, 0, new ofxExitAnimation(NAME_MGR::ANIM_WarmTypeExit, pElementPtr_, eExitType::eEXIT_TO_UP,cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
	else if(strName == NAME_MGR::AS_FreshTypeExit)
	{
		_Director.GetElementPtr(NAME_MGR::E_TYPE_FRESH, pElementPtr_);
		_Director.AddAnimation(NAME_MGR::S_TYPE, 0, new ofxExitAnimation(NAME_MGR::ANIM_FreshTypeExit, pElementPtr_, eExitType::eEXIT_TO_UP,cWINDOW_WIDTH, cWINDOW_HEIGHT));
	}
}

//--------------------------------------------------------------
void MineshineTheatre::onTheatreEvent(ofxTheatreEventArgs& e)
{
	//Element
	if(e.strMessage == NAME_MGR::E_MV)
	{
		this->nextScence();
	}
}
#pragma endregion

#pragma region QR Code
void MineshineTheatre::setQRCodeImg(ofImage& QRImg)
{
	if(!_bWaitQRCode && _Director.GetNowScenes()->GetScenesName() != NAME_MGR::S_MAIN)
	{
		ofLog(OF_LOG_ERROR, "[MineshineTheatre:setQRCodeImg] _bWaitQRCode is false");
		return;
	}

	ofxDynamicImageElement* pQRImg_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_QR, pQRImg_);
	pQRImg_->updateImg(QRImg);
	_bWaitQRCode = false;
}
#pragma endregion

#pragma region MV
bool MineshineTheatre::setMV(int iSongID)
{
	if(iSongID <= 0 || iSongID > cSONG_NUM)
	{
		return false;
	}
	ofxVideoElement* pMV_ = nullptr;
	_Director.GetElementPtr(NAME_MGR::E_MV, pMV_);
	pMV_->ChangeVideoActor(dynamic_cast<ofxVideoActor*>(_Director.GetActor("A_MV_" + ofToString(iSongID) )));
	return true;
}
#pragma endregion

#pragma region Timer Trigger
void MineshineTheatre::setupTimerTrigger()
{
	_fTimer = .0;
	_bEnableTimer = false;
}

//-------------------------------------------------
void MineshineTheatre::updateTimerTrigger(float fDelta)
{
	if(_bEnableTimer)
	{
		_fTimer -= fDelta;

		if(_fTimer < 0.0)
		{
			_bEnableTimer = false;
			_trigger(this);
		}
	}
}

//-------------------------------------------------
void MineshineTheatre::addTimerTrigger(float fTimer, function<void(MineshineTheatre*)> triggerEvent )
{
	if(!_bEnableTimer)
	{
		_fTimer = fTimer;
		_trigger = triggerEvent;
		_bEnableTimer = true;
	}
}

//-------------------------------------------------
void MineshineTheatre::removeTimerTrigger()
{
	if(_bEnableTimer)
	{
		_fTimer = .0;
		_bEnableTimer = false;
	}
}
#pragma endregion
