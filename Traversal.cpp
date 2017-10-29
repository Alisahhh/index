#include<cstdio>
#include<iostream>
#include<cstring>
#include<io.h>
#include<map>
#include<fstream>
#include<vector>
void Travel(string Path);
void Read(string Path);
void MakeString(int id,int S);
int cnt;//文件总数
map<string,int>mp1;//给文件标号

int main()
{
	using namespace std;
	string FilePath;
	cin >> FilePath;
	Travel(FilePath);
	MakeIndex();

}

void Travel(string Path)
{
	_ finddata_t File;
	string NowPath = Path + "/*";
	long Handle = _findfirst(NowPath.c_str(),&File);
	if(Handle == -1) 
	{
		cout<<"No File"<<endl;
		return;
	}
	while(!_findnext(handle,&File))
	{
		if(File.atteib == _A_SUBDIR)//folder
		{
			if(strcmp(File.name,"..") != 0&&strcmp(File.name,".")!=0)
			{
				Travel(Path+'l'+File.name);
			}
		}
		else
		{
			Read(Path+'l'+File.name);
		}
	}
	_findclose(handle);
}

void Read(string File)
{
	++cnt;
	mp1[File] = cnt;
	ifstream infile;
	infile.open(File,ios::in);
	while(!infile.eof())
	{	
		string tmp;
		infile.getline(tmp,'\n');
		MakeString(cnt,tmp);
	}
}

void MakeString(int id,string S)
{
	int Begin = 0;
	while(S.find(" ",Begin) != string::npos )
	{
		int tmp = S.find(" ",Begin);
		string Str = S.substr(Begin + 1,tmp - Begin - 1);
		if(!mp2[Str])
		{
			StringStore[++cntS] = Str;
			vector<string>Str;
		}
		mp2[Str] ++;
		Str.push_back(id);
		Begin = tmp;
	}
}

void MakeIndex()
{
	sort(StringStore+1,StringStore+cntS);
	for(int i = 1;i <= cntS;i ++)
	{
		printf("%s ",StringStore[i]);
		for(int j = 0;j < StringStore[i].size();j ++)
		{
			cout<<StringStore[i]<<" ";
		}
		printf("\n");
	}
}
