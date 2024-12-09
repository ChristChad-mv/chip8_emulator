##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=chip_8
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/administrateur/Téléchargements/chip8_emulator
ProjectPath            :=/home/administrateur/Téléchargements/chip8_emulator/chip_8
IntermediateDirectory  :=../build-$(ConfigurationName)/chip_8
OutDir                 :=../build-$(ConfigurationName)/chip_8
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=administrateur
Date                   :=09/12/24
CodeLitePath           :=/home/administrateur/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -lprovided -lSDL2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include $(IncludeSwitch)./lib/libprovided/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)lib/libprovided/lib/x86_64 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/chip_8/src_ram.c$(ObjectSuffix) ../build-$(ConfigurationName)/chip_8/src_main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/chip_8/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/chip_8"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/chip_8"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/chip_8/.d:
	@mkdir -p "../build-$(ConfigurationName)/chip_8"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/chip_8/src_ram.c$(ObjectSuffix): src/ram.c ../build-$(ConfigurationName)/chip_8/src_ram.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/administrateur/Téléchargements/chip8_emulator/chip_8/src/ram.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ram.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/chip_8/src_ram.c$(DependSuffix): src/ram.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/chip_8/src_ram.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/chip_8/src_ram.c$(DependSuffix) -MM src/ram.c

../build-$(ConfigurationName)/chip_8/src_ram.c$(PreprocessSuffix): src/ram.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/chip_8/src_ram.c$(PreprocessSuffix) src/ram.c

../build-$(ConfigurationName)/chip_8/src_main.c$(ObjectSuffix): src/main.c ../build-$(ConfigurationName)/chip_8/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/administrateur/Téléchargements/chip8_emulator/chip_8/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/chip_8/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/chip_8/src_main.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/chip_8/src_main.c$(DependSuffix) -MM src/main.c

../build-$(ConfigurationName)/chip_8/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/chip_8/src_main.c$(PreprocessSuffix) src/main.c


-include ../build-$(ConfigurationName)/chip_8//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


