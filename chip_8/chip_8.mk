##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=chip_8
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/audrey/Bureau/chip8_emulator
ProjectPath            :=/home/audrey/Bureau/chip8_emulator/chip_8
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/chip_8
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=audrey
Date                   :=29/01/25
CodeLitePath           :=/home/audrey/.codelite
MakeDirCommand         :=mkdir -p
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=/home/audrey/Bureau/chip8_emulator/build-$(WorkspaceConfiguration)/bin
OutputFile             :=../build-$(WorkspaceConfiguration)/bin/$(ProjectName)
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_ram.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_processor.c$(ObjectSuffix) $(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/src_ram.c$(ObjectSuffix): src/ram.c $(IntermediateDirectory)/src_ram.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/audrey/Bureau/chip8_emulator/chip_8/src/ram.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ram.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ram.c$(DependSuffix): src/ram.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ram.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ram.c$(DependSuffix) -MM src/ram.c

$(IntermediateDirectory)/src_ram.c$(PreprocessSuffix): src/ram.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ram.c$(PreprocessSuffix) src/ram.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c $(IntermediateDirectory)/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/audrey/Bureau/chip8_emulator/chip_8/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM src/main.c

$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/src_processor.c$(ObjectSuffix): src/processor.c $(IntermediateDirectory)/src_processor.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/audrey/Bureau/chip8_emulator/chip_8/src/processor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_processor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_processor.c$(DependSuffix): src/processor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_processor.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_processor.c$(DependSuffix) -MM src/processor.c

$(IntermediateDirectory)/src_processor.c$(PreprocessSuffix): src/processor.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_processor.c$(PreprocessSuffix) src/processor.c

$(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix): src/chip8machine.c $(IntermediateDirectory)/src_chip8machine.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/audrey/Bureau/chip8_emulator/chip_8/src/chip8machine.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_chip8machine.c$(DependSuffix): src/chip8machine.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_chip8machine.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_chip8machine.c$(DependSuffix) -MM src/chip8machine.c

$(IntermediateDirectory)/src_chip8machine.c$(PreprocessSuffix): src/chip8machine.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_chip8machine.c$(PreprocessSuffix) src/chip8machine.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


