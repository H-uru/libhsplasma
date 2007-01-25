# Microsoft Developer Studio Project File - Name="Plasma" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Plasma - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Plasma.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Plasma.mak" CFG="Plasma - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Plasma - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Plasma - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Plasma - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Plasma - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "Tahg" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Plasma - Win32 Release"
# Name "Plasma - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CoreLib"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\CoreLib\hsBitVector.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\hsBounds.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\hsElfStream.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\hsGeometry3.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\hsMatrix44.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\hsRefCnt.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\hsStream.cpp
# End Source File
# Begin Source File

SOURCE=.\CoreLib\plEncryptedStream.cpp
# End Source File
# End Group
# Begin Group "DynLib"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\DynLib\PageID.cpp
# End Source File
# End Group
# Begin Group "NucleusLib"

# PROP Default_Filter ".cpp"
# Begin Group "pnFactory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NucleusLib\pnFactory\plCreatable.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnFactory\plFactory.cpp
# End Source File
# End Group
# Begin Group "pnKeyedObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NucleusLib\pnKeyedObject\hsKeyedObject.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnKeyedObject\plKey.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnKeyedObject\plReceiver.cpp
# End Source File
# End Group
# Begin Group "pnSceneObject"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NucleusLib\pnSceneObject\plAudioInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnSceneObject\plCoordinateInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnSceneObject\plDrawInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnSceneObject\plObjInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnSceneObject\plSceneObject.cpp
# End Source File
# Begin Source File

SOURCE=.\NucleusLib\pnSceneObject\plSimulationInterface.cpp
# End Source File
# End Group
# Begin Group "pnMessage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NucleusLib\pnMessage\plMessage.cpp
# End Source File
# End Group
# Begin Group "pnNetCommon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NucleusLib\pnNetCommon\plSynchedObject.cpp
# End Source File
# End Group
# End Group
# Begin Group "PubUtilLib"

# PROP Default_Filter ""
# Begin Group "plAvatar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plAvatar\plClothingItem.cpp
# End Source File
# End Group
# Begin Group "plResMgr"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plResMgr\plKeyCollector.cpp
# End Source File
# Begin Source File

SOURCE=.\PubUtilLib\plResMgr\plResManager.cpp
# End Source File
# End Group
# Begin Group "plPipeline"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plPipeline\plFogEnvironment.cpp
# End Source File
# End Group
# Begin Group "plScene"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plScene\plSceneNode.cpp
# End Source File
# End Group
# Begin Group "plSurface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plSurface\hsGMaterial.cpp
# End Source File
# End Group
# Begin Group "plGImage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plGImage\plBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\PubUtilLib\plGImage\plCubicEnvironmap.cpp
# End Source File
# Begin Source File

SOURCE=.\PubUtilLib\plGImage\plFont.cpp
# End Source File
# Begin Source File

SOURCE=.\PubUtilLib\plGImage\plMipmap.cpp
# End Source File
# End Group
# Begin Group "plDrawable"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PubUtilLib\plDrawable\plSpan.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\PlasmaTest.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
