#include <assert.h>
#include <chrono>
#include <stddef.h>
#include <stdio.h>

#define __tree_structure__ __attribute__((annotate("tf_tree")))
#define __tree_child__ __attribute__((annotate("tf_child")))
#define __tree_traversal__ __attribute__((annotate("tf_fuse")))
#define _Bool bool

enum NodeType { VAL_NODE, NULL_NODE };

class __tree_structure__ Node {
public:
  bool Found = false;
  NodeType Type;
  __tree_traversal__ virtual void search(int Key, bool ValidCall) {}

  __tree_traversal__ virtual void insert(int Key, bool ValidCall) {}
  virtual void __virtualStub0(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                              _Bool _f1_ValidCall, unsigned int truncate_flags);
  virtual void __virtualStub1(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                              _Bool _f1_ValidCall, unsigned int truncate_flags);
  virtual void __virtualStub2(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                              _Bool _f1_ValidCall, int _f2_Key,
                              _Bool _f2_ValidCall, unsigned int truncate_flags);
};

class __tree_structure__ NullNode : public Node {

  __tree_traversal__ virtual void search(int Key, bool ValidCall) {
    Found = false;
  }

  __tree_traversal__ virtual void insert(int Key, bool ValidCall) {}
  void __virtualStub0(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                      _Bool _f1_ValidCall,
                      unsigned int truncate_flags) override;
  void __virtualStub1(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                      _Bool _f1_ValidCall,
                      unsigned int truncate_flags) override;
  void __virtualStub2(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                      _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                      unsigned int truncate_flags) override;
};

class __tree_structure__ ValueNode : public Node {
public:
  int Value;
  __tree_child__ Node *Left, *Right;

  __tree_traversal__ void search(int Key, bool ValidCall) override {

    if (ValidCall == false)
      return;

    Found = false;
    if (Key == Value) {
      Found = true;
      return;
    }
    Left->search(Key, Key < Value);
    Right->search(Key, Key >= Value);
    Found = Left->Found || Right->Found;
  }

  __tree_traversal__ void insert(int NewValue, bool ValidCall) {
    if (ValidCall == false)
      return;

    if (NewValue < Value && Left->Type == NULL_NODE) {
      delete Left;
      Left = new ValueNode();
      ValueNode *const Left_ = static_cast<ValueNode *>(Left);
      Left_->Value = NewValue;
      Left_->Type = VAL_NODE;

      Left_->Left = new NullNode();
      Left_->Left->Type = NULL_NODE;

      Left_->Right = new NullNode();
      Left_->Right->Type = NULL_NODE;

      return;
    }
    if (NewValue >= Value && Right->Type == NULL_NODE) {
      delete Right;
      Right = new ValueNode();
      ValueNode *const Right_ = static_cast<ValueNode *>(Right);
      Right_->Value = NewValue;
      Right_->Type = VAL_NODE;

      Right_->Left = new NullNode();
      Right_->Left->Type = NULL_NODE;

      Right_->Right = new NullNode();
      Right_->Right->Type = NULL_NODE;
      return;
    }

    Left->insert(NewValue, NewValue < Value);
    Right->insert(NewValue, NewValue >= Value);
  }
  void __virtualStub0(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                      _Bool _f1_ValidCall,
                      unsigned int truncate_flags) override;
  void __virtualStub1(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                      _Bool _f1_ValidCall,
                      unsigned int truncate_flags) override;
  void __virtualStub2(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                      _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                      unsigned int truncate_flags) override;
};

Node *createTree() {
  Node *Root = new ValueNode();
  ValueNode *const Root_ = static_cast<ValueNode *>(Root);
  Root_->Value = 5;
  Root_->Type = VAL_NODE;

  Root_->Left = new NullNode();
  Root_->Left->Type = NULL_NODE;

  Root_->Right = new NullNode();
  Root_->Right->Type = NULL_NODE;

  return Root;
}

void _fuse__F5F6(ValueNode *_r, int _f0_NewValue, _Bool _f0_ValidCall,
                 int _f1_Key, _Bool _f1_ValidCall, unsigned int truncate_flags);
void _fuse__F1F2(Node *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                 _Bool _f1_ValidCall, unsigned int truncate_flags);
void _fuse__F5F5F6(ValueNode *_r, int _f0_NewValue, _Bool _f0_ValidCall,
                   int _f1_NewValue, _Bool _f1_ValidCall, int _f2_Key,
                   _Bool _f2_ValidCall, unsigned int truncate_flags);
void _fuse__F1F1F2(Node *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                   _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                   unsigned int truncate_flags);
void _fuse__F3F4(NullNode *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                 _Bool _f1_ValidCall, unsigned int truncate_flags);
void _fuse__F3F3F4(NullNode *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                   _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                   unsigned int truncate_flags);
void _fuse__F5F6(ValueNode *_r, int _f0_NewValue, _Bool _f0_ValidCall,
                 int _f1_Key, _Bool _f1_ValidCall,
                 unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ValueNode *_r_f0 = (ValueNode *)(_r);
  ValueNode *_r_f1 = (ValueNode *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0_ValidCall == false) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
    if (_f0_NewValue < _r_f0->Value && _r_f0->Left->Type == NULL_NODE) {
      delete _r_f0->Left;
      _r_f0->Left = new ValueNode();
      class ValueNode *const _f0_Left_ =
          static_cast<class ValueNode *>(_r_f0->Left);
      _f0_Left_->Value = _f0_NewValue;
      _f0_Left_->Type = VAL_NODE;
      _f0_Left_->Left = new NullNode();
      _f0_Left_->Left->Type = NULL_NODE;
      _f0_Left_->Right = new NullNode();
      _f0_Left_->Right->Type = NULL_NODE;
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
    if (_f0_NewValue >= _r_f0->Value && _r_f0->Right->Type == NULL_NODE) {
      delete _r_f0->Right;
      _r_f0->Right = new ValueNode();
      class ValueNode *const _f0_Right_ =
          static_cast<class ValueNode *>(_r_f0->Right);
      _f0_Right_->Value = _f0_NewValue;
      _f0_Right_->Type = VAL_NODE;
      _f0_Right_->Left = new NullNode();
      _f0_Right_->Left->Type = NULL_NODE;
      _f0_Right_->Right = new NullNode();
      _f0_Right_->Right->Type = NULL_NODE;
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    if (_f1_ValidCall == false) {
      truncate_flags &= 0b11111111101;
      goto _label_B1F1_Exit;
    }
    _r_f1->Found = false;
    if (_f1_Key == _r_f1->Value) {
      _r_f1->Found = true;
      truncate_flags &= 0b11111111101;
      goto _label_B1F1_Exit;
    }
  }
_label_B1F1_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f1->Left->__virtualStub0(_f0_NewValue, _f0_NewValue < _r_f0->Value,
                                _f1_Key, _f1_Key < _r_f1->Value,
                                AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f1->Right->__virtualStub1(_f0_NewValue, _f0_NewValue >= _r_f0->Value,
                                 _f1_Key, _f1_Key >= _r_f1->Value,
                                 AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    _r_f1->Found = _r_f1->Left->Found || _r_f1->Right->Found;
  }
_label_B3F1_Exit:
  return;
};
void _fuse__F1F2(Node *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                 _Bool _f1_ValidCall, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  return;
};
void _fuse__F5F5F6(ValueNode *_r, int _f0_NewValue, _Bool _f0_ValidCall,
                   int _f1_NewValue, _Bool _f1_ValidCall, int _f2_Key,
                   _Bool _f2_ValidCall, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ValueNode *_r_f0 = (ValueNode *)(_r);
  ValueNode *_r_f1 = (ValueNode *)(_r);
  ValueNode *_r_f2 = (ValueNode *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0_ValidCall == false) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
    if (_f0_NewValue < _r_f0->Value && _r_f0->Left->Type == NULL_NODE) {
      delete _r_f0->Left;
      _r_f0->Left = new ValueNode();
      class ValueNode *const _f0_Left_ =
          static_cast<class ValueNode *>(_r_f0->Left);
      _f0_Left_->Value = _f0_NewValue;
      _f0_Left_->Type = VAL_NODE;
      _f0_Left_->Left = new NullNode();
      _f0_Left_->Left->Type = NULL_NODE;
      _f0_Left_->Right = new NullNode();
      _f0_Left_->Right->Type = NULL_NODE;
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
    if (_f0_NewValue >= _r_f0->Value && _r_f0->Right->Type == NULL_NODE) {
      delete _r_f0->Right;
      _r_f0->Right = new ValueNode();
      class ValueNode *const _f0_Right_ =
          static_cast<class ValueNode *>(_r_f0->Right);
      _f0_Right_->Value = _f0_NewValue;
      _f0_Right_->Type = VAL_NODE;
      _f0_Right_->Left = new NullNode();
      _f0_Right_->Left->Type = NULL_NODE;
      _f0_Right_->Right = new NullNode();
      _f0_Right_->Right->Type = NULL_NODE;
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Left->insert(_f0_NewValue, _f0_NewValue < _r_f0->Value);
  }
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Right->insert(_f0_NewValue, _f0_NewValue >= _r_f0->Value);
  }
  if (truncate_flags & 0b10) {
    if (_f1_ValidCall == false) {
      truncate_flags &= 0b11111111101;
      goto _label_B3F1_Exit;
    }
    if (_f1_NewValue < _r_f1->Value && _r_f1->Left->Type == NULL_NODE) {
      delete _r_f1->Left;
      _r_f1->Left = new ValueNode();
      class ValueNode *const _f1_Left_ =
          static_cast<class ValueNode *>(_r_f1->Left);
      _f1_Left_->Value = _f1_NewValue;
      _f1_Left_->Type = VAL_NODE;
      _f1_Left_->Left = new NullNode();
      _f1_Left_->Left->Type = NULL_NODE;
      _f1_Left_->Right = new NullNode();
      _f1_Left_->Right->Type = NULL_NODE;
      truncate_flags &= 0b11111111101;
      goto _label_B3F1_Exit;
    }
    if (_f1_NewValue >= _r_f1->Value && _r_f1->Right->Type == NULL_NODE) {
      delete _r_f1->Right;
      _r_f1->Right = new ValueNode();
      class ValueNode *const _f1_Right_ =
          static_cast<class ValueNode *>(_r_f1->Right);
      _f1_Right_->Value = _f1_NewValue;
      _f1_Right_->Type = VAL_NODE;
      _f1_Right_->Left = new NullNode();
      _f1_Right_->Left->Type = NULL_NODE;
      _f1_Right_->Right = new NullNode();
      _f1_Right_->Right->Type = NULL_NODE;
      truncate_flags &= 0b11111111101;
      goto _label_B3F1_Exit;
    }
  }
_label_B3F1_Exit:
  if (truncate_flags & 0b100) {
    if (_f2_ValidCall == false) {
      truncate_flags &= 0b11111111011;
      goto _label_B3F2_Exit;
    }
    _r_f2->Found = false;
    if (_f2_Key == _r_f2->Value) {
      _r_f2->Found = true;
      truncate_flags &= 0b11111111011;
      goto _label_B3F2_Exit;
    }
  }
_label_B3F2_Exit:
  if ((truncate_flags & 0b110)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    _r_f2->Left->__virtualStub0(_f1_NewValue, _f1_NewValue < _r_f1->Value,
                                _f2_Key, _f2_Key < _r_f2->Value,
                                AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b110)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    _r_f2->Right->__virtualStub1(_f1_NewValue, _f1_NewValue >= _r_f1->Value,
                                 _f2_Key, _f2_Key >= _r_f2->Value,
                                 AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100) {
    _r_f2->Found = _r_f2->Left->Found || _r_f2->Right->Found;
  }
_label_B5F2_Exit:
  return;
};
void _fuse__F1F1F2(Node *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                   _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  Node *_r_f2 = (Node *)(_r);
  return;
};
void _fuse__F3F4(NullNode *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                 _Bool _f1_ValidCall, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  NullNode *_r_f0 = (NullNode *)(_r);
  NullNode *_r_f1 = (NullNode *)(_r);
  if (truncate_flags & 0b10) {
    _r_f1->Found = false;
  }
_label_B1F1_Exit:
  return;
};
void _fuse__F3F3F4(NullNode *_r, int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                   _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  NullNode *_r_f0 = (NullNode *)(_r);
  NullNode *_r_f1 = (NullNode *)(_r);
  NullNode *_r_f2 = (NullNode *)(_r);
  if (truncate_flags & 0b100) {
    _r_f2->Found = false;
  }
_label_B1F2_Exit:
  return;
};
void Node::__virtualStub0(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                          _Bool _f1_ValidCall, unsigned int truncate_flags) {
  _fuse__F1F2(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall,
              truncate_flags);
}
void NullNode::__virtualStub0(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                              _Bool _f1_ValidCall,
                              unsigned int truncate_flags) {
  _fuse__F3F4(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall,
              truncate_flags);
}
void ValueNode::__virtualStub0(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                               _Bool _f1_ValidCall,
                               unsigned int truncate_flags) {
  _fuse__F5F6(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall,
              truncate_flags);
}
void Node::__virtualStub1(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                          _Bool _f1_ValidCall, unsigned int truncate_flags) {
  _fuse__F1F2(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall,
              truncate_flags);
}
void NullNode::__virtualStub1(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                              _Bool _f1_ValidCall,
                              unsigned int truncate_flags) {
  _fuse__F3F4(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall,
              truncate_flags);
}
void ValueNode::__virtualStub1(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                               _Bool _f1_ValidCall,
                               unsigned int truncate_flags) {
  _fuse__F5F6(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall,
              truncate_flags);
}
void Node::__virtualStub2(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                          _Bool _f1_ValidCall, int _f2_Key, _Bool _f2_ValidCall,
                          unsigned int truncate_flags) {
  _fuse__F1F1F2(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall, _f2_Key,
                _f2_ValidCall, truncate_flags);
}
void NullNode::__virtualStub2(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                              _Bool _f1_ValidCall, int _f2_Key,
                              _Bool _f2_ValidCall,
                              unsigned int truncate_flags) {
  _fuse__F3F3F4(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall, _f2_Key,
                _f2_ValidCall, truncate_flags);
}
void ValueNode::__virtualStub2(int _f0_Key, _Bool _f0_ValidCall, int _f1_Key,
                               _Bool _f1_ValidCall, int _f2_Key,
                               _Bool _f2_ValidCall,
                               unsigned int truncate_flags) {
  _fuse__F5F5F6(this, _f0_Key, _f0_ValidCall, _f1_Key, _f1_ValidCall, _f2_Key,
                _f2_ValidCall, truncate_flags);
}
int main() {
  Node *Root = createTree();
  // Root->insert(10, true);
  // Root->insert(20, true);
  // Root->search(10, true);

  // added by fuse transformer
  Root->__virtualStub2(10, true, 20, true, 10, true, 0b111);
  if (Root->Found)
    printf("10 is found\n");
  else
    printf("10 is not found\n");
}
