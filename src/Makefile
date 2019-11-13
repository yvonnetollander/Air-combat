# source files to compile
SRC = main.cpp Engine.cpp GameEntity.cpp Infantry.cpp MovingEntity.cpp Plane.cpp Troop.cpp util.cpp
# build/binary dir
BUILD_DIR = ../build
# build/binary dir from the library include path
LIB_BUILD_DIR = ../../$(BUILD_DIR)
 # library dir
LIB_DIR = ../lib/SFML-2.5.1
# library dir with backslashes for windows workdir trickery
LIB_DIR_WIN = ..\lib\SFML-2.5.1
# compilers
CXX = g++
CXX_WSL = i686-w64-mingw32-g++
# compiler & linker flags
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -I$(LIB_DIR)/include -L$(LIB_DIR)/bin
# lib link flags
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
LDLIBS_LOCAL = -lsfml-graphics-2 -lsfml-audio-2 -lsfml-window-2 -lsfml-system-2 
# mingw flags (to statically link C and C++ standard libs)
MINGW_FLAGS = -static-libgcc -static-libstdc++
.DEFAULT_GOAL := br

# Figure out what kind of env we're in
WSLENV ?= notwsl
ifeq '$(findstring ;,$(PATH))' ';'
    UNAME := win
	RMC := del /q
else
	ifndef WSLENV
		UNAME := wsl
	else
    	UNAME := linux
	endif
	RMC := $(RM)
endif

build-win: $(SRC)
	$(CXX_WSL) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(BUILD_DIR)\game.exe $(LDLIBS_LOCAL)

win: build-win
	CMD /C "START /D $(LIB_DIR_WIN)\bin $(BUILD_DIR)\game.exe"

run-win:
	CMD /C "START /D $(LIB_DIR_WIN)\bin $(BUILD_DIR)\game.exe"

build-linux: $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(BUILD_DIR)/game $(LDLIBS)

linux: build-linux
	(cd $(LIB_DIR)/bin && exec $(LIB_BUILD_DIR)/game)

run-linux:
	(cd $(LIB_DIR)/bin && exec $(LIB_BUILD_DIR)/game)

build-wsl:
	mkdir -p $(BUILD_DIR)
	$(CXX_WSL) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/game.exe $(MINGW_FLAGS) $(LDLIBS_LOCAL)

wsl: build-wsl
	CMD.exe /C "START /D $(LIB_DIR_WIN)\bin $(BUILD_DIR)\game.exe"

run-wsl:
	CMD.exe /C "START /D $(LIB_DIR_WIN)\bin $(BUILD_DIR)\game.exe"

br:
	$(info ** Runtime environment detected as '$(UNAME)' **)
	$(MAKE) $(UNAME)

build:
	$(info ** Runtime environment detected as '$(UNAME)' **)
	$(MAKE) build-$(UNAME)

run:
	$(info ** Runtime environment detected as '$(UNAME)' **)
	$(MAKE) run-$(UNAME)

clean:
	$(RMC) "$(BUILD_DIR)/*"
