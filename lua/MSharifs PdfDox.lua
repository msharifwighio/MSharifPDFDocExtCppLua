
 --[[
 Developer: Mohammad Sharif Wighio
 PDDOC PDF DOC Extension
 Version: 2.0
 Dated: 5 Oct 2017
 
 DLL to LUA linking library
 This files provides library to access the DLL functions compiled from C++, via into LUA Programming Interface.
 
 ]]--

-- Path to the dll file
 PDFDOC_EXT_DLL = _SourceFolder .. "\\pdfdox.dll"; 
 
 PDFDOC_EXT_NORETURN = "";
 PDFDOC_EXT_HOSTOBJNAME = "obHostv2";
 PdfDocExt = {};
 -- Host Object that will recieve the text
 PdfDocExt.HostObj = nil;
 PdfDocExt.HostWnd = 0;
 PdfDocExt.Ready = false;
 
 PdfDocExt.HostObjProps = {};
 PdfDocExt.HostObjProps.Enable = false;
 PdfDocExt.HostObjProps.Visible = false;
 PdfDocExt.HostObjProps.X = 0;
 PdfDocExt.HostObjProps.Y = 0;
 
 
 --[[
  GetCurrentPage: Retrieves the current page from any active document in Adobe Acrobat Reader
  -- Arguments:
     str strObhName   -> The valid name of the pdf object want get current page
  
  -- Returns
    str   --> Current page in string of the document
 ]]--
 PdfDocExt.GetCurrentPage = function(strObjName)
   -- Check the dll file existance
   if not File.DoesExist(PDFDOC_EXT_DLL) then
   result = Dialog.Message("Missing DLL file", "The MSharif's PdfDoc Ext DLL file is not found.\r\nFile Path: '"..PDFDOC_EXT_DLL.."'", MB_OK, MB_ICONSTOP, MB_DEFBUTTON1);
   return "";
   end
   
   local Obj = PDF.GetProperties(strObjName);
   local hWnd = 0;
   local strCPage = "";
   
   -- Check the host status
   if PdfDocExt.Ready == false or PdfDocExt.HostWnd == 0 then
       -- Create host host object
       Page.CreateObject(OBJECT_INPUT, PDFDOC_EXT_HOSTOBJNAME, PdfDocExt.HostObjProps);
       local p = Input.GetProperties(PDFDOC_EXT_HOSTOBJNAME);
       if p ~= nil then
          PdfDocExt.Ready = true;
          PdfDocExt.HostWnd = p.WindowHandle;
          else return "";
       end
   end
   
    if Obj ~= nil then
       hWnd = Obj.WindowHandle;       
       -- Check the handle status 
       local params = hWnd .. "," .. PdfDocExt.HostWnd;
       local resp = DLL.CallFunction(PDFDOC_EXT_DLL, "Sharifi_GetCurrentPage", params, 1, 0 );
       if resp == 0 then return PDFDOC_EXT_NORETURN; end
       strCPage =  Input.GetText(PDFDOC_EXT_HOSTOBJNAME);
    end 
  
  

  return strCPage;
 
 end
 
 --[[
  GetCurrentPage: Retrieves the current page from any active document in Adobe Acrobat Reader
  -- Arguments:
     str strObhName   -> The valid name of the pdf object
     str strPage      -> Page where to navigate
  
  -- Returns
    1 or 0
 ]]--
 PdfDocExt.GotoPage = function(strObjName, strPage)
   
   -- Check the dll file existance
   if not File.DoesExist(PDFDOC_EXT_DLL) then
   result = Dialog.Message("Missing DLL file", "The MSharif's PdfDoc Ext DLL file is not found.\r\nFile Path: '"..PDFDOC_EXT_DLL.."'", MB_OK, MB_ICONSTOP, MB_DEFBUTTON1);
   return "";
   end
   
   local Obj = PDF.GetProperties(strObjName);
   local hWnd = 0;
   local strCPage = "";
   
    if Obj ~= nil then
       hWnd = Obj.WindowHandle;
             
       -- Check the handle status
       local params = hWnd .. "," .. "\"" .. strPage .. "\"";
       
       local resp = DLL.CallFunction(PDFDOC_EXT_DLL, "Sharifi_GotoPage", params, 1, 0 );
       return resp;
       
    end 
  
  return 0;
 
 end
 
 -- Shows the dll info
 PdfDocExt.About = function()
   
   -- Check the dll file existance
   if not File.DoesExist(PDFDOC_EXT_DLL) then
   result = Dialog.Message("Missing DLL file", "The MSharif's PdfDoc Ext DLL file is not found.\r\nFile Path: '"..PDFDOC_EXT_DLL.."'", MB_OK, MB_ICONSTOP, MB_DEFBUTTON1);
   return "";
   end
   
   local resp DLL.CallFunction(PDFDOC_EXT_DLL, "Sharifi_About", "", 1, 0 );
   return resp;
 end