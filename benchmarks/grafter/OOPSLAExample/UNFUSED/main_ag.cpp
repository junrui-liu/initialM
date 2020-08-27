#include <assert.h>
#include <chrono>
#include <stddef.h>
#include <stdio.h>

#define __tree_structure__ __attribute__((annotate("tf_tree")))
#define __tree_child__ __attribute__((annotate("tf_child")))
#define __tree_traversal__ __attribute__((annotate("tf_fuse")))

enum NodeType {
	VAL_NODE,
	NULL_NODE
};

class __tree_structure__ Node {
	public: 
		NodeType Type;
		__tree_traversal__ virtual void f1() {}
		__tree_traversal__ virtual void f2() {}
};

class __tree_structure__ NullNode: public Node {
	__tree_traversal__ void f1() { return; }
	__tree_traversal__ void f2() { return; }
};

class __tree_structure__ ValueNode: public Node {
	public: 
		int v, x, y;
		__tree_child__ Node * Left, * Right;
		__tree_traversal__ void f1() {
			bool is_leaf = (Left -> Type == NULL_NODE) && (Right -> Type == NULL_NODE);
			Left -> f1();
			Right -> f1();
			if (is_leaf) {
				v = 1;
			} else {
				v = static_cast < ValueNode * > (Left) -> v + static_cast < ValueNode * > (Right) -> v;
			}
			return;
		}
		__tree_traversal__ void f2() {
			// left part
			if (Left -> Type == VAL_NODE) {
				ValueNode * LL = static_cast < ValueNode * > (Left);
				bool left_is_leaf = (LL -> Left -> Type == NULL_NODE) && (LL -> Right -> Type == NULL_NODE);
				if (left_is_leaf) {
					LL -> x = v + 2;
				} else {
					LL -> x = LL -> v;
				}
				LL -> y = LL -> v * 2;
			}
			

			// right part
			if (Right -> Type == VAL_NODE) {
				ValueNode * RR = static_cast < ValueNode * > (Right);
				bool right_is_leaf = (RR -> Left -> Type == NULL_NODE) && (RR -> Right -> Type == NULL_NODE);
				if (right_is_leaf) {
					RR -> x = -9999;
				} else {
					RR -> x = RR -> v;
				}
				RR -> y = RR -> v * 2;
			}
			
			Left -> f2();
			Right -> f2();
		}
};

Node * createTree() {
	Node * Root = new ValueNode();
	ValueNode *const _Root = static_cast<ValueNode *>(Root);
	_Root -> v = 5;
	_Root -> Type = VAL_NODE;

	Node * N3 = new ValueNode();
	ValueNode *const _N3 = static_cast<ValueNode *>(N3);
	_N3 -> v = 3;
	_N3 -> Type = VAL_NODE;

	Node * N3_L = new NullNode();
	N3_L -> Type = NULL_NODE;
	Node * N3_R = new NullNode();
	N3_R -> Type = NULL_NODE;
	_N3 -> Left = N3_L;
	_N3 -> Right = N3_R;

	Node * N7 = new ValueNode();
	ValueNode *const _N7 = static_cast<ValueNode *>(N7);
	_N7 -> v = 7;
	_N7 -> Type = VAL_NODE;

	Node * N7_L = new NullNode();
	N7_L -> Type = NULL_NODE;
	Node * N7_R = new NullNode();
	N7_R -> Type = NULL_NODE;
	_N7 -> Left = N7_L;
	_N7 -> Right = N7_R;

	_Root -> Left = N3;
	_Root -> Right = N7;

	return Root;
}

int main() {
	Node * Root = createTree();
	// here starts the part that requires fusion
	Root -> f1();
	Root -> f2();
}
