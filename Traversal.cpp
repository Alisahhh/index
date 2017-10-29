#include<cstdio>
#include<iostream>
#include<cstring>
#include<io.h>

void Travel(string Path);
void Read(string Path);
int main()
{
	using namespace std;
	string FilePath;
	cin >> FilePath;
	Travel(FilePath);

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
	
}
