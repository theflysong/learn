#include <bits/stdc++.h>
using namespace std;

struct Token {
	enum class Type {
		EMPTY = 0,
		DIGIT,
		OPERATOR,
		BRACKET
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
		
		void addTree(Tree<T>* tree) {
			vector<Node*> children = tree -> root -> children;
			
			for (Node* child : children) {
				this -> node -> addChild(child);
			}
			
			tree -> root -> children.clear();
			delete tree;
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
	~Tree() {
		delete root;
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
			return Token::makeToken(Token::Type::BRACKET, buffer.substr(0, 1));
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
	class ExpTreeGenerator {
		static Token nextToken(vector<Token> tokens) {
			static int pos = 0;
			return tokens[pos ++];
		}
	public:
		static Tree<Token>* genPrefixExpTree(vector<Token> tokens) {
			auto tree = new Tree<Token>;
			
			Token token = nextToken(tokens);
			
			auto pos = tree -> begin().addChild(token);
			
			if (token.type == Token::Type::OPERATOR) {
				pos.addTree(genPrefixExpTree(tokens));
				pos.addTree(genPrefixExpTree(tokens));
			}
			
			return tree;
		}
		static inline Tree<Token>* genInfixExpTree(vector<Token> tokens) {
			reverse(tokens.begin(), tokens.end());
			vector<Token> exps;
			stack<Token> args;
			stack<Token> opts;
			for (Token token : tokens) {
				switch (token.type) {
					case Token::Type::DIGIT: {
						args.push(token);
						break;
					}
					case Token::Type::OPERATOR: {
						if (opts.size() == 0 || opts.top().type == Token::Type::BRACKET || 
							(((opts.top().value == "+") || (opts.top().value == "-")) ^ ((token.value == "*") || (token.value == "/")))) {
							opts.push(token);
							break;
						}
						Token opt = opts.top();
						opts.pop();
						opts.push(token);
						opts.push(opt);
						break;
					}
					case Token::Type::BRACKET: {
						if (token.value == ")") {
							opts.push(token);
						}
						else {
							while (opts.top().value != ")") {
								args.push(opts.top());
								opts.pop();
							}
							opts.pop();
						}
						break;
					}
				}
			}
			while (! opts.empty()) {
				args.push(opts.top());
				opts.pop();
			}
			
			while (! args.empty()) {
				exps.push_back(args.top());
				args.pop();
			}
			
			return genPrefixExpTree(exps);
		}
	};
	Tree<Token>* tokens;
public:
	void parse(Lexer& lexer) {
		vector<Token> toks(lexer.tokens);
		tokens -> begin().addTree(ExpTreeGenerator::genInfixExpTree(toks));
	}
	void printTree(ostream& out) {
		out << "root" << endl;
		printTree(tokens -> begin().children(), 1, out);
	}
	ASTTree() {
		tokens = new Tree<Token>;
	}
	~ASTTree() {
		delete tokens;
	}
	friend class Compiler;
};

class Compiler {
	class ExpGen {
	public:
		static string genPrefixExp(Tree<Token>::Pos start) {
			string result = start.get().value + " ";
			
			for (auto pos : start.children()) {
				result += genPrefixExp(pos);
			}
			
			return result;
		}
	};
public:
	void compile(ASTTree &ast, ostream& out) {
		string result = "";
		result = ExpGen::genPrefixExp(ast.tokens -> begin().children()[0]);
		out << result;
	}
};

int main(int argv, char **argc) {
	string opt = argc[2];
	if (opt == "-o") {
		ifstream source(argc[1]);
		ofstream output(argc[3]);
		Lexer* lexer = new Lexer;
		ASTTree* ast = new ASTTree;
		Compiler* compiler = new Compiler;
		lexer -> lex(source);
		ast -> parse(*lexer);
		ast -> printTree(cout);
	    compiler -> compile(*ast, output);
	    delete lexer;
	    delete ast;
	    delete compiler;
	}
	else if (opt == "-p") {
		ifstream source(argc[1]);
		ofstream output(argc[3]);
		Lexer* lexer = new Lexer;
		ASTTree* ast = new ASTTree;
		Compiler* compiler = new Compiler;
		lexer -> lex(source);
		ast -> parse(*lexer);
		ast -> printTree(output);
	    delete lexer;
	    delete ast;
	    delete compiler;
	}
	else {
		cerr << "Unknow Command " << opt << " find";
		return -1;
	}
	return 0;
}
