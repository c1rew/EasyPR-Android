
#include <easypr.h>
#include <ctime>
#include <fstream>

using namespace easypr;

int main(int argc, char **argv)
{
    CPlateRecognize pr;

    pr.LoadANN("/tmp/ann.xml");
    pr.LoadSVM("/tmp/svm.xml");

    // 设置Debug模式
    pr.setDebug(false);

    pr.setLifemode(true);


    Mat src = imread("/tmp/1.jpg");

    //pr.setGaussianBlurSize(5);
    //pr.setMorphSizeWidth(17);

    //pr.setVerifyMin(3);
    //pr.setVerifyMax(20);

    pr.setMaxPlates(3);

    //pr.setLiuDingSize(7);
    //pr.setColorThreshold(150);

    vector<string> plateVec;

    int count = pr.plateRecognize(src, plateVec);
    string str = "";

    int num = plateVec.size();

    if (count == 0 && num != 0) {
        str = plateVec[0];
    }
    cout << "plate: " << str << endl;

    return 0;
}

