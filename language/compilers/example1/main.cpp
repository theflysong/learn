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
			children.push_back(new Node(data, this))
		}
		
		~Node() {
			for (Node* node : children) {
				delete node;
			}
		}
	};
public:
	struct pos {
		friend class Tree;
	private:
		Node* node;
	};
};

int main(void) {
	return 0;
}

