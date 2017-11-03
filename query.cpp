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
vector<string> fileStore;
vector<SS> index1;
vector<int> wordStore;
map<string, int> wordId;
int _wordCount;
void preQuery() {
  string S;
  cin >> S;
  wordStore.clear();
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
  for (int i = 1; i <= wordCount; i++) {
    int count;
    infile >> count;
    wordStore.push_back(count);
  }
  for (int i = 1; i <= wordCount; i++) {
    string _S;
    infile >> _S;
    if (S == _S) {
      for (int j = 1; j <= wordStore[i - 1]; j++) {
        int fileId, wordSum;
        infile >> fileId >> wordSum;
        cout << fileStore[fileId - 1] << " " << wordSum << endl;
      }
      return;
    } else {
      for (int j = 1; j <= wordStore[i - 1]; j++) {
        int fileId, wordSum;
        infile >> fileId >> wordSum;
      }
    }
  }
  cout << "Are you kidding?I can't find the word";
  infile.close();
}

int main() { preQuery(); }
