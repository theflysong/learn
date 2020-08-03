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

char escape(char ch)
{
	int i = 0, value = 0;
    switch (ch) {
        case 'a':case 'A': return '\a'; break;
        case 'b':case 'B': return '\b'; break;
        case 'f':case 'F': return '\f'; break;
        case 'n':case 'N': return '\n'; break;
        case 'r':case 'R': return '\r'; break;
        case 't':case 'T': return '\t'; break;
        case 'v':case 'V': return '\v'; break;
        case '\\': return '\\'; break;
        case '\'': return '\''; break;
        case '\"': return '\"'; break;
        case '?': return '\?'; break;
        case '0': return '\0'; break;
    }
}


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
		char c = stream.peek ();
		while (isdigit (c)) {
			stream.next();
			v += c;
			c = stream.peek ();
		}
		u.value=v; 
	}
	else if (opt == '^') {
		u.opt = unit::CHAR;
		string v = "";
		v += stream.next();
		if (v == "\\") {
			v = escape (stream.next());
		}
		u.value = v;
	}
	else if (opt == '"') {
		u.opt = unit::STRING; 
		string v;
		char c = stream.next();
		while (c != '"') {
			if (c == '\\') {
				c = escape (stream.next());
			}
			v += c;
			c = stream.next();
		}
		u.value=v;
	}
	else {
		u.opt = unit::UNKNOW;
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
				case unit::CHAR: {
					char* ch = new char[1];
					ch[0] = u.value[0];
					fout.write(ch,1);
					delete ch;
					break;
				}
				case unit::STRING: {
					fout.write(u.value.c_str(), u.value.length());
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

