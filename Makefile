#  PlumeSim Makefile
#  PlumeSim source available at:
#  http://embedded.deec.uc.pt/~guardians/plumesim/Downloads_files/PlumeSim1.0.zip
#
#
#  Follow these directions if source was obtained from above link: 
#	1. Unzip the PlumeSim source into a single base directory
#	2. Create a subdirectory called utils
#	3. Move all source files into utils except 
#	   PlumeSim.cpp, config.h, and replace.h
#	4. Copy this makefile into the PlumeSim base directory
#	5. Run "make"
#
#  Rich Mattes
#  08 Aug 2010

SRC = PlumeSim.cpp utils/PSFluent.cpp utils/PSGaussian.cpp \
utils/PSLog.cpp utils/PSMeadering.cpp utils/PSOdorSensor.cpp \
utils/PSSource.cpp utils/PSFramePoints.cpp utils/PSPoints2Draw.cpp 

OBJLIBS = libPlumeSim.so

OBJS = PlumeSim.o PSFluent.o PSGaussian.o \
PSLog.o PSMeadering.o PSOdorSensor.o \
PSSource.o PSFramePoints.o PSPoints2Draw.o 

CXX = g++

all: $(OBJLIBS)

$(OBJS): $(SRC)
	@echo "-> Building the PlumeSim plugin..."
	$(CXX) -Wall -fpic -g3 `pkg-config --cflags playercore` -c $(SRC)

$(OBJLIBS): $(OBJS)
	@echo "-> Linking the PlumeSim plugin..."
	$(CXX) -rdynamic -shared -nostartfiles -o $@ $^
	@echo "-> Done."

clean:
	@echo "-> Cleaning up the PlumeSim plugin..."
	rm -f $(OBJS) $(OBJLIBS)
	@echo "-> Done."

.SILENT:
