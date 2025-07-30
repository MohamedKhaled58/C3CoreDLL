# Microsoft Developer Studio Project File - Name="C3_CORE_DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=C3_CORE_DLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "C3_CORE_DLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "C3_CORE_DLL.mak" CFG="C3_CORE_DLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "C3_CORE_DLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "C3_CORE_DLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/3DGameMap", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "C3_CORE_DLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../libR"
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "C3_CORE_DLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /GB /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_USRDLL" /D "C3_CORE_DLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ijl15l.lib d3d8.lib d3dx8.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"D:\EO\eosource\EoClient\C3_CORE_DLL.dll" /libpath:"../"

!ELSEIF  "$(CFG)" == "C3_CORE_DLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "C3_CORE_DLL___Win32_Debug"
# PROP BASE Intermediate_Dir "C3_CORE_DLL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir ""
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "C3_CORE_DLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "C3_CORE_DLL_EXPORTS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ijl15l.lib d3d8.lib d3dx8.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"D:\EO\eosource\EoClient\C3_CORE_DLL.dll" /pdbtype:sept /libpath:"../"

!ENDIF 

# Begin Target

# Name "C3_CORE_DLL - Win32 Release"
# Name "C3_CORE_DLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\c3_camera.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_capscreen.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_common.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_datafile.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_font.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_key.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_main.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_omni.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_phy.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_ptcl.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_scene.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_shape.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\source\c3_texture.cpp
# End Source File
# Begin Source File

SOURCE=.\source\DnFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\c3_camera.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_capscreen.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_common.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_datafile.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_font.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_key.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_main.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_omni.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_phy.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_ptcl.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_scene.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_shape.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_sprite.h
# End Source File
# Begin Source File

SOURCE=.\include\c3_texture.h
# End Source File
# Begin Source File

SOURCE=.\include\DnFile.h
# End Source File
# Begin Source File

SOURCE=.\include\ijl.h
# End Source File
# Begin Source File

SOURCE=.\include\MyDataFile.h
# End Source File
# Begin Source File

SOURCE=.\include\NvTriStrip.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
