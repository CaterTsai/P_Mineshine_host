#ifndef MINESHINE_NAME_MANAGER
#define MINESHINE_NAME_MANAGER

#include <string>
using namespace std;

#define CREATE_VALUE(NAME) static const string NAME = #NAME;
#define CREATE_VALUE_WITH_VALUE(NAME, VALUE) static const string NAME = VALUE;

namespace NAME_MGR
{
//-------------------------------------------------
//Theatre
//-------------------------------------------------
///////////////////////////////////////
// Scenes
///////////////////////////////////////
	CREATE_VALUE(S_MAIN);
	CREATE_VALUE(S_MV);
	CREATE_VALUE(S_KV);

///////////////////////////////////////
// Actor
///////////////////////////////////////
	CREATE_VALUE(A_MAIN_LOOP);
	CREATE_VALUE(A_QR);

	CREATE_VALUE(A_MENU_LOOP);
	CREATE_VALUE(A_TYPE_HOT_LOOP);
	CREATE_VALUE(A_TYPE_WARM_LOOP);
	CREATE_VALUE(A_TYPE_FRESH_LOOP);	

	CREATE_VALUE(A_MV_1);
	CREATE_VALUE(A_MV_2);
	CREATE_VALUE(A_MV_3);
	CREATE_VALUE(A_MV_4);
	CREATE_VALUE(A_MV_5);
	CREATE_VALUE(A_MV_6);
	CREATE_VALUE(A_MV_7);
	CREATE_VALUE(A_MV_8);
	CREATE_VALUE(A_MV_9);
	CREATE_VALUE(A_MV_10);
	CREATE_VALUE(A_MV_11);
	CREATE_VALUE(A_MV_12);
	CREATE_VALUE(A_MV_13);

	CREATE_VALUE(A_KV);

///////////////////////////////////////
// Plane
///////////////////////////////////////
	CREATE_VALUE(P_MAIN_OPEN);
	CREATE_VALUE(P_MAIN_MENU);
	CREATE_VALUE(P_MAIN_TYPE);

	CREATE_VALUE(P_MV);
	CREATE_VALUE(P_KV);
	
///////////////////////////////////////
// Element
///////////////////////////////////////
	CREATE_VALUE(E_MAIN_LOOP);
	CREATE_VALUE(E_QR);

	CREATE_VALUE(E_MENU_LOOP);

	CREATE_VALUE(E_TYPE_HOT_LOOP);
	CREATE_VALUE(E_TYPE_WARM_LOOP);
	CREATE_VALUE(E_TYPE_FRESH_LOOP);

	CREATE_VALUE(E_MV);

	CREATE_VALUE(E_KV);

///////////////////////////////////////
// Translate
///////////////////////////////////////

///////////////////////////////////////
// Theatre Animation Set
///////////////////////////////////////
	
	CREATE_VALUE(AS_HotTypeExit);
	CREATE_VALUE(AS_WarmTypeExit);
	CREATE_VALUE(AS_FreshTypeExit);

///////////////////////////////////////
// Theatre Animation
///////////////////////////////////////	
	CREATE_VALUE(ANIM_QREnter);

	CREATE_VALUE(ANIM_HotTypeExit);
	CREATE_VALUE(ANIM_WarmTypeExit);
	CREATE_VALUE(ANIM_FreshTypeExit);

///////////////////////////////////////
// Event
///////////////////////////////////////
	CREATE_VALUE(EVENT_ENABLE_LISTEN_STATE);
};

#endif // !MINESHINE_NAME_MANAGER