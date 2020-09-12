#include <bits/stdc++.h>
using namespace std;

struct Token {
	enum class Type {
		EMPTY = 0,
		DIGIT,
		OPERATOR,
		BUCKET
	};
	Type type;
	string value;
	static Token makeToken(Token::Type type, string value) {
		return (Token){type, value};
	}
}EMPTY;

template<typename T>class Tree {
	struct Node {
		T data;
		vector<Node*> children;
		Node* parent;
		
		Node(T data, Node* parent) {
			this -> data = data;
			this -> parent = parent;
		}
		
		Node() {
			
		}
		
		Node* addChild(T data) {
			return addChild(new Node(data, this));
		}
		
		Node* addChild(Node* node) {
			children.push_back(node);
			node -> parent = this;
			return node;
		}
		
		~Node() {
			for (Node* node : children) {
				delete node;
			}
		}
	};
	Node* root;
public:
	struct Pos {
		friend class Tree;
		
		T get() {
			return node -> data;
		}
		
		vector<Pos> children() {
			vector<Pos> children;
			
			for (Node* node : this -> node -> children) {
				children.push_back(Pos::makePos(node));
			}
			
			return children;
		}
	
		Pos parent() {
			return Pos::makePos(this -> node -> parent);
		}
		
		Pos addChild(T data) {
			return Pos::makePos(this -> node -> addChild(data));
		}
	private:
		static Pos makePos(Node* node) {
			Pos pos;
			pos.node = node;
			return pos;
		}
		Node* node;
	};
	Pos begin() {
		return Pos::makePos(root); 
	}
	Tree() {
		root = new Node;
	}
};

class Lexer {
	vector<Token> tokens;
	Token get(string buffer) {
		if (isdigit(buffer[0])) {
			int cnt = 0;
			while (isdigit(buffer[cnt ++]));
			return Token::makeToken(Token::Type::DIGIT, buffer.substr(0, cnt - 1));
		}
		if (buffer[0] == ' ' || buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\t') {
			return Token::makeToken(Token::Type::EMPTY, " ");
		}
		if (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/') {
			return Token::makeToken(Token::Type::OPERATOR, buffer.substr(0, 1));
		}
		if (buffer[0] == '(' || buffer[0] == ')') {
			return Token::makeToken(Token::Type::BUCKET, buffer.substr(0, 1));
		}
		return EMPTY;
	}
public:
	void lex(istream& in) {
		string str;
		while (! in.eof()) {
			str += in.get();
		}
		int pos = 0;
		while (pos < str.length() - 1) {
			Token token = get(str.substr(pos));
			pos += token.value.length();
			if (token.type != Token::Type::EMPTY) {
				tokens.push_back(token);
			}
		}
	}
	friend class ASTTree;
};

class ASTTree {
	void printTree(vector<Tree<Token>::Pos> children, int lvl, ostream& out) {
		for (auto child : children) {
			for (register int i = 0 ; i < lvl ; i ++) {
				out << "  ";
			}
			out << child.get().value << endl;
			printTree(child.children(), lvl + 1, out);
		}
	}
	Tree<Token> tokens;
public:
	void parse(Lexer& lexer) {
		vector<Token> toks(lexer.tokens);
		reverse(toks.begin(), toks.end());
		auto pos = tokens.begin();
		for (int i = 0 ; i < toks.size() ; i ++) {
			Token token = toks[i];
			if (token.type == Token::Type::DIGIT) {
				Token op = toks[++ i];
				if (op.type == Token::Type::OPERATOR) {
					if (toks[++ i].type == Token::Type::DIGIT) {
						auto opt = pos.addChild(op);
						opt.addChild(token);
						opt.addChild(toks[i]);
					}
				}
			}
		}
	}
	void printTree(ostream& out) {
		out << "root" << endl;
		printTree(tokens.begin().children(), 1, out);
	}
	friend class Compiler;
};

class Compiler {
public:
	void compile(ASTTree ast, ostream& out) {
		auto pos = ast.tokens.begin();
		auto opt = pos.children()[0];
		Token op = opt.get();
		if (op.type == Token::Type::OPERATOR) {
			out << op.value << " ";
			auto args = opt.children();
			if (args.size() == 2) {
				for (auto parg : args) {
					Token arg = parg.get();
					if (arg.type == Token::Type::DIGIT) {
						out << arg.value << " ";
					}
				}
			}
		}
	}
};

int main(int argv, char **argc) {
	string opt = argc[2];
	if (opt == "-o") {
		ifstream source(argc[1]);
		ofstream output(argc[3]);
		Lexer lexer;
		ASTTree ast;
		Compiler compiler;
		lexer.lex(source);
		ast.parse(lexer);
		ast.printTree(cout);
		compiler.compile(ast, output);
	}
	else if (opt == "-p") {
		ifstream source(argc[1]);
		ofstream output(argc[3]);
		Lexer lexer;
		ASTTree ast;
		Compiler compiler;
		lexer.lex(source);
		ast.parse(lexer);
		ast.printTree(output);
	}
	else {
		cerr << "Unknow Command " << opt << " find";
		return -1;
	}
	return 0;
}

