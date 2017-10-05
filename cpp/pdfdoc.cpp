/*
 Developer: Mohammad Sharif Wighio
 PDDOC PDF DOC Extension
 Version: 2.0
 Dated: 5 Oct 2017 09:14

 -----------------------------------------------------------
 -- Objectives for New Version:
 --   Due to the accidental loss of the version 1
 --   Fix some major errors
 --   Increase the flexibility

 ------------------------------------------------------------
 Programmer Prerequisties:
   -- WinAPI
   -- String Conversion
   -- Error handling


 Updates:
   
   2.1 Nil

   2.2 Updated On: 09th of May 2018, Wed 11:39 PM, Night GD, MSharif
      [ Solve the result character problem on Windows 10]
      Version 2.2
 
 */

#include <iostream>
#include <windows.h>
#include "pdfdoc.h"
#include <fstream>

using namespace std;

EXP_API int Sharifi_GotoPage(HWND hWnd,const char*t)
{
	// Return Status
	signed int status = 0; // 0 for Error
	/*
	Two Window Objects which stores the current page
	  1 -> AVUICommandWidget
	  2 -> AVSplitterView
	*/
	// AVUI CommandWidget
	HWND hDocW, hUIWidget, hZoomEdit, hPageEdit;
	HWND hTargetEdit = 0;

	hDocW = FindWindowExA(hWnd, 0, 0, 0);
	if(hDocW != NULL){

		hUIWidget = FindWindowExA(hDocW, 0, "AVL_AVView", "AVUICommandWidget");
		hZoomEdit = FindWindowExA(hUIWidget, 0, 0, 0);
		hPageEdit = FindWindowExA(hUIWidget, hZoomEdit, 0, 0);

		// AVSplitterView
		HWND hSplitter, hSplitPageV, hAVSplitter, hAVScrollPage, hAVScrollV, hAVPageV, hRPageEdit;

		hSplitter = FindWindowExA(hDocW, 0, "AVL_AVView", "AVSplitterView");
		hSplitPageV = FindWindowExA(hSplitter, 0, "AVL_AVView", "AVSplitationPageView");
		hAVSplitter = FindWindowExA(hSplitPageV, 0, "AVL_AVView", "AVSplitterView");

		//AVScrolledPageView
		hAVScrollPage = FindWindowExA(hAVSplitter, 0, "AVL_AVView", "AVScrolledPageView");
		hAVScrollV = FindWindowExA(hAVScrollPage, 0, "AVL_AVView", "AVScrollView");

		hAVPageV = FindWindowExA(hAVScrollV, 0, "AVL_AVView", "AVPageView");
		hRPageEdit = FindWindowExA(hAVPageV, 0, "RICHEDIT50W", 0);

		// Send the text to the edit controlls
		LRESULT a=0,b=0,c=0,d=0;
		a = SendMessageA(hPageEdit, WM_SETTEXT, 0 , LPARAM(t));
		c = SendMessageA(hRPageEdit, WM_SETTEXT, 0 , LPARAM(t));

		// Test the result
		if(a||c){

			// Send the return key press
			b = PostMessageA(hPageEdit, WM_KEYDOWN, VK_RETURN, 0);
			d = PostMessageA(hRPageEdit, WM_KEYDOWN, VK_RETURN, 0);

			// Check the response
			if(b || d) status = 1; else status = 0;
			return status;
		}
	}
	return status;
}
EXP_API int Sharifi_GetCurrentPage(HWND hget,HWND hpost)
{
	// Return Status
	signed int status = 0; // 0 for Error
	/*
	Two Window Objects which stores the current page
	  1 -> AVUICommandWidget
	  2 -> AVSplitterView
	*/
	// AVUI CommandWidget
	HWND hDocW, hUIWidget, hZoomEdit, hPageEdit;
	HWND hTargetEdit = 0;

	hDocW = FindWindowExA(hget, 0, 0, 0);
	if(hDocW != NULL){

		hUIWidget = FindWindowExA(hDocW, 0, "AVL_AVView", "AVUICommandWidget");
		hZoomEdit = FindWindowExA(hUIWidget, 0, 0, 0);
		hPageEdit = FindWindowExA(hUIWidget, hZoomEdit, 0, 0);
	
		// AVSplitterView
		HWND hSplitter, hSplitPageV, hAVSplitter, hAVScrollPage, hAVScrollV, hAVPageV, hRPageEdit;

		hSplitter = FindWindowExA(hDocW, 0, "AVL_AVView", "AVSplitterView");
		hSplitPageV = FindWindowExA(hSplitter, 0, "AVL_AVView", "AVSplitationPageView");
		hAVSplitter = FindWindowExA(hSplitPageV, 0, "AVL_AVView", "AVSplitterView");

		//AVScrolledPageView
		hAVScrollPage = FindWindowExA(hAVSplitter, 0, "AVL_AVView", "AVScrolledPageView");
		hAVScrollV = FindWindowExA(hAVScrollPage, 0, "AVL_AVView", "AVScrollView");

		hAVPageV = FindWindowExA(hAVScrollV, 0, "AVL_AVView", "AVPageView");
		hRPageEdit = FindWindowExA(hAVPageV, 0, "RICHEDIT50W", 0);



		// Set the Buffers
		const int BUFF_SZ = 256;
		char buffA[BUFF_SZ], buffB[BUFF_SZ];//, final[BUFF_SZ]="";

		// Send the Msg: GetText 8bit from the both edits
		LRESULT l=0,c=0;

		if(hRPageEdit)
		{
			l = SendMessageA(hRPageEdit , WM_GETTEXT, sizeof(buffA), LPARAM(buffA));
		}else if(hPageEdit)
		{
			l = SendMessageA(hPageEdit , WM_GETTEXT, sizeof(buffA), LPARAM(buffA));
		}

			
			
		  /*************************************************************
		  Update 2.2:
		  Updated On: 09th of May 2018, Wed 11:39 PM, Night GD, MSharif
		  --------------------------------------------------------------
		  This part of the code is removed to solve the problem of ambiguous results
		  for some files on Window 10 platform.

		  While Analysis:
		      It is found that the causes of the problem was in the below part of the
			  CODE, mal adjustment of the character manipulation.

		  Alternate/New Method:
		      Changes the check implementation to Check and Implement the Rich Text Object First,
			  Then the TextBox.



		  // Compare the results of two different buffers
		  if(strcmp(buffA, buffB) < 0){
				strcpy(final, buffB);
			} else {
				strcpy(final, buffA);
			}

			*********************************************************/

		// Share the retrieved text/page to the host 
		c = SendMessageA(hpost, WM_SETTEXT, 0, LPARAM(buffA));
		//MessageBoxA(0, buffA ,"Response A- MSharif's PDFDoc Ext 2.0", MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
		//MessageBoxA(0, buffB ,"Response B- MSharif's PDFDoc Ext 2.0", MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
		//MessageBoxA(0, buffA ,"Response B- MSharif's PDFDoc Ext 2.0", MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);

		return int(c);
	}
	return status;
}

EXP_API int Sharifi_About()
{
	char Msg[1024] = "MSharif's PDFDoc Ext version 2.2\n----------------------------------\nDeveloped By  Mohammad Sharif Wighio (BSIT SALU)\nDated:  10 October 2017, 05:24PM GMT+5, GD\nLatest Update:  09 May 2018, 11:48PM GMT+5, GD\nEmail: ms.wighio@gmail.com | Facebook/ msharif.wighio\n\n\nWhat's New? \n\n  1. Fixed Major Bugs.\n  2. Added support for English and Roman input.\n  3. Improved Flexibility and Extensibility.\n  4. Improved Support.\n  5. Improved Inter-Communication methods.\n  6. Added Supported for Windows 10 (Version 2.2 Latest).\n  & much more....\n\n\nTested and fully supports Adobe Acrobat XI (Version 11.10.32 Latest)\n\n\n  ~*MSharif";
	MessageBoxA(0, Msg ,"About - MSharif's PDFDoc Ext 2.2", MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
	return 1;
}