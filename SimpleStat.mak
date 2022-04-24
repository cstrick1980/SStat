# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = SimpleStat.exe
OBJFILES = SimpleStat.obj Bordinv.obj Buildss.obj Listdata.obj mathss.obj \
   Meanstat.obj minmax.obj Readfile.obj Regr.obj TSSData.obj Ttest.obj Anova.obj \
   Medstats.obj Heapsort.obj Stats.obj Domode.obj GetPlot.obj SSScatter.obj \
   SSGetVarList.obj SSMathEntry.obj SSBar.obj SSAbout.obj TSStat.obj \
   SSGetSingleList.obj
RESFILES = SimpleStat.res
RESDEPEN = $(RESFILES) GetPlot.dfm SSScatter.dfm SSGetVarList.dfm \
   SSMathEntry.dfm SSBar.dfm SSAbout.dfm TSStat.dfm SSGetSingleList.dfm
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -Od -Hc -w -k -r- -y -v -vi- -c -a4 -b- -w-par -w-inl -Vx -Ve -x
CFLAG2 = -Ic:\stat\src\original;c:\stat\src;$(BCB)\projects;$(BCB)\components\txygraph;$(BCB)\include;$(BCB)\include\vcl \
   -H=$(BCB)\lib\vcld.csm 
PFLAGS = -Uc:\stat\src\original;c:\stat\src;$(BCB)\projects;$(BCB)\components\txygraph;$(BCB)\lib\obj;$(BCB)\lib \
   -Ic:\stat\src\original;c:\stat\src;$(BCB)\projects;$(BCB)\components\txygraph;$(BCB)\include;$(BCB)\include\vcl \
   -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -v \
   -$Y -$W -$O- -JPHNV -M     
RFLAGS = -ic:\stat\src\original;c:\stat\src;$(BCB)\projects;$(BCB)\components\txygraph;$(BCB)\include;$(BCB)\include\vcl 
LFLAGS = -Lc:\stat\src\original;c:\stat\src;$(BCB)\projects;$(BCB)\components\txygraph;$(BCB)\lib\obj;$(BCB)\lib \
   -aa -Tpe -x -v -V4.0 
IFLAGS = 
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
