LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# OpenCV
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
include /home/c1rew/install/EasyPR/OpenCV-2.4.10-android-sdk/sdk/native/jni/OpenCV.mk 


EASYPR_SRC_PATH := $(LOCAL_PATH)/src
EASYPR_INC_PATH := $(LOCAL_PATH)/include
 
BLACKLIST_SRC_FILES := \
  %test/accuracy.hpp \
  %test/main.cpp \
  %test/chars.hpp \
  %test/plate.hpp

EASYPR_SRC_FILE := \
  $(wildcard $(EASYPR_SRC_PATH)/core/*.cpp) \
  $(wildcard $(EASYPR_SRC_PATH)/preprocess/*.cpp) \
  $(wildcard $(EASYPR_SRC_PATH)/train/*.cpp) \
  $(wildcard $(EASYPR_SRC_PATH)/util/*.cpp)

LOCAL_SRC_FILES := \
  $(filter-out $(BLACKLIST_SRC_FILES),$(subst $(LOCAL_PATH)/,,$(EASYPR_SRC_FILE)))

LOCAL_C_INCLUDES := \
  $(EASYPR_INC_PATH) \
  $(EASYPR_INC_PATH)/easypr \
  $(EASYPR_INC_PATH)/easypr/preprocess

LOCAL_C_INCLUDES += /home/c1rew/install/EasyPR/OpenCV-2.4.10-android-sdk/sdk/native/jni/include

LOCAL_SRC_FILES += \
  ImageProc.cpp \

LOCAL_CFLAGS := \
  -DUSE_STD_NAMESPACE \
  --std=c++11 \
  -D'VERSION="Android"' \
  -fpermissive \
  -Wno-deprecated

LOCAL_MODULE     := easypr  
LOCAL_LDLIBS += -llog 
include $(BUILD_SHARED_LIBRARY)  

# OpenCV
#OPENCV_CAMERA_MODULES:=on
#OPENCV_INSTALL_MODULES:=on
#include /home/zhengql/install/EasyPR/OpenCV-2.4.10-android-sdk/sdk/native/jni/OpenCV.mk  
#FILE_LIST := $(wildcard $(LOCAL_SRC_PATH)/core/*.cpp)
#LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_SRC_PATH)/%=%)
#LOCAL_SRC_FILES += ImageProc.cpp
#LOCAL_C_INCLUDES += $(LOCAL_SRC_PATH)/include

