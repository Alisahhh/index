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
void preQuery() {
  wordStore.clear();
  ifstream infile;
  infile.open("/home/alisa/Documents/index/index.dat");
  // printf("OK\n");
  int fileCount;
  infile >> fileCount;
  // cout << fileCount << endl;
  // int _fileCount = atoi(fileCount.c_str());
  for (int i = 1; i <= fileCount; i++) {
    string S;
    infile >> S;
    // cout << S << endl;
    // infile>>id;
    fileStore.push_back(S);
  }
  int wordCount;
  infile >> wordCount;
  // int wordCount = atoi(wordCount.c_str());
  // cout << _wordCount << endl;
  for (int i = 1; i <= wordCount; i++) {
    // cout << i << endl;
    int count;
    infile >> count;
    // int _count = atoi(count.c_str());
    // cout << _count << endl;
    wordStore.push_back(count);
  }
  for (int i = 1; i <= wordCount; i++) {
    string S;
    infile >> S;
    // cout << S << endl;
    for (int j = 1; j <= wordStore[i - 1]; j++) {
      int fileId, wordSum;
      infile >> fileId >> wordSum;
      // cout << fileId << " " << wordSum << endl;
      index1.push_back(SS{S, fileId, wordSum});
    }
  }
  infile.close();
}

int findAddressL(string S, int L, int R) {
  while (L < R) {
    int mid = (L + R) >> 1;
    // cout << index1[mid].word << endl;
    if (index1[mid].word < S)
      L = mid + 1;
    else
      R = mid;
  }
  if (index1[L].word == S)
    return L;
  else
    return -1;
}

int findAddressR(string S, int L, int R) {
  while (L <= R) {
    int mid = (L + R) >> 1;
    // cout << index1[mid].word << endl;
    if (index1[mid].word < S)
      L = mid + 1;
    else
      R = mid - 1;
  }
  if (index1[L].word == S)
    return L;
  else
    return -1;
}

void query() {
  /// cout << "ok!";
  string S;
  cin >> S;
  // cout << "ok!";
  int L = findAddressL(S, 0, index1.size() - 1);
  int R = findAddressR(S, 0, index1.size() - 1);
  // cout << L << " " << R;
  if (L == -1 || R == -1) {
    cout << "Are you kidding?";
    return;
  }
  for (int i = L; i <= R; i++) {
    cout << fileStore[index1[i].fileNum - 1] << " " << index1[i].count << endl;
  }
}

int main() {
  preQuery();
  query();
}
