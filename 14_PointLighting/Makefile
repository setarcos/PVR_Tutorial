PVRSDK=/home/yangyj/work/arm/graphics/Native_SDK
PVRFRAME=$(PVRSDK)/framework
PVRSDKINC=$(PVRSDK)/include
CDEFINE=-DX11
TARGET=HelloPVR
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o, $(SRC))
LIBS=$(PVRSDK)/build/framework/PVRShell/libPVRShell.a \
	 $(PVRSDK)/build/framework/PVRAssets/libPVRAssets.a \
	 $(PVRSDK)/build/framework/PVRUtils/OpenGLES/libPVRUtilsGles.a \
	 $(PVRSDK)/build/framework/PVRCore/libPVRCore.a
all: $(TARGET)
%.o: %.cpp
	g++ $(CDEFINE) $< -I$(PVRFRAME) -I$(PVRSDKINC) -c

$(TARGET): $(OBJ)
	g++ $(OBJ) $(LIBS) -lX11 -ldl -o $(TARGET)
clean:
	rm *.o $(TARGET) log.txt
