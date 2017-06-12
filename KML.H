/*
 *   kml.h
 *
 *   This file is part of Emu42
 *
 *   Copyright (C) 2004 Christoph Gieﬂelink
 *
 */

#define LEX_BLOCK   0
#define LEX_COMMAND 1
#define LEX_PARAM   2

typedef enum eTokenId
{
	TOK_NONE, //0
	TOK_ANNUNCIATOR, //1
	TOK_BACKGROUND, //2
	TOK_IFPRESSED, //3
	TOK_RESETFLAG, //4
	TOK_SCANCODE, //5
	TOK_HARDWARE, //6
	TOK_MENUITEM, //7
	TOK_DISTANCE, //8
	TOK_SYSITEM, //9
	TOK_INTEGER, //10
	TOK_SETFLAG, //11
	TOK_RELEASE, //12
	TOK_VIRTUAL, //13
	TOK_INCLUDE, //14
	TOK_NOTFLAG, //15
	TOK_STRING, //16
	TOK_GLOBAL, //17
	TOK_AUTHOR, //18
	TOK_BITMAP, //19
	TOK_ZOOMXY, //20
	TOK_OFFSET, //21
	TOK_BUTTON, //22
	TOK_IFFLAG, //23
	TOK_ONDOWN, //24
	TOK_NOHOLD, //25
	TOK_LOCALE, //26
	TOK_TOPBAR, //27
	TOK_MENUBAR, //28
	TOK_TITLE, //29
	TOK_OUTIN, //30
	TOK_PATCH, //31
	TOK_PRINT, //32
	TOK_DEBUG, //33
	TOK_COLOR, //34
	TOK_MODEL, //35
	TOK_CLASS, //36
	TOK_PRESS, //37
	TOK_DIGIT, //38
	TOK_IFMEM, //39
	TOK_TYPE, //40
	TOK_SIZE, //41
	TOK_DOWN, //42
	TOK_ZOOM, //43
	TOK_ELSE, //44
	TOK_ONUP, //45
	TOK_EOL, //46
	TOK_MAP, //47
	TOK_ROM, //48
	TOK_VGA, //49
	TOK_LCD, //50
	TOK_END //51
} TokenId;

#define TYPE_NONE    00
#define TYPE_INTEGER 01
#define TYPE_STRING  02

typedef struct KmlToken
{
	TokenId eId;
	DWORD   nParams;
	DWORD   nLen;
	LPCTSTR szName;
} KmlToken;

typedef struct KmlLine
{
	struct KmlLine* pNext;
	TokenId eCommand;
	DWORD_PTR nParam[6];
} KmlLine;

typedef struct KmlBlock
{
	TokenId eType;
	DWORD nId;
	struct KmlLine*  pFirstLine;
	struct KmlBlock* pNext;
} KmlBlock;

#define BUTTON_NOHOLD  0x0001
#define BUTTON_VIRTUAL 0x0002
typedef struct KmlButton
{
	UINT nId;
	BOOL bDown;
	UINT nType;
	DWORD dwFlags;
	UINT nOx, nOy;
	UINT nDx, nDy;
	UINT nCx, nCy;
	UINT nOut, nIn;
	KmlLine* pOnDown;
	KmlLine* pOnUp;
} KmlButton;

typedef struct KmlAnnunciator
{
	UINT nOx, nOy;
	UINT nDx, nDy;
	UINT nCx, nCy;
} KmlAnnunciator;

extern KmlBlock* pKml;
extern KmlAnnunciator pAnnunciator[60];
extern BOOL DisplayChooseKml(CHAR cType);
extern VOID FreeBlocks(KmlBlock* pBlock);
extern VOID DrawAnnunciator(UINT nId, BOOL bOn, DWORD dwColor);
extern VOID ReloadButtons(WORD *Keyboard_Row, UINT nSize);
extern VOID RefreshButtons(RECT *rc);
extern BOOL MouseIsButton(DWORD x, DWORD y);
extern VOID MouseButtonDownAt(UINT nFlags, DWORD x, DWORD y);
extern VOID MouseButtonUpAt(UINT nFlags, DWORD x, DWORD y);
extern VOID MouseMovesTo(UINT nFlags, DWORD x, DWORD y);
extern VOID RunKey(BYTE nId, BOOL bPressed);
extern VOID PlayKey(UINT nOut, UINT nIn, BOOL bPressed);
extern BOOL InitKML(LPCTSTR szFilename, BOOL bNoLog);
extern VOID KillKML(VOID);
