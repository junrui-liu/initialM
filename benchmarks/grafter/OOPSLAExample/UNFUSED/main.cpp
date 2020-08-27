#include <assert.h>
#include <chrono>
#include <stddef.h>
#include <stdio.h>

#define __tree_structure__ __attribute__((annotate("tf_tree")))
#define __tree_child__ __attribute__((annotate("tf_child")))
#define __tree_traversal__ __attribute__((annotate("tf_fuse")))
#define _Bool bool

enum NodeType {
	VAL_NODE,
	NULL_NODE
};

class __tree_structure__ Node {
	public: 
		NodeType Type;
		virtual bool is_leaf() {}
		virtual void insert(int Key, bool ValidCall) {}
		__tree_traversal__ virtual void f1() {}
		__tree_traversal__ virtual void f2() {}
};

class __tree_structure__ NullNode: public Node {
	virtual bool is_leaf() {}
	virtual void insert(int Key, bool ValidCall) {}
	__tree_traversal__ void f1() { return; }
	__tree_traversal__ void f2() { return; }
};

class __tree_structure__ ValueNode: public Node {
	public: 
		int v, x, y;
		__tree_child__ Node * Left, * Right;
		bool is_leaf() { return (Left -> Type == NULL_NODE) && (Right -> Type == NULL_NODE); }
		void insert(int NewValue, bool ValidCall) {
			if (ValidCall == false)
				return;

			if (NewValue < v && Left -> Type == NULL_NODE) {
				delete Left;
				Left = new ValueNode();
				ValueNode * const Left_ = static_cast < ValueNode * > (Left);
				Left_ -> v = NewValue;
				Left_ -> Type = VAL_NODE;

				Left_ -> Left = new NullNode();
				Left_ -> Left -> Type = NULL_NODE;

				Left_ -> Right = new NullNode();
				Left_ -> Right -> Type = NULL_NODE;

				return;
			}
			if (NewValue >= v && Right -> Type == NULL_NODE) {
				delete Right;
				Right = new ValueNode();
				ValueNode * const Right_ = static_cast < ValueNode * > (Right);
				Right_ -> v = NewValue;
				Right_ -> Type = VAL_NODE;

				Right_ -> Left = new NullNode();
				Right_ -> Left -> Type = NULL_NODE;

				Right_ -> Right = new NullNode();
				Right_ -> Right -> Type = NULL_NODE;
				return;
			}

			Left -> insert(NewValue, NewValue < v);
			Right -> insert(NewValue, NewValue >= v);
		}
		__tree_traversal__ void f1() {
			Left -> f1();
			Right -> f1();
			if (is_leaf()) {
				v = 1;
			} else {
				v = static_cast < ValueNode * > (Left) -> v + static_cast < ValueNode * > (Right) -> v;
			}
			return;
		}
		__tree_traversal__ void f2() {
			if (!is_leaf()) {
				x = v;
				static_cast < ValueNode * > (Left) -> x = x + 2;
			}
			y = v * 2;
			Left -> f2();
			Right -> f2();
		}
};

Node * createTree() {
	Node * Root = new ValueNode();
	ValueNode * const Root_ = static_cast < ValueNode * > (Root);
	Root_ -> v = 5;
	Root_ -> Type = VAL_NODE;

	Root_ -> Left = new NullNode();
	Root_ -> Left -> Type = NULL_NODE;

	Root_ -> Right = new NullNode();
	Root_ -> Right -> Type = NULL_NODE;

	return Root;
}

int main() {
	Node * Root = createTree();
	Root -> insert(4, true);
	Root -> insert(2, true);
	Root -> insert(1, true);
	Root -> insert(3, true);
	Root -> insert(6, true);
	Root -> insert(5, true);
	Root -> insert(7, true);
}