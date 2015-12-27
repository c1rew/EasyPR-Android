# 关于本项目
本项目是根据 linuxxx 的 EasyPR_Android 修改而来，在此感谢linuxxx，只是将jni修改成了EasyPR最新版，修改了jni编译脚本，对应修改了Android工程中的一些小问题，也解决了jni检测图片时，因为图片中无车牌而导致的检测崩溃问题。


# 注意MainActivity下
		String svmpath = path+"/svm.xml";
		String annpath = path+"/ann.xml";
		imgDir = path + "PIC/"
将项目jni/model 下的svm.xml和ann.xml导入你手机的SD卡根目录下的EasyPR目录中，将要测试的图片放到SD卡下PIC目录，可以放多张；

# 使用步骤
* 下载并导入OpenCV-2.4.10-android-sdk项目到eclipse，设置为is Library

* 导入EasyPR-Android该项目，添加引用
右键properties-> Android-> library-> add OpenCV-2.4.10-android-sdk

* 修改jni/Android.mk
把里面的路径替换成你本机的路径：include D:/OpenCV-2.4.10-android-sdk/OpenCV-2.4.10-android-sdk/sdk/native/jni/OpenCV.mk

* 重新编译
cmd 到jni目录，执行ndk-build

* 导入libs
把OpenCV-2.4.2-android-sdk/sdk/native/libs/下的文件复制到libs/


# 强烈建议
* 在linux中编译jni，下载对应ndk和opencv2.4.10版本

* [OpenCV-2.4.10-android-sdk](https://github.com/c1rew/OpenCV-2.4.10-android-sdk)
我在这上传了对应的源码；

* 目前上传的jni是在Ubuntu14.04下编译通过的

# 其他
有任何问题请发issues，或者联系我cholyon@foxmail.com  or QQ: 121981859



