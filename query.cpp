#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <vector>
using namespace std;
struct SS {
  string word;
  int fileNum;
  int count;
};

int main() {
  vector<string> fileStore;
  bool flag = 0;
  string S;
  cin >> S;
  ifstream infile;
  infile.open("/home/alisa/Documents/index/index.dat");
  int fileCount;
  infile >> fileCount;
  for (int i = 1; i <= fileCount; i++) {
    string S;
    infile >> S;
    fileStore.push_back(S);
  }
  int wordCount;
  infile >> wordCount;
  int fileId, wordSum;
  for (int i = 1; i <= wordCount; i++) {
    string _S;
    infile >> _S;
    if (S == _S) {
      flag = 1;
      infile >> fileId >> wordSum;
      cout << fileStore[fileId - 1] << " " << wordSum << endl;
    } else {
      /*if (_S > S)
        break;*/
      infile >> fileId >> wordSum;
    }
  }
  if (!flag)
    cout << "Are you kidding?I can't find the word";
  infile.close();
}
