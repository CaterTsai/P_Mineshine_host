#ifndef MINESHINE_CONST_PARAMETER
#define MINESHINE_CONST_PARAMETER

#include "ofMain.h"
#include "NameManager.h"

const static int cWINDOW_WIDTH = 1280;
const static int cWINDOW_HEIGHT = 720;

//PHP active name
const static string cADD_NEW_QRCODE = "new_qr";
const static string cCHECK_DB = "check";
const static float cCHECK_TIME = 1.0;

//BGM
const static float cBGM_FADE_TIME = 1.0;

//QR code
const static int cQR_SIZE = 235;

//MV
const static int cWAIT_TO_REST = 5;
const static int cSONG_NUM = 13;

//SLACK
const static float cKEEP_ALIVE_TIMER = 1 * 60.0 * 30.0; //30 mins
#endif // !MINESHINE_CONST_PARAMETER