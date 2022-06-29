#include <Windows.h>
#include <string>
#include<cctype>
#include <cmath>

using namespace std;

string ConvertToString(int num) {
	string str = to_string(num);
	return str;
}
string ConvertToString(char letter) {
	string str = to_string(letter);
	return str;
}
void PositionXY(int x, int y) {
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x,y };
	SetConsoleCursorPosition(hconsole, coord);

}

string ConvertToupper(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
	return s;
}
char ConvertToupper(char s) {
	return toupper(s);
}
char ConvertTolower(char s) {
	return tolower(s);
}
int ABS(int value) {
	return abs(value);
}
bool UpperCase(char C) {
	return (C > 64 && C < 91);
}
bool LowerCase(char C) {
	return (C > 96 && C < 123);
}
/*
* string* splitMessagebyspace(string message) {
	string splitstr[3];
	for (int i = 0; i < 3; i++) {
		splitstr[i] = message.substr(0, message.find(" "));
		message.erase(0, message.substr(0, message.find(" ")).length() + 1);
	}
	return splitstr;
}
*/
