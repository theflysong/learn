#include <bits/stdc++.h>
using namespace std;

struct Token {
	enum class Type {
		EMPTY = 0,
		DIGIT,
		OPERATOR,
		SEPARATOR
	};
	Type type;
	string value;
	Token makeToken(Token::Type type, string value) {
		return (Token){type, value};
	}
};

template<typename T>class Tree {
	struct Node {
		T data;
		vector<Node*> children;
		Node* parent;
		
		Node(T data, Node* parent) {
			this -> data = data;
			this -> parent = parent;
		}
		
		void addChild(T data) {
			children.push_back(new Node(data, this));
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
		
		vector<Pos> children(Pos parent) {
			vector<Pos> children;
			
			for (Node* node : parent.node -> children) {
				children.push_back(Pos::makePos(node));
			}
			
			return children;
		}
	
		Pos parent(Pos child) {
			return Pos::makePos(child.node -> parent);
		}
		
		void addChild(T data, Pos pos) {
			pos.node -> addChild(data);
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

class Lex {
	
};

class ASTTree {
	
};

int main(void) {
	return 0;
}

