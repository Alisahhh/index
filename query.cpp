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
  wordStore.clear();
  ifstream infile;
  infile.open("/home/alisa/Documents/index/index.dat");
  // printf("OK\n");
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
    string S;
    infile >> S;
    wordId[S] = ++_wordCount;
    // cout << S << endl;
    for (int j = 1; j <= wordStore[i - 1]; j++) {
      int fileId, wordSum;
      infile >> fileId >> wordSum;
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

void query() {
  string S;
  cin >> S;
  int L = findAddressL(S, 0, index1.size() - 1);
  if (L == -1) {
    cout << "Are you kidding?";
    return;
  }
  for (int i = L; i <= L + wordStore[wordId[S] - 1] - 1; i++) {
    cout << fileStore[index1[i].fileNum - 1] << " " << index1[i].count << endl;
  }
}

int main() {
  preQuery();
  query();
}
