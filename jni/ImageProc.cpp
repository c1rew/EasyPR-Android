#include<com_example_carplate_CarPlateDetection.h>
#include "plate_locate.h"
#include "plate_judge.h"
#include "chars_segment.h"
#include "chars_identify.h"
#include "plate_detect.h"
#include "chars_recognise.h"
#include "plate_recognize.h"
using namespace easypr;
#include <android/log.h>
#include <string>
#define LOG_TAG "System.out"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


JNIEXPORT jstring JNICALL Java_com_example_carplate_CarPlateDetection_ImageProc(
		JNIEnv *env, jclass obj, jstring imgpath, jstring svmpath,
		jstring annpath) {
	CPlateRecognize pr;
	const char *img = env->GetStringUTFChars(imgpath, 0);
	const char *svm = env->GetStringUTFChars(svmpath, 0);
	const char *ann = env->GetStringUTFChars(annpath, 0);

	Mat src = imread(img);
	pr.LoadSVM(svm);
	pr.LoadANN(ann);

	pr.setLifemode(true);
    pr.setDebug(false);
	pr.setMaxPlates(3);

	vector <string> plateVec;
	int count = pr.plateRecognize(src, plateVec);

	string str;

	if (count == 0 && plateVec.size() != 0) {
		str = plateVec[0];
	}

	char *result = NULL;
    if (plateVec.size() == 0) {
		result = "";
	} else {
		result = new char[str.length() + 1];
		strcpy(result, str.c_str());
	}
    jstring strRet = env->NewStringUTF(result);
    return strRet;
}

