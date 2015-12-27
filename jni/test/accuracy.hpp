#ifndef EASYPR_ACCURACY_HPP
#define EASYPR_ACCURACY_HPP

#include <easypr.h>
#include <ctime>
#include <fstream>

namespace easypr {

namespace demo {

int accuracyTest(const char* test_path) {
  auto files = Utils::getFiles(test_path);

  CPlateRecognize pr;

  pr.LoadANN("resources/model/ann.xml");
  pr.LoadSVM("resources/model/svm.xml");

  // ����Debugģʽ
  pr.setDebug(false);

  pr.setLifemode(true);

  // ����Ҫ�����һ��ͼƬ������ж��ٳ���
  pr.setMaxPlates(4);

  int size = files.size();

  if (0 == size) {
    cout << "No File Found in general_test/native_test!" << endl;
    return 0;
  }

  cout << "Begin to test the easypr accuracy!" << endl;

  // �ܵĲ���ͼƬ����
  int count_all = 0;
  // �����ͼƬ����
  int count_err = 0;
  // δʶ���ͼƬ����
  int count_norecogin = 0;
  // not recognized pictures
  std::list<std::string> not_recognized_files;

  // �ܵ��ַ����
  float diff_all = 0;
  // ƽ���ַ����
  float diff_avg = 0;
  // ��ȫƥ���ʶ�����
  float match_count = 0;
  // ��ȫƥ���ʶ�������ռʶ��ͼƬ�еı���
  float match_rate = 0;

  // ��ʼ�ͽ���ʱ��
  time_t begin, end;
  time(&begin);

  for (int i = 0; i < size; i++) {
    string filepath = files[i].c_str();

    // EasyPR��ʼ�жϳ���
    Mat src = imread(filepath);

    // ����Ƿ�ͼ���ļ���ֱ�ӹ�ȥ
    if (!src.data) continue;

    cout << "------------------" << endl;

    // ��ȡ��ʵ�ĳ���
    string plateLicense = Utils::getFileName(filepath);
    cout << "ԭ��:" << plateLicense << endl;

    vector<string> plateVec;
    int result = pr.plateRecognize(src, plateVec, i);
    if (result == 0) {
      int num = plateVec.size();

      if (num == 0) {
        cout << "�޳���" << endl;
        if (plateLicense != "�޳���") {
          not_recognized_files.push_back(plateLicense);
          count_norecogin++;
        }
      } else if (num > 1) {
        // �೵��ʹ��diff��С���Ǹ���¼
        int mindiff = 10000;
        for (int j = 0; j < num; j++) {
          cout << plateVec[j] << " (" << j + 1 << ")" << endl;
          string colorplate = plateVec[j];

          // ����"����:��E7KU22"��ð�ź���ĳ��ƴ�С"
          vector<string> spilt_plate = Utils::splitString(colorplate, ':');

          int size = spilt_plate.size();
          if (size == 2 && spilt_plate[1] != "") {
            int diff = utils::levenshtein_distance(plateLicense,
                                                   spilt_plate[size - 1]);
            if (diff < mindiff) mindiff = diff;
          }
        }

        cout << "���:" << mindiff << "���ַ�" << endl;
        if (mindiff == 0) {
          // ��ȫƥ��
          match_count++;
        }
        diff_all = diff_all + mindiff;
      } else {
        // ������ֻ����һ��diff
        for (int j = 0; j < num; j++) {
          cout << plateVec[j] << endl;
          string colorplate = plateVec[j];

          // ����"����:��E7KU22"��ð�ź���ĳ��ƴ�С"
          vector<string> spilt_plate = Utils::splitString(colorplate, ':');

          int size = spilt_plate.size();
          if (size == 2 && spilt_plate[1] != "") {
            int diff = utils::levenshtein_distance(plateLicense,
                                                   spilt_plate[size - 1]);
            cout << "���:" << diff << "���ַ�" << endl;

            if (diff == 0) {
              // ��ȫƥ��
              match_count++;
            }
            diff_all = diff_all + diff;
          }
        }
      }
    } else {
      cout << "������:" << result << endl;
      count_err++;
    }
    count_all++;
  }
  time(&end);

  cout << "------------------" << endl;
  cout << "Easypr accuracy test end!" << endl;
  cout << "------------------" << endl;
  cout << endl;
  cout << "ͳ�Ʋ���:" << endl;
  cout << "��ͼƬ��:" << count_all << "��,  ";
  cout << "δʶ��ͼƬ:" << count_norecogin << "��,  ";

  float count_recogin = float(count_all - (count_err + count_norecogin));
  float count_rate = count_recogin / count_all;
  cout << "��λ��:" << count_rate * 100 << "%  " << endl;

  if (count_recogin > 0) {
    diff_avg = diff_all / count_recogin;
  }

  if (count_recogin > 0) {
    match_rate = match_count / count_recogin * 100;
  }

  cout << "ƽ���ַ����:" << diff_avg << "��,  ";
  cout << "��ȫƥ����:" << match_count << "��,  ";
  cout << "��ȫƥ����:" << match_rate << "%  " << endl;

  double seconds = difftime(end, begin);
  double avgsec = seconds / double(count_all);

  cout << "��ʱ��:" << seconds << "��,  ";
  cout << "ƽ��ִ��ʱ��:" << avgsec << "��" << endl;

  cout << "δʶ��ͼƬ:" << endl;

  for (auto it = not_recognized_files.begin(); it != not_recognized_files.end();
       ++it) {
    cout << *it << endl;
  }

  cout << endl;

  cout << "------------------" << endl;

  ofstream myfile("accuracy.txt", ios::app);
  if (myfile.is_open()) {
    time_t t = time(0);  // get time now
    struct tm* now = localtime(&t);
    char buf[80];

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", now);
    myfile << string(buf) << endl;

    myfile << "��ͼƬ��:" << count_all << "��,  ";
    myfile << "δʶ��ͼƬ:" << count_norecogin << "��,  ";
    myfile << "��λ��:" << count_rate * 100 << "%  " << endl;
    myfile << "ƽ���ַ����:" << diff_avg << "��,  ";
    myfile << "��ȫƥ����:" << match_count << "��,  ";
    myfile << "��ȫƥ����:" << match_rate << "%  " << endl;
    myfile << "��ʱ��:" << seconds << "��,  ";
    myfile << "ƽ��ִ��ʱ��:" << avgsec << "��" << endl;
    myfile.close();
  } else {
    cout << "Unable to open file";
  }
  return 0;
}
}
}

#endif  // EASYPR_ACCURACY_HPP
