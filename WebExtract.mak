# Microsoft Developer Studio Generated NMAKE File, Based on WebExtract.dsp
!IF "$(CFG)" == ""
CFG=WebExtract - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WebExtract - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WebExtract - Win32 Release" && "$(CFG)" != "WebExtract - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WebExtract.mak" CFG="WebExtract - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WebExtract - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WebExtract - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WebExtract - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\bin\WebExtract.exe"


CLEAN :
	-@erase "$(INTDIR)\regexpr2.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\syntax2.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\webbrowser.obj"
	-@erase "$(INTDIR)\WebExtract.obj"
	-@erase "$(INTDIR)\WebExtract.pch"
	-@erase "$(INTDIR)\WebExtract.res"
	-@erase "$(INTDIR)\WebExtractDlg.obj"
	-@erase ".\bin\WebExtract.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\WebExtract.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\WebExtract.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WebExtract.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\WebExtract.pdb" /machine:I386 /out:"bin/WebExtract.exe" /libpath:"lib" 
LINK32_OBJS= \
	"$(INTDIR)\regexpr2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\syntax2.obj" \
	"$(INTDIR)\webbrowser.obj" \
	"$(INTDIR)\WebExtract.obj" \
	"$(INTDIR)\WebExtractDlg.obj" \
	"$(INTDIR)\WebExtract.res"

".\bin\WebExtract.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\bin\WebExtract_d.exe" "$(OUTDIR)\WebExtract.bsc"


CLEAN :
	-@erase "$(INTDIR)\regexpr2.obj"
	-@erase "$(INTDIR)\regexpr2.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\syntax2.obj"
	-@erase "$(INTDIR)\syntax2.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\webbrowser.obj"
	-@erase "$(INTDIR)\webbrowser.sbr"
	-@erase "$(INTDIR)\WebExtract.obj"
	-@erase "$(INTDIR)\WebExtract.pch"
	-@erase "$(INTDIR)\WebExtract.res"
	-@erase "$(INTDIR)\WebExtract.sbr"
	-@erase "$(INTDIR)\WebExtractDlg.obj"
	-@erase "$(INTDIR)\WebExtractDlg.sbr"
	-@erase "$(OUTDIR)\WebExtract.bsc"
	-@erase "$(OUTDIR)\WebExtract_d.pdb"
	-@erase ".\bin\WebExtract_d.exe"
	-@erase ".\bin\WebExtract_d.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WebExtract.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\WebExtract.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WebExtract.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\regexpr2.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\syntax2.sbr" \
	"$(INTDIR)\webbrowser.sbr" \
	"$(INTDIR)\WebExtract.sbr" \
	"$(INTDIR)\WebExtractDlg.sbr"

"$(OUTDIR)\WebExtract.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\WebExtract_d.pdb" /debug /machine:I386 /out:"bin/WebExtract_d.exe" /pdbtype:sept /libpath:"lib" 
LINK32_OBJS= \
	"$(INTDIR)\regexpr2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\syntax2.obj" \
	"$(INTDIR)\webbrowser.obj" \
	"$(INTDIR)\WebExtract.obj" \
	"$(INTDIR)\WebExtractDlg.obj" \
	"$(INTDIR)\WebExtract.res"

".\bin\WebExtract_d.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WebExtract.dep")
!INCLUDE "WebExtract.dep"
!ELSE 
!MESSAGE Warning: cannot find "WebExtract.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WebExtract - Win32 Release" || "$(CFG)" == "WebExtract - Win32 Debug"
SOURCE=.\greta\regexpr2.cpp

!IF  "$(CFG)" == "WebExtract - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\regexpr2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\regexpr2.obj"	"$(INTDIR)\regexpr2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "WebExtract - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\WebExtract.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WebExtract.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WebExtract.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\WebExtract.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\greta\syntax2.cpp

!IF  "$(CFG)" == "WebExtract - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\syntax2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\syntax2.obj"	"$(INTDIR)\syntax2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\webbrowser.cpp

!IF  "$(CFG)" == "WebExtract - Win32 Release"


"$(INTDIR)\webbrowser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WebExtract.pch"


!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"


"$(INTDIR)\webbrowser.obj"	"$(INTDIR)\webbrowser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WebExtract.pch"


!ENDIF 

SOURCE=.\WebExtract.cpp

!IF  "$(CFG)" == "WebExtract - Win32 Release"


"$(INTDIR)\WebExtract.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WebExtract.pch"


!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"


"$(INTDIR)\WebExtract.obj"	"$(INTDIR)\WebExtract.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WebExtract.pch"


!ENDIF 

SOURCE=.\WebExtract.rc

"$(INTDIR)\WebExtract.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\WebExtractDlg.cpp

!IF  "$(CFG)" == "WebExtract - Win32 Release"


"$(INTDIR)\WebExtractDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WebExtract.pch"


!ELSEIF  "$(CFG)" == "WebExtract - Win32 Debug"


"$(INTDIR)\WebExtractDlg.obj"	"$(INTDIR)\WebExtractDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WebExtract.pch"


!ENDIF 


!ENDIF 

