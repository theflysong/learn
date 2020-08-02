#include <bits/stdc++.h>
using namespace std;

struct unit {
	enum opts {
		INT = 0, 
		CHAR,
		STRING,
		BYTE,
		LONG,
		SHORT,
		UNKNOW
	}opt;
	string value;
};

class cstream {
	vector<char> buf;
	int cnt;
public:
	cstream(ifstream& stream) {
		cnt = 0;
		while (!stream.eof ()) {
			buf.push_back (stream.get ());
		} 
	}
	char peek() {
		return buf[cnt];
	}
	char next() {
		return buf[cnt++];
	}
	bool end() {
		return cnt == buf.size();
	}
};

unit nextUnit(cstream& stream) {
	unit u;
	char opt = stream.next ();
	if (opt == '~') {
		u.opt = unit::BYTE;
		string v;
		char c = stream.peek();
		while (isdigit (c)) {
			stream.next();
			v += c;
			c = stream.peek ();
		}
		u.value=v; 
	}
	else if (opt == '!') {
		u.opt = unit::SHORT;
		string v;
		char c = stream.peek();
		while (isdigit (c)) {
			stream.next();
			v += c;
			c = stream.peek ();
		}
		u.value=v; 
	}
	else if (opt == '?') {
		u.opt = unit::INT;
		string v;
		char c = stream.peek();
		while (isdigit (c)) {
			stream.next();
			v += c;
			c = stream.peek ();
		}
		u.value=v; 
	}
	else if (opt == '&') {
		u.opt = unit::LONG;
		string v;
		char c = stream.peek();
		while (isdigit (c)) {
			stream.next();
			v += c;
			c = stream.peek ();
		}
		u.value=v; 
	}
	return u;
}

void IntToBin(int num, char* out) {
	out[0] = (char)(num & 0xFF);
	out[1] = (char)((num & 0xFF00) >> 8);
	out[2] = (char)((num & 0xFF0000) >> 16);
	out[3] = (char)((num >> 24) & 0xFF);
}

void ShortToBin(short num, char* out) {
	out[0] = (char) (num >> 8);
	out[1] = (char) (num);
}

void LongLongToBin(long long num, char* out) {
	int tmp=56;
	for(int i=7;i>=0;i--)
	{
		long long temp=num<<tmp;
		out[i]=temp>>56;
		tmp-=8;
	}
}

int main(int argc, char *argv[]) {
	if(argc<2) {
		printf ("Too few args");
		return -1;
	}
	string opt (argv[1]);
	if(opt=="-w") {
		if(argc<4) {
			printf ("Too few args");
			return -1;
		}
		ifstream fin (argv[2]);
		ofstream fout;fout.open (argv[3], ios::binary);  
		cstream ct (fin); 
		while (!ct.end ()) {
			unit u = nextUnit (ct);
			if(ct.end ()) {
				break;
			}
			switch (u.opt) {
				case unit::BYTE: {
					stringstream ss;
					ss<<u.value;
					int w;
					ss>>w;
					char* ch = new char[4];
					IntToBin(w,ch);
					fout.write(ch,1);
					delete ch;
					break;
				}
				case unit::SHORT: {
					stringstream ss;
					ss<<u.value;
					int w;
					ss>>w;
					char* ch = new char[2];
					ShortToBin(w,ch);
					fout.write(ch,2);
					delete ch;
					break;
				}
				case unit::INT: {
					stringstream ss;
					ss<<u.value;
					int w;
					ss>>w;
					char* ch = new char[4];
					IntToBin(w,ch);
					fout.write(ch,4);
					delete ch;
					break;
				}
				case unit::LONG: {
					stringstream ss;
					ss<<u.value;
					int w;
					ss>>w;
					char* ch = new char[8];
					LongLongToBin(w,ch);
					fout.write(ch,8);
					delete ch;
					break;
				}
				default: {
					printf ("Wrong code!");
					return -1;
				}
			}
		}
		fin.close ();
		fout.close ();
	}
	return 0;
}

