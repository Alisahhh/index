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
#include <vector>
using namespace std;

struct SS {
  string word;
  int wordId;
};
vector<vector<int>> inWhichFile;
vector<SS> word;            // 每个单词所对应的编号
map<string, int> fileStore; //储存文件编号
map<string, int> wordStore; //确定单词是否被读以及赋予编号
int wordCount, fileCount;   //单词总数，文件总数

void makeWord(string S, int fileCount) {
  if (!wordStore[S]) {
    wordCount++;
    wordStore[S] = wordCount;
    word.push_back(SS{S, wordCount});
  }
  // cout << S << " " << fileCount << " " << wordCount << endl;
  // inWhichFile[wordStore[S]].push_back(fileCount);
}

void scan_file(const char *fileName) {
  fileCount++;
  string _filename(fileName);
  cout << _filename << endl;
  fileStore[_filename] = fileCount;
  cout << fileCount << endl;
  ifstream infile;
  infile.open(fileName);
  printf("OK\n");
  string S;
  while (infile >> S) {
    cout << S << endl;
    makeWord(S, fileCount);
  }
  //}
  infile.close();
  for (int i = 0; i < word.size(); i++) {
    SS tmp = word[i];
    cout << tmp.word << " " << tmp.wordId;
  }
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
      cout << ent->d_name << endl;
      scan_file(_fullPath.c_str());
    } else {
      if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
        continue;
      scan_dir(_fullPath.c_str());
    }
  }
  cout << fileCount << endl;
}

bool cmp(SS a, SS b) {
  if (a.word < b.word)
    return 1;
}

void printIndex() {
  sort(word.begin(), word.end(), cmp);
  for (int i = 1; i <= wordCount; i++) {
    cout << word[i].word << " ";
    for (int j = 0; j < inWhichFile.size(); j++) {
      cout << inWhichFile[i][j] << " ";
    }
    cout << "\n";
  }
}

int main() {
  string path;
  cin >> path;
  cout << path;
  scan_dir(path.c_str());
  // scan_dir("/home/alisa/Documents/code/tmp");
  // printIndex();
}
