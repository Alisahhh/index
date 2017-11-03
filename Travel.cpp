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
vector<SS> sum;
vector<string> oppoMap;
vector<string> allFile;     // 每个单词在每个文件里的数量
map<string, int> fileStore; //储存文件编号
map<string, int> wordStore; //确定单词是否被读以及赋予编号
map<int, int> sumInAFile;
int wordCount, fileCount; //单词总数，文件总数
void scan_file(const char *fileName) {
  fileCount++;
  sumInAFile.clear();
  wordStore.clear();
  oppoMap.clear();
  wordCount = 0;
  string _filename(fileName);
  fileStore[_filename] = fileCount;
  allFile.push_back(_filename);
  ifstream infile;
  infile.open(fileName);
  string S;
  while (infile >> S) {
    if (!wordStore[S]) {
      wordStore[S] = ++wordCount;
      oppoMap.push_back(S);
    }
    sumInAFile[wordStore[S]]++;
    // sum.push_back(SS{S, fileCount, sumInAFile[wordStore[S]]});
  }
  for (int i = 0; i < wordCount; i++)
    sum.push_back(SS{oppoMap[i], fileCount, sumInAFile[wordStore[oppoMap[i]]]});
  infile.close();
}

void scan_dir(const char *path) {
  struct dirent *ent = NULL;
  DIR *pDir;
  pDir = opendir(path);
  if (pDir == NULL)
    return;
  while (NULL != (ent = readdir(pDir))) {
    string _path(path);
    string _dirName(ent->d_name);
    string _fullPath = _path + "/" + _dirName;
    if (ent->d_type == 8) {
      scan_file(_fullPath.c_str());
    } else {
      if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
        continue;
      scan_dir(_fullPath.c_str());
    }
  }
}

bool cmp(SS a, SS b) {
  if (a.word == b.word)
    return a.count > b.count;
  return a.word < b.word;
}

void printIndex() {
  ofstream outfile;
  outfile.open("index.dat");
  wordStore.clear();
  sumInAFile.clear();
  wordCount = 0;
  outfile << fileCount << endl;
  for (int i = 0; i < allFile.size(); i++)
    outfile << allFile[i] << endl;
  sort(sum.begin(), sum.end(), cmp);
  for (int i = 0; i < sum.size(); i++) {
    if (!wordStore[sum[i].word]) {
      wordCount++;
      wordStore[sum[i].word] = 1;
    }
    sumInAFile[wordCount]++;
  }
  outfile << wordCount << endl;
  for (int i = 1; i <= wordCount; i++)
    outfile << sumInAFile[i] << endl;
  // outfile << " ";
  wordStore.clear();
  for (int i = 0; i < sum.size(); i++) {
    if (!wordStore[sum[i].word]) {
      outfile << endl;
      wordStore[sum[i].word] = 1;
      outfile << sum[i].word << endl;
    }
    outfile << sum[i].fileNum << endl << sum[i].count << endl;
  }
  outfile.close();
}

int main() {
  string path;
  cin >> path;
  // cout << path;
  scan_dir(path.c_str());
  // scan_file("/home/alisa/Documents/code/");
  cout << "done" << endl;
  cout << "Totle Time : " << (double)clock() / CLOCKS_PER_SEC << "s" << endl;
  printIndex();
}
