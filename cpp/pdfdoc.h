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

// Includes
#include <windows.h>



#ifndef SHARIFI_PDFDOC_API
#define SHARIFI_PDFDOC_API 1
  
  // Declarations
#define EXP_API extern "C" __declspec(dllexport)
  
EXP_API int Sharifi_GotoPage(HWND,const char*);
EXP_API int Sharifi_GetCurrentPage(HWND,HWND hpost = 0);
EXP_API int Sharifi_About();

#endif

