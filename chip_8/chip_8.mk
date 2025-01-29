##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=chip_8
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/radiamerabtene/Téléchargements/last
ProjectPath            :=/home/radiamerabtene/Téléchargements/versionfinale/chip8_emulator/chip_8
IntermediateDirectory  :=../../../last/build-$(WorkspaceConfiguration)/__/versionfinale/chip8_emulator/chip_8
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=radiamerabtene
Date                   :=29/01/25
CodeLitePath           :=/home/radiamerabtene/.codelite
MakeDirCommand         :=mkdir -p
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
OutputDirectory        :=/home/radiamerabtene/Téléchargements/last/build-$(WorkspaceConfiguration)/bin
OutputFile             :=../../../last/build-$(WorkspaceConfiguration)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -lprovided -lSDL2 -lm
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include $(IncludeSwitch)./lib/libprovided/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)lib/libprovided/lib/x86_64 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
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
Objects0=$(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix) $(IntermediateDirectory)/src_ram.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_processor.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@$(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix): src/chip8machine.c 
	$(CC) $(SourceSwitch) "/home/radiamerabtene/Téléchargements/versionfinale/chip8_emulator/chip_8/src/chip8machine.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_chip8machine.c$(PreprocessSuffix): src/chip8machine.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_chip8machine.c$(PreprocessSuffix) src/chip8machine.c

$(IntermediateDirectory)/src_ram.c$(ObjectSuffix): src/ram.c 
	$(CC) $(SourceSwitch) "/home/radiamerabtene/Téléchargements/versionfinale/chip8_emulator/chip_8/src/ram.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ram.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ram.c$(PreprocessSuffix): src/ram.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ram.c$(PreprocessSuffix) src/ram.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c 
	$(CC) $(SourceSwitch) "/home/radiamerabtene/Téléchargements/versionfinale/chip8_emulator/chip_8/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/src_processor.c$(ObjectSuffix): src/processor.c 
	$(CC) $(SourceSwitch) "/home/radiamerabtene/Téléchargements/versionfinale/chip8_emulator/chip_8/src/processor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_processor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_processor.c$(PreprocessSuffix): src/processor.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_processor.c$(PreprocessSuffix) src/processor.c

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


