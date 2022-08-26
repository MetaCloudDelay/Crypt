//SimmilarVernam
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;
ifstream fin;
ofstream fout;
bool isenc;
void init(int argc,char *argv[]);
string ky;
int lenky;
void kygen(int argc,char *argv[]);
void doit(void);
int main(int argc,char *argv[]) {
	init(argc,argv);
	kygen(argc,argv);
	if (argc <= 2) {
		if (isenc) printf("Encrypting...\n");
		else printf("Decrypting...\n");
	}
	doit();
	if (argc <= 2) printf("Done.\n");
	fin.close();fout.close();
	return 0;
}
void init(int argc,char *argv[]) {
	string fname,tmpfname;
	if (argc > 2) fname = argv[1];
	else {
		printf("Input File Name: ");
		getline(cin,fname);
	}
	fin.open(fname.c_str(),ios::in);
	if (fname.size() > 4 && fname.substr(fname.size() - 4,4) == ".enc") {
		tmpfname = fname.substr(0,fname.size() - 4);
		fname = tmpfname;
		isenc = false;
	} else {
		fname += ".enc";
		isenc = true;
	}
	fout.open(fname.c_str(),ios::out);
	return;
}
void kygen(int argc,char *argv[]) {
	string kyf;
	if (argc > 2) {
		kyf = argv[2];
	} else {
		printf("Input File.ky: ");
		getline(cin,kyf);
	}
	ifstream getky(kyf.c_str());
	getline(getky,ky);
	lenky = ky.size();
	getky.close();
	return;
}
void doit(void) {
	if (isenc) {
		int i = 0,lenstr;
		string str;
		while (getline(fin,str)) {
			lenstr = str.size();
			for (int j = 0;j < lenstr;j ++) {
				fout << int (str[j] ^ ky[i]) << " ";
				++ i;
				if (i >= lenky) i = 0;
			}
			fout << "-1 ";
		}
		return;
	} else {
		int i = 0,num;
		while (fin >> num) {
			if (num == -1) fout << endl;
			else {
				fout << char (num ^ ky[i]);
				++ i;
				if (i >= lenky) i = 0;
			}
		}
		return;
	}
	return;
}

