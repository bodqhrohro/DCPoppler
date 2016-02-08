#include <stdlib.h>
#include <gtk/gtk.h>
#include <poppler/glib/poppler.h>
#include <cairo/cairo.h>

#define lc_copy			1
#define lc_newparams		2
#define lc_selectall		3
#define lc_setpercent		4
#define lcp_wraptext		1
#define lcp_fittowindow		2
#define lcp_ansi		4
#define lcp_ascii		8
#define lcp_variable		12
#define lcp_forceshow		16
#define lcp_fitlargeronly	32
#define lcp_center		64
#define lcs_findfirst		1
#define lcs_matchcase		2
#define lcs_wholewords		4
#define lcs_backwards		8
#define itm_percent		0xfffe
#define itm_fontstyle		0xfffd
#define itm_wrap		0xfffc
#define itm_fit			0xfffb
#define itm_next		0xfffa
#define itm_center		0xfff9
#define LISTPLUGIN_OK		0
#define LISTPLUGIN_ERROR	1

#define MAX_PATH		32000

struct tListDefaultParamStruct {
	long size,
	PluginInterfaceVersionLow,
	PluginInterfaceVersionHi;
	char DefaultIniName[MAX_PATH];
};

struct tdateformat {
	int wYear,
	wMonth,
	wDay;
};

struct ttimeformat {
	int wHour,
	wMinute,
	wSecond;
};

typedef long HBITMAP;
typedef GtkWidget thandle;
typedef void trect;
typedef void hbitmap;

extern "C" {
	thandle* ListLoad(thandle* ParentWin, char* FileToLoad, int ShowFlags);
	int ListLoadNext(thandle* ParentWin, thandle PluginWin, char* FileToLoad, int ShowFlags);
	void ListCloseWindow(thandle* ListWin);
	void ListGetDetectString(char* DetectString, int maxlen);
	int ListSearchText(thandle* ListWin, char* SearchString, int SearchParameter);
	int ListSearchDialog(thandle* ListWin, int FindNext);
	int ListSendCommand(thandle* ListWin, int Command, int Parameter);
	int ListPrint(thandle* ListWin, char* FileToPrint, char* DefPrinter, int PrintFlags, trect* Margins);
	int ListNotificationReceived(thandle* ListWin, int Message, int wParam, int lParam);
	void ListSetDefaultParams(tListDefaultParamStruct* dps);
	void ListGetPreviewBitmap(char* FileToLoad, int width, int height, char* contentbuf, int contentbuflen);
}
