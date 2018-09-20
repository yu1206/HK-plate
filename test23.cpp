
#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
using namespace std;


int test23(int argc, char *argv[])
{
	int classlabel = 10;
	string  labelpath = "I:\\calibration\\港澳车牌\\biaoji\\1\\0_text.txt";
	string  labelpathone = "I:/calibration/港澳车牌/biaoji/1/0_one.txt";
	//string imagepath = "I:/calibration/港澳车牌/biaoji/1/";

	map<string,vector<string>> str1;
	string nametxt = "I:/calibration/港澳车牌/biaoji/1.txt";
	fstream finRead1;
	finRead1.open(nametxt, ios::in);
	if (!finRead1.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	
	string line2;
	while (getline(finRead1, line2))
	{
		if (line2.empty())
		{
			break;
		}
		stringstream str_s(line2);
		string name; string HK; 
		str_s >> name >> HK ;
		str1[name].push_back(HK);
		
	}


	fstream finRead;
	finRead.open(labelpath, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	fstream finWrite;
	finWrite.open(labelpathone, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	string line;
	while (getline(finRead, line))
	{
		if (line.empty())
		{
			break;
		}
		fstream fin1;
		fin1.open(line);
		cout << line.c_str() << endl;
		if (!fin1.is_open())
		{
			cout << "error" << endl;
			cout << line.c_str() << endl;
			cout << "fin1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}
		string line1;
		while (getline(fin1, line1))
		{
			string name; int label; int x1, y1, x2, y2;
			stringstream str_s(line1);
			str_s >> name >> label >> x1 >> y1 >> x2 >> y2;
			if (label == classlabel)
			{
				int npos2 = name.find_last_of('.');
				string temp = name.substr(0, npos2);
				
				map<string, vector<string>>::iterator iter = str1.begin();
				for (; iter !=str1.end();iter++)
				{
					string s1 = iter->first;
					if (temp==iter->first)
					{
						vector<string>vs = iter->second;
						for (int i = 0; i < vs.size();i++)
						{
							finWrite << temp << " " << vs[i] << endl;
						}
						
					}
				}
			}

		}
		fin1.close();
	}
	finRead.close();
	finWrite.close();
	return 0;
}
