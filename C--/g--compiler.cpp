#include <bits/stdc++.h>
using namespace std;
void imax(int &a, int b){
	a=max(a, b);
}
void imin(int &a, int b){
	a=min(a, b);
}
void lmax(long long &a, long long b){
	a=max(a, b);
}
void lmin(long long &a, long long b){
	a=min(a, b);
}
/*
	WARNING: I'm using strange bracket style!
*/
vector <string> code, comments;
vector <int> tabs;
string s;
int T=0;
string removeTab(string s){
	string out;
	for (int i=(s[0]!=9)?4:1; i<s.size(); i++)
		out+=s[i];
	return out;
}
bool isTab(string s){
	if (s.size() && s[0]==9) return true;
	if (s.size()>=4 && s[0]==' ' && s[1]==' ' && s[2]==' ' && s[3]==' ') return true;
	return false;
}
void removeComments(){
	bool underComment=false;
	for (int i=0; i<code.size(); i++)
		{
		comments.push_back("");
		for (int j=1; j<code[i].size(); j++)
			{
			if (code[i][j-1]=='/' && code[i][j]=='/')
				{
				for (int g=j-1; g<code[i].size(); g++)
					comments.back().push_back(code[i][g]);
				code[i]=code[i].substr(0, j-1);
				break;
				}
			if (code[i][j-1]=='/' && code[i][j]=='*')
				{
				for (int g=j-1; g<code[i].size(); g++)
					comments.back().push_back(code[i][g]);
				code[i]=code[i].substr(0, j-1);
				underComment=true;
				break;
				}
			if (code[i][j-1]=='*' && code[i][j]=='/')
				{
				comments[i-1]+="*/", comments[i]+="//";
				for (int g=0; g<=j; g++)
					comments.back().push_back(code[i][g]);
				code[i]=code[i].substr(j+1, code[i].size()-j-1);
				underComment=false;
				break;
				}
			}
		if (underComment && comments[i].size()==0)
			comments[i]=code[i], code[i]="";
		}
}
string gmmMagic(string s){
	bool isForGmm=false;
	for (int i=1; i<s.size(); i++)
		if (s[i-1]=='<' && s[i]=='-')
			isForGmm=true;
	if (isForGmm)
		{
		string arg1, arg2, arg3;
		int x=4, y=0;
		while (s[x]!=' ' && s[x]!='<')
			arg1+=s[x++];
		for (int i=1; i<s.size(); i++)
			if (s[i-1]=='.' && s[i]=='.')
				y=i;
		x=y+1;
		while (s[x]!='}')
			arg3+=s[x++];
		x=y-2;
		while (s[x]!='{')
			arg2=s[x--]+arg2;
		return "for (int "+arg1+"="+arg2+"; "+arg1+"<="+arg3+"; "+arg1+"++)";
		}
	return s;
}
string clear(string s){
	for (int i=1; i<s.size(); i++)
		if (s[i-1]=='*' && s[i]=='/')
			swap(s[i-1], s[i]);
	return s;
}
int main()
	{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout<<"/*\n";
	cout<<"    Code was written in c-- and compiled to c++\n";
	cout<<"    Github link\n";
	cout<<"    WARNING: Code has strange bracket style!\n";
	cout<<"*/\n";
	cout<<"//Original code (with */ replaced with /*):\n";
	cout<<"/*\n";
	while (getline(cin, s))
		{
		cout<<clear(s)<<"\n";
		while (isTab(s))
			s=removeTab(s), T++;
		s.pop_back(), code.push_back(s), tabs.push_back(T), T=0;
		}
	cout<<"*/\n";
	removeComments();
	for (auto i: comments)
		cout<<i<<"\n";
	for (int i=0; i<code.size(); i++)
		{
		code[i]=gmmMagic(code[i]);
		for (int j=0; j<tabs[i]; j++)
			cout<<(char(9));
		cout<<code[i];
		if (code[i]!="")
			{
			if (tabs[i+1]-tabs[i]<=0 && code[i][0]!='#')
				cout<<";";
			for (int j=0; j<tabs[i+1]-tabs[i]; j++)
				cout<<"{";
			for (int j=0; j<tabs[i]-tabs[i+1]; j++)
				cout<<"}";
			}
		cout<<comments[i];
		cout<<"\n";
		}
	return 0;
	}
