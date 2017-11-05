#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <omp.h>
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
void scan_file(const char *fileName, vector<SS> &sum, vector<string> &oppoMap,
               vector<string> &allFile, map<string, int> &fileStore,
               map<string, int> &wordStore, map<int, int> &sumInAFile,
               int &fileCount, int &wordCount) {
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
      //#pragma omp atomic
      oppoMap.push_back(S);
    }
    sumInAFile[wordStore[S]]++;
  }

  for (int i = 0; i < wordCount; i++)
    //#pragma omp atomic
    sum.push_back(SS{oppoMap[i], fileCount, sumInAFile[wordStore[oppoMap[i]]]});
  infile.close();
}

void scan_dir(const char *path, vector<SS> &sum, vector<string> &oppoMap,
              vector<string> &allFile, map<string, int> &fileStore,
              map<string, int> &wordStore, map<int, int> &sumInAFile,
              int &fileCount, int &wordCount) {
  // thread p[4];
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
      scan_file(_fullPath.c_str(), sum, oppoMap, allFile, fileStore, wordStore,
                sumInAFile, wordCount, fileCount);
    } else {
      if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
        continue;
      scan_dir(_fullPath.c_str(), sum, oppoMap, allFile, fileStore, wordStore,
               sumInAFile, wordCount, fileCount);
    }
  }
}

bool cmp(SS a, SS b) { return a.count > b.count; }

/*bool cmp(SS a, SS b) {
  if (a.word == b.word)
    return a.count > b.count;
  return a.word < b.word;
}*/

void printIndex(vector<SS> sum, vector<string> allFile) {
  ofstream outfile;
  outfile.open("index.dat");
  outfile << allFile.size() << endl;
  for (int i = 0; i < allFile.size(); i++)
    outfile << allFile[i] << endl;
  sort(sum.begin(), sum.end(), cmp);
  int tmp = sum.size();
  outfile << tmp << endl;
  for (int i = 0; i < tmp; i++)
    outfile << sum[i].word << " " << sum[i].fileNum << " " << sum[i].count
            << endl;
  outfile.close();
}

int main() {
  string path;
  vector<SS> sum;
  vector<string> oppoMap;
  vector<string> allFile;     // 每个单词在每个文件里的数量
  map<string, int> fileStore; //储存文件编号
  map<string, int> wordStore; //确定单词是否被读以及赋予编号
  map<int, int> sumInAFile;
  int wordCount = 0, fileCount = 0; //单词总数，文件总数
  cin >> path;
  // cout << path;
  scan_dir(path.c_str(), sum, oppoMap, allFile, fileStore, wordStore,
           sumInAFile, wordCount, fileCount);
  // scan_file("/home/alisa/Documents/code/");
  /*/cout << "done" << endl;
  cout << "Totle Time : " << (double)clock() / CLOCKS_PER_SEC << "s" << endl;*/
  printIndex(sum, allFile);
  cout << "done" << endl;
  cout << "Totle Time : " << (double)clock() / CLOCKS_PER_SEC << "s" << endl;
}
