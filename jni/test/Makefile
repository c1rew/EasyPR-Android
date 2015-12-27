#################################################################
#
# Makefile for android tool
#
#################################################################


INCLUDE  += -I/home/zhengql/install/EasyPR/jni/include/ -I/home/zhengql/install/EasyPR/jni/include/easypr/
INCLUDE  += -I/home/zhengql/install/EasyPR/OpenCV-2.4.10-android-sdk/sdk/native/jni/include/
CFLAGS   = -D__USE_BSD -DHAVE_CONFIG_H -D__BARRY_LIBRARY_BUILD__ -D__BARRY_HAVE_GCCVISIBILITY__  -DSQLITE_HAS_CODEC
CFLAGS  += -D_FILE_OFFSET_BITS=64 -fno-strict-aliasing -fvisibility=hidden
CFLAGS  += -Wno-unused-function -Wall -g -O2 -Werror
CFLAGS  += ${INCLUDE}

LIBPATH  = -L/home/zhengql/install/EasyPR/libs/armeabi-v7a/
LIBS     = -lImageProc -lopencv_java
LDFLAGS  = $(LIBPATH) $(LIBS)


# target
TARGET   = test
OBJS     = test.o
           

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CPP) $(OBJS) -o $(TARGET) $(LDFLAGS)
	
.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ 
.cpp.o:
	@$(CPP) $(CFLAGS) -c $< -o $@
	
clean:
	-rm -rf *.o
	-rm -rf ./-Wno-psabi
	-rm -rf $(TARGET)
