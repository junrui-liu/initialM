#define __tree_structure__ __attribute__((annotate("tf_tree")))
#define __tree_child__ __attribute__((annotate("tf_child")))
#define __tree_traversal__ __attribute__((annotate("tf_fuse")))
#define __abstract_access__(AccessList)                                        \
  __attribute__((annotate("tf_strict_access" #AccessList)))

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
int _VISIT_COUNTER = 0;

#ifdef PAPI
#include <iostream>
#include <papi.h>
#define SIZE 3
string instance("Original");
int ret;
int _VISIT_COUNTER = 0;
int events[] = {PAPI_L2_TCM, PAPI_L3_TCM, PAPI_TOT_INS};
string defs[] = {"L2 Cache Misses", "L3 Cache Misses ", "Instructions"};

long long values[SIZE];
long long rcyc0, rcyc1, rusec0, rusec1;
long long vcyc0, vcyc1, vusec0, vusec1;

void init_papi() {
  if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
    cout << "PAPI Init Error" << endl;
    exit(1);
  }
  for (int i = 0; i < SIZE; ++i) {
    if (PAPI_query_event(events[i]) != PAPI_OK) {
      cout << "PAPI Event " << i << " does not exist" << endl;
    }
  }
}
void start_counters() {
  // Performance Counters Start
  if (PAPI_start_counters(events, SIZE) != PAPI_OK) {
    cout << "PAPI Error starting counters" << endl;
  }
}
void read_counters() {
  // Performance Counters Read
  ret = PAPI_stop_counters(values, SIZE);
  if (ret != PAPI_OK) {
    if (ret == PAPI_ESYS) {
      cout << "error inside PAPI call" << endl;
    } else if (ret == PAPI_EINVAL) {
      cout << "error with arguments" << endl;
    }

    cout << "PAPI Error reading counters" << endl;
  }
}
void print_counters() {
  for (int i = 0; i < SIZE; ++i)
    cout << defs[i] << " : " << values[i] << "\n";
}
#endif

enum NodeType { LEAF, INNER };
// polynomial representation as an array

// Tree node
class __tree_structure__ Node {
public:
  float startDom;
  float endDom;
  NodeType type;
  float projectVal;

  virtual void print(){};
  __tree_traversal__ virtual void buildTree(int depth, int d, int size, float s,
                                            float e){};
  __tree_traversal__ virtual void addConst(float c){};
  __tree_traversal__ virtual void multConst(float c){};
  __tree_traversal__ virtual void divConst(float c){};
  __tree_traversal__ virtual void differentiate(){};
  __tree_traversal__ virtual void mulVar(){};
  __tree_traversal__ virtual void rangeMulConst(float c, float _s, float _e){};
  __tree_traversal__ virtual void rangeMulVar(float _s, float _e){};
  __tree_traversal__ virtual void boundedIntegrate(float _a, float _b){};
  __tree_traversal__ virtual void project(float x){};
  __tree_traversal__ virtual void square(){};
  virtual void __virtualStub0(float _f0_c, unsigned int truncate_flags);
  virtual void __virtualStub1(float _f0_c, unsigned int truncate_flags);
  virtual void __virtualStub3(float _f0_c, float _f0__s, float _f0__e,
                              float _f4__a, float _f4__b,
                              unsigned int truncate_flags);
  virtual void __virtualStub2(float _f0_c, float _f0__s, float _f0__e,
                              float _f4__a, float _f4__b,
                              unsigned int truncate_flags);
  virtual void __virtualStub4(float _f0_c, float _f2_c, float _f2__s,
                              float _f2__e, float _f6__a, float _f6__b,
                              unsigned int truncate_flags);
  virtual void __virtualStub5(float _f5_x, unsigned int truncate_flags);
  virtual void __virtualStub6(float _f5_x, unsigned int truncate_flags);
  virtual void __virtualStub7(float _f5_x, unsigned int truncate_flags);
  virtual void __virtualStub10(float _f0_c, unsigned int truncate_flags);
  virtual void __virtualStub11(float _f0_c, unsigned int truncate_flags);
  virtual void __virtualStub8(float _f4_c, float _f6_c, float _f8_c,
                              unsigned int truncate_flags);
  virtual void __virtualStub9(float _f4_c, float _f6_c, float _f8_c,
                              unsigned int truncate_flags);
  virtual void __virtualStub12(float _f4_c, float _f6_c, float _f8_c,
                               float _f10_c, unsigned int truncate_flags);
};

class __tree_structure__ Poly {
public:
  // loc1
  std::vector<float> arr;
  int size;

  inline void print() {
    std::cout << arr[0];
    for (int i = 1; i < size; i++) {
      std::cout << " + " << arr[i] << "x^" << i;
    }
    std::cout << std::endl;
  }

  __abstract_access__("(1,'w','local')") inline void assignCoeff(int _size) {
    size = _size;
    arr.resize(size, 0);
    // for(int i = 0; i < size; i++) arr.push_back(1);
  }
  __abstract_access__("(1,'w','local')") inline void addCons(float c) {
    arr[0] += c;
  }

  __abstract_access__("(1,'w','local')") inline void multConst(float c) {
    for (int i = 0; i < size; i++) {
      arr[i] *= c;
    }
  }

  __abstract_access__("(1,'w','local')") inline void divConst(float c) {
    for (int i = 0; i < size; i++) {
      arr[i] /= c;
    }
  }

  __abstract_access__("(1,'w','local')") inline void differentiate() {
    for (int i = 0; i < size - 1; i++) {
      arr[i] = (i + 1) * arr[i + 1];
    }
    size--;
  }
  __abstract_access__("(1,'w','local')") inline void mulVar() {
    // float tmp[] = {0};
    if (arr.size() == 0)
      arr.push_back(0);
    else
      arr.insert(arr.begin(), 0);
    size++;
  }

  __abstract_access__("(1,'w','local')") inline void setArray(
      std::vector<float> &_arr, int _size) {
    arr = _arr;
    size = _size;
  }

  __abstract_access__("(1,'w','local')") inline float boundedIntegrate(
      float _a, float _b) {
    float ret = 0.0;
    for (int i = 0; i < size; i++) {
      float pa_ = 1.0;
      float pb_ = 1.0;
      for (int j = 0; j < i + 1; j++) {
        pa_ *= _a;
        pb_ *= _b;
      }
      ret += arr[i] * (pb_ - pa_) / (i + 1);
    }
    return ret;
  }

  __abstract_access__("(1,'w','local')") inline float project(float x) {
    float ret = 0.0;
    for (int i = 0; i < size; i++) {
      float p = 1.0;
      for (int j = 0; j < i; j++)
        p *= x;
      ret += arr[i] * p;
    }
    return ret;
  }

  __abstract_access__("(1,'w','local')") inline void square() {
    std::vector<float> sarr;
    int N = size;
    int M = N * N;
    sarr.resize(M, 0);
    // for(int i = 0; i < M; i++) sarr.push_back(0);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        sarr[i + j] += arr[i] * arr[j];
      }
    }
    setArray(sarr, M);
  }
};

class __tree_structure__ Inner : public Node {
public:
  __tree_child__ Node *l;
  __tree_child__ Node *r;
  void print() override;
  __tree_traversal__ void buildTree(int depth, int d, int size, float s,
                                    float e) override;
  __tree_traversal__ void addConst(float c) override;
  __tree_traversal__ void multConst(float c) override;
  __tree_traversal__ void divConst(float c) override;
  __tree_traversal__ void differentiate() override;
  __tree_traversal__ void mulVar() override;
  __tree_traversal__ void inline splitLeft(float c, float s);
  __tree_traversal__ void inline splitRight(float _s, float _e);
  __tree_traversal__ void rangeMulConst(float c, float _s, float _e) override;
  __tree_traversal__ void rangeMulVar(float _s, float _e) override;
  __tree_traversal__ void boundedIntegrate(float _a, float _b) override;
  __tree_traversal__ void project(float x) override;
  __tree_traversal__ void square() override;
  void __virtualStub0(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub1(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub3(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                      float _f4__b, unsigned int truncate_flags) override;
  void __virtualStub2(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                      float _f4__b, unsigned int truncate_flags) override;
  void __virtualStub4(float _f0_c, float _f2_c, float _f2__s, float _f2__e,
                      float _f6__a, float _f6__b,
                      unsigned int truncate_flags) override;
  void __virtualStub5(float _f5_x, unsigned int truncate_flags) override;
  void __virtualStub6(float _f5_x, unsigned int truncate_flags) override;
  void __virtualStub7(float _f5_x, unsigned int truncate_flags) override;
  void __virtualStub10(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub11(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub8(float _f4_c, float _f6_c, float _f8_c,
                      unsigned int truncate_flags) override;
  void __virtualStub9(float _f4_c, float _f6_c, float _f8_c,
                      unsigned int truncate_flags) override;
  void __virtualStub12(float _f4_c, float _f6_c, float _f8_c, float _f10_c,
                       unsigned int truncate_flags) override;
};

class __tree_structure__ Leaf : public Node {
public:
  __tree_child__ Poly *coeff;
  void print() override;
  __tree_traversal__ void buildTree(int depth, int d, int size, float s,
                                    float e) override;
  __tree_traversal__ void addConst(float c) override;
  __tree_traversal__ void multConst(float c) override;
  __tree_traversal__ void divConst(float c) override;
  __tree_traversal__ void differentiate() override;
  __tree_traversal__ void mulVar() override;
  __tree_traversal__ void rangeMulConst(float c, float _s, float _e) override;
  __tree_traversal__ void rangeMulVar(float _s, float _e) override;
  __tree_traversal__ void boundedIntegrate(float _a, float _b) override;
  __tree_traversal__ void project(float x) override;
  __tree_traversal__ void square() override;
  void __virtualStub0(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub1(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub3(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                      float _f4__b, unsigned int truncate_flags) override;
  void __virtualStub2(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                      float _f4__b, unsigned int truncate_flags) override;
  void __virtualStub4(float _f0_c, float _f2_c, float _f2__s, float _f2__e,
                      float _f6__a, float _f6__b,
                      unsigned int truncate_flags) override;
  void __virtualStub5(float _f5_x, unsigned int truncate_flags) override;
  void __virtualStub6(float _f5_x, unsigned int truncate_flags) override;
  void __virtualStub7(float _f5_x, unsigned int truncate_flags) override;
  void __virtualStub10(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub11(float _f0_c, unsigned int truncate_flags) override;
  void __virtualStub8(float _f4_c, float _f6_c, float _f8_c,
                      unsigned int truncate_flags) override;
  void __virtualStub9(float _f4_c, float _f6_c, float _f8_c,
                      unsigned int truncate_flags) override;
  void __virtualStub12(float _f4_c, float _f6_c, float _f8_c, float _f10_c,
                       unsigned int truncate_flags) override;
};

void Inner::print() {
  l->print();
  r->print();
}

void Leaf::print() {
  std::cout << "Range:[ " << startDom << ", " << endDom << "]" << std::endl;
  coeff->print();
}

// build a balanced kd-tree
__tree_traversal__ void Inner::buildTree(int depth, int d, int size, float s,
                                         float e) {
  startDom = s;
  endDom = e;
  projectVal = 0.0;

  if (d == depth - 1) {
    l = new Leaf();
    l->type = LEAF;
  }

  if (d == depth - 1) {
    r = new Leaf();
    r->type = LEAF;
  }
  if (d < depth - 1) {
    l = new Inner();
    l->type = INNER;
  }

  if (d < depth - 1) {
    r = new Inner();
    r->type = INNER;
  }

  l->buildTree(depth, d + 1, size, s, (s + e) / 2);
  r->buildTree(depth, d + 1, size, (s + e) / 2, e);
}

__tree_traversal__ void Leaf::buildTree(int depth, int d, int size, float s,
                                        float e) {
  startDom = s;
  endDom = e;
  projectVal = 0.0;
  coeff = new Poly();
  coeff->assignCoeff(size);
}

__tree_traversal__ void Inner::addConst(float c) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  l->addConst(c);
  r->addConst(c);
}

// adding constant to x^0
__tree_traversal__ void Leaf::addConst(float c) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  coeff->addCons(c);
}

__tree_traversal__ void Inner::multConst(float c) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif

  l->multConst(c);
  r->multConst(c);
}

// multiplying every coeff by the constant
__tree_traversal__ void Leaf::multConst(float c) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  coeff->multConst(c);
}

__tree_traversal__ void Inner::divConst(float c) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  l->divConst(c);
  r->divConst(c);
}

// dividing every coeff by the constant
__tree_traversal__ void Leaf::divConst(float c) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  coeff->divConst(c);
}

__tree_traversal__ void Inner::differentiate() {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  l->differentiate();
  r->differentiate();
}

// differentiate the polynomial for the range
__tree_traversal__ void Leaf::differentiate() {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif

  coeff->differentiate();
}

__tree_traversal__ void Inner::mulVar() {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  l->mulVar();
  r->mulVar();
}

// multiply the function by x
__tree_traversal__ void Leaf::mulVar() {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  coeff->mulVar();
}

__tree_traversal__ void Inner::splitLeft(float _s, float _e) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  // splitting if needed
  if (l->type == LEAF && ((_s > l->startDom && _s < l->endDom) ||
                          (_e > l->startDom && _e < l->endDom))) {

    // split into 5 nodes
    if ((_s > l->startDom && _s < l->endDom) &&
        (_e > l->startDom && _e < l->endDom)) {
      float s1 = l->startDom;
      float e1 = _s;
      float s2 = e1;
      float e2 = _e;
      float s3 = e2;
      float e3 = l->endDom;

      Leaf *const oldNode = static_cast<Leaf *>(l);
      l = new Inner();
      auto *const newInner1 = static_cast<Inner *>(l);
      newInner1->type = INNER;
      newInner1->startDom = s1;
      newInner1->endDom = e3;

      // create node Inner1 and leaf1
      newInner1->l = new Leaf();
      static_cast<Leaf *>(newInner1->l)->coeff = new Poly();

      newInner1->l->type = LEAF;
      newInner1->l->startDom = s1;
      newInner1->l->endDom = e1;
      static_cast<Leaf *>(newInner1->l)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);

      // creating Inner2 and leaf2, and leaf3
      newInner1->r = new Inner();
      auto *const newInner2 = static_cast<Inner *>(newInner1->r);
      newInner2->type = INNER;
      newInner2->startDom = s2;
      newInner2->endDom = e3;

      newInner2->l = new Leaf();
      static_cast<Leaf *>(newInner2->l)->coeff = new Poly();

      newInner2->l->type = LEAF;
      newInner2->l->startDom = s2;
      newInner2->l->endDom = e2;
      static_cast<Leaf *>(newInner2->l)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);

      newInner2->r = new Leaf();
      static_cast<Leaf *>(newInner2->r)->coeff = new Poly();

      newInner2->r->type = LEAF;
      newInner2->r->startDom = s3;
      newInner2->r->endDom = e3;
      static_cast<Leaf *>(newInner2->r)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);
      delete oldNode;
    }
    // split into three nodes
    else {
      float s1 = l->startDom;
      float e1;
      if (_s > l->startDom && _s < l->endDom)
        e1 = _s;
      else
        e1 = _e;

      float s2 = e1;
      float e2 = l->endDom;

      auto *const oldNode = static_cast<Leaf *>(l);

      // create Inner Node
      l = new Inner();
      l->type = INNER;
      auto *const newInner = static_cast<Inner *>(l);
      newInner->type = INNER;
      newInner->startDom = s1;
      newInner->endDom = e2;

      newInner->l = new Leaf();
      static_cast<Leaf *>(newInner->l)->coeff = new Poly();

      newInner->l->type = LEAF;
      newInner->l->startDom = s1;
      newInner->l->endDom = e1;
      static_cast<Leaf *>(newInner->l)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);

      newInner->r = new Leaf();
      static_cast<Leaf *>(newInner->r)->coeff = new Poly();

      newInner->r->type = LEAF;
      newInner->r->startDom = s2;
      newInner->r->endDom = e2;
      static_cast<Leaf *>(newInner->r)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);
      delete oldNode;
    }
  }
}

__tree_traversal__ void Inner::splitRight(float _s, float _e) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  // splitting if needed
  if (r->type == LEAF && ((_s > r->startDom && _s < r->endDom) ||
                          (_e > r->startDom && _e < r->endDom))) {

    // split into 5 nodes
    if ((_s > r->startDom && _s < r->endDom) &&
        (_e > r->startDom && _e < r->endDom)) {
      float s1 = r->startDom;
      float e1 = _s;
      float s2 = e1;
      float e2 = _e;
      float s3 = e2;
      float e3 = r->endDom;

      Leaf *const oldNode = static_cast<Leaf *>(r);
      r = new Inner();
      auto *const newInner1 = static_cast<Inner *>(r);
      newInner1->type = INNER;
      newInner1->startDom = s1;
      newInner1->endDom = e3;

      // create node Inner1 and leaf1
      newInner1->l = new Leaf();
      static_cast<Leaf *>(newInner1->l)->coeff = new Poly();

      newInner1->l->type = LEAF;
      newInner1->l->startDom = s1;
      newInner1->l->endDom = e1;
      static_cast<Leaf *>(newInner1->l)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);

      // creating Inner2 and leaf2, and leaf3
      newInner1->r = new Inner();
      auto *const newInner2 = static_cast<Inner *>(newInner1->r);
      newInner2->type = INNER;
      newInner2->startDom = s2;
      newInner2->endDom = e3;

      newInner2->l = new Leaf();
      static_cast<Leaf *>(newInner2->l)->coeff = new Poly();

      newInner2->l->type = LEAF;
      newInner2->l->startDom = s2;
      newInner2->l->endDom = e2;
      static_cast<Leaf *>(newInner2->l)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);

      newInner2->r = new Leaf();
      static_cast<Leaf *>(newInner2->r)->coeff = new Poly();

      newInner2->r->type = LEAF;
      newInner2->r->startDom = s3;
      newInner2->r->endDom = e3;
      static_cast<Leaf *>(newInner2->r)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);
      delete oldNode;
    }
    // split into three nodes
    else {
      float s1 = r->startDom;
      float e1;
      if (_s > r->startDom && _s < r->endDom)
        e1 = _s;
      else
        e1 = _e;

      float s2 = e1;
      float e2 = r->endDom;

      auto *const oldNode = static_cast<Leaf *>(r);

      // create Inner Node
      r = new Inner();
      r->type = INNER;
      auto *const newInner = static_cast<Inner *>(r);
      newInner->type = INNER;
      newInner->startDom = s1;
      newInner->endDom = e2;

      newInner->l = new Leaf();
      static_cast<Leaf *>(newInner->l)->coeff = new Poly();

      newInner->l->type = LEAF;
      newInner->l->startDom = s1;
      newInner->l->endDom = e1;
      static_cast<Leaf *>(newInner->l)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);

      newInner->r = new Leaf();
      static_cast<Leaf *>(newInner->r)->coeff = new Poly();

      newInner->r->type = LEAF;
      newInner->r->startDom = s2;
      newInner->r->endDom = e2;
      static_cast<Leaf *>(newInner->r)
          ->coeff->setArray(oldNode->coeff->arr, oldNode->coeff->size);
      delete oldNode;
    }
  }
}

void Inner::rangeMulConst(float c, float _s, float _e) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (_s >= endDom || _e <= startDom)
    return;

  splitLeft(_s, _e);
  ;
  splitRight(_s, _e);

  l->rangeMulConst(c, _s, _e);
  r->rangeMulConst(c, _s, _e);
}

// multiply the range by a constant
__tree_traversal__ void Leaf::rangeMulConst(float c, float _s, float _e) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (_s >= endDom || _e <= startDom)
    return;

  coeff->multConst(c);
}

void Inner::rangeMulVar(float _s, float _e) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (_s >= endDom || _e <= startDom)
    return;

  splitLeft(_s, _e);
  ;
  splitRight(_s, _e);
  l->rangeMulVar(_s, _e);
  r->rangeMulVar(_s, _e);
}

// multiply the range by x
__tree_traversal__ void Leaf::rangeMulVar(float _s, float _e) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (_s >= endDom || _e <= startDom)
    return;

  coeff->mulVar();
}

__tree_traversal__ void Inner::boundedIntegrate(float _a, float _b) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (_a > endDom || _b < startDom) {
    projectVal = 0.0;
    return;
  }

  float a_;
  a_ = _a;
  float b_;
  b_ = _b;

  if (_a < startDom)
    a_ = startDom;
  if (_b > endDom)
    b_ = endDom;

  l->boundedIntegrate(a_, b_);
  r->boundedIntegrate(a_, b_);

  projectVal = l->projectVal + r->projectVal;
}

// integrate the polynomial for the range
__tree_traversal__ void Leaf::boundedIntegrate(float _a, float _b) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (_a > endDom || _b < startDom) {
    projectVal = 0.0;
    return;
  }

  float a_;
  a_ = _a;
  float b_;
  b_ = _b;

  if (_a < startDom)
    a_ = startDom;
  if (_b > endDom)
    b_ = endDom;

  projectVal = coeff->boundedIntegrate(a_, b_);
}

// compute the function at a given point
__tree_traversal__ void Inner::project(float x) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (x < startDom || x > endDom)
    return;

  l->project(x);
  r->project(x);

  if (x >= l->startDom && x < l->endDom)
    projectVal = l->projectVal;
  if (x >= r->startDom && x < r->endDom)
    projectVal = r->projectVal;
}

__tree_traversal__ void Leaf::project(float x) {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  if (x < startDom || x > endDom)
    return;

  projectVal = coeff->project(x);
}

// square the domain of the function
__tree_traversal__ void Inner::square() {
#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  l->square();
  r->square();
}

__tree_traversal__ void Leaf::square() {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  coeff->square();
}

void _fuse__F22F22F22F22F22F23(Leaf *_r, float _f5_x,
                               unsigned int truncate_flags);
void _fuse__F20F20F20F20F20F21(Inner *_r, float _f5_x,
                               unsigned int truncate_flags);
void _fuse__F18F18F18F18F18F19(Node *_r, float _f5_x,
                               unsigned int truncate_flags);
void _fuse__F15F16F16F16F17(Leaf *_r, float _f0_c, float _f0__s, float _f0__e,
                            float _f4__a, float _f4__b,
                            unsigned int truncate_flags);
void _fuse__F8F9F9F9F10(Inner *_r, float _f0_c, float _f0__s, float _f0__e,
                        float _f4__a, float _f4__b,
                        unsigned int truncate_flags);
void _fuse__F3F4F4F4F5(Node *_r, float _f0_c, float _f0__s, float _f0__e,
                       float _f4__a, float _f4__b, unsigned int truncate_flags);
void _fuse__F1F2F3F4F4F4F5(Node *_r, float _f0_c, float _f2_c, float _f2__s,
                           float _f2__e, float _f6__a, float _f6__b,
                           unsigned int truncate_flags);
void _fuse__F1F2(Node *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F11F12F15F16F16F16F17(Leaf *_r, float _f0_c, float _f2_c,
                                  float _f2__s, float _f2__e, float _f6__a,
                                  float _f6__b, unsigned int truncate_flags);
void _fuse__F6F7F8F9F9F9F10(Inner *_r, float _f0_c, float _f2_c, float _f2__s,
                            float _f2__e, float _f6__a, float _f6__b,
                            unsigned int truncate_flags);
void _fuse__F11F12(Leaf *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F13F14(Inner *_r, float _f0__s, float _f0__e, float _f1__s,
                   float _f1__e, unsigned int truncate_flags);
void _fuse__F6F7(Inner *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F22F22F22F22F22F23(Leaf *_r, float _f5_x,
                               unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  Leaf *_r_f2 = (Leaf *)(_r);
  Leaf *_r_f3 = (Leaf *)(_r);
  Leaf *_r_f4 = (Leaf *)(_r);
  Leaf *_r_f5 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    _r_f0->coeff->differentiate();
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->differentiate();
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->coeff->differentiate();
  }
_label_B1F2_Exit:
  if (truncate_flags & 0b1000) {
    _r_f3->coeff->differentiate();
  }
_label_B1F3_Exit:
  if (truncate_flags & 0b10000) {
    _r_f4->coeff->differentiate();
  }
_label_B1F4_Exit:
  if (truncate_flags & 0b100000) {
    if (_f5_x < _r_f5->startDom || _f5_x > _r_f5->endDom) {
      truncate_flags &= 0b11111011111;
      goto _label_B1F5_Exit;
    }
    _r_f5->projectVal = _r_f5->coeff->project(_f5_x);
  }
_label_B1F5_Exit:
  return;
};
void _fuse__F20F20F20F20F20F21(Inner *_r, float _f5_x,
                               unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  Inner *_r_f2 = (Inner *)(_r);
  Inner *_r_f3 = (Inner *)(_r);
  Inner *_r_f4 = (Inner *)(_r);
  Inner *_r_f5 = (Inner *)(_r);
  if (truncate_flags & 0b100000) {
    if (_f5_x < _r_f5->startDom || _f5_x > _r_f5->endDom) {
      truncate_flags &= 0b11111011111;
      goto _label_B1F5_Exit;
    }
  }
_label_B1F5_Exit:
  if ((truncate_flags & 0b111111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f5->l->__virtualStub5(_f5_x, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100000) {
    if (_f5_x >= _r_f5->l->startDom && _f5_x < _r_f5->l->endDom) {
      _r_f5->projectVal = _r_f5->l->projectVal;
    }
  }
_label_B2F5_Exit:
  if ((truncate_flags & 0b111111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f5->r->__virtualStub6(_f5_x, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100000) {
    if (_f5_x >= _r_f5->r->startDom && _f5_x < _r_f5->r->endDom) {
      _r_f5->projectVal = _r_f5->r->projectVal;
    }
  }
_label_B3F5_Exit:
  return;
};
void _fuse__F18F18F18F18F18F19(Node *_r, float _f5_x,
                               unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  Node *_r_f2 = (Node *)(_r);
  Node *_r_f3 = (Node *)(_r);
  Node *_r_f4 = (Node *)(_r);
  Node *_r_f5 = (Node *)(_r);
  return;
};
void Node::__virtualStub5(float _f5_x, unsigned int truncate_flags) {
  _fuse__F18F18F18F18F18F19(this, _f5_x, truncate_flags);
}
void Inner::__virtualStub5(float _f5_x, unsigned int truncate_flags) {
  _fuse__F20F20F20F20F20F21(this, _f5_x, truncate_flags);
}
void Leaf::__virtualStub5(float _f5_x, unsigned int truncate_flags) {
  _fuse__F22F22F22F22F22F23(this, _f5_x, truncate_flags);
}
void Node::__virtualStub6(float _f5_x, unsigned int truncate_flags) {
  _fuse__F18F18F18F18F18F19(this, _f5_x, truncate_flags);
}
void Inner::__virtualStub6(float _f5_x, unsigned int truncate_flags) {
  _fuse__F20F20F20F20F20F21(this, _f5_x, truncate_flags);
}
void Leaf::__virtualStub6(float _f5_x, unsigned int truncate_flags) {
  _fuse__F22F22F22F22F22F23(this, _f5_x, truncate_flags);
}
void Node::__virtualStub7(float _f5_x, unsigned int truncate_flags) {
  _fuse__F18F18F18F18F18F19(this, _f5_x, truncate_flags);
}
void Inner::__virtualStub7(float _f5_x, unsigned int truncate_flags) {
  _fuse__F20F20F20F20F20F21(this, _f5_x, truncate_flags);
}
void Leaf::__virtualStub7(float _f5_x, unsigned int truncate_flags) {
  _fuse__F22F22F22F22F22F23(this, _f5_x, truncate_flags);
}
void runExp2(Node *n) {

  // n->differentiate();
  // n->differentiate();
  // n->differentiate();
  // n->differentiate();
  // n->differentiate();
  // n->project(0);

  // added by fuse transformer
  n->__virtualStub7(0, 0b111111);
}

void _fuse__F22F22F12F12F11F16F11F16F11F16F11F16(Leaf *_r, float _f4_c,
                                                 float _f6_c, float _f8_c,
                                                 float _f10_c,
                                                 unsigned int truncate_flags);
void _fuse__F6F9(Inner *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F20F20F7F7F6F9F6F9F6F9(Inner *_r, float _f4_c, float _f6_c,
                                   float _f8_c, unsigned int truncate_flags);
void _fuse__F1F4(Node *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F6F7(Inner *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F11F16(Leaf *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F13F14(Inner *_r, float _f0__s, float _f0__e, float _f1__s,
                   float _f1__e, unsigned int truncate_flags);
void _fuse__F11F12(Leaf *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F11F12F15F16F16F16F17(Leaf *_r, float _f0_c, float _f2_c,
                                  float _f2__s, float _f2__e, float _f6__a,
                                  float _f6__b, unsigned int truncate_flags);
void _fuse__F18F18F2F2F1F4F1F4F1F4F1F4(Node *_r, float _f4_c, float _f6_c,
                                       float _f8_c, float _f10_c,
                                       unsigned int truncate_flags);
void _fuse__F22F22F12F12F11F16F11F16F11F16(Leaf *_r, float _f4_c, float _f6_c,
                                           float _f8_c,
                                           unsigned int truncate_flags);
void _fuse__F1F2(Node *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F1F2F3F4F4F4F5(Node *_r, float _f0_c, float _f2_c, float _f2__s,
                           float _f2__e, float _f6__a, float _f6__b,
                           unsigned int truncate_flags);
void _fuse__F6F7F8F9F9F9F10(Inner *_r, float _f0_c, float _f2_c, float _f2__s,
                            float _f2__e, float _f6__a, float _f6__b,
                            unsigned int truncate_flags);
void _fuse__F3F4F4F4F5(Node *_r, float _f0_c, float _f0__s, float _f0__e,
                       float _f4__a, float _f4__b, unsigned int truncate_flags);
void _fuse__F20F20F7F7F6F9F6F9F6F9F6F9(Inner *_r, float _f4_c, float _f6_c,
                                       float _f8_c, float _f10_c,
                                       unsigned int truncate_flags);
void _fuse__F18F18F2F2F1F4F1F4F1F4(Node *_r, float _f4_c, float _f6_c,
                                   float _f8_c, unsigned int truncate_flags);
void _fuse__F18F18F18F18F18F19(Node *_r, float _f5_x,
                               unsigned int truncate_flags);
void _fuse__F15F16F16F16F17(Leaf *_r, float _f0_c, float _f0__s, float _f0__e,
                            float _f4__a, float _f4__b,
                            unsigned int truncate_flags);
void _fuse__F20F20F20F20F20F21(Inner *_r, float _f5_x,
                               unsigned int truncate_flags);
void _fuse__F8F9F9F9F10(Inner *_r, float _f0_c, float _f0__s, float _f0__e,
                        float _f4__a, float _f4__b,
                        unsigned int truncate_flags);
void _fuse__F22F22F22F22F22F23(Leaf *_r, float _f5_x,
                               unsigned int truncate_flags);
void _fuse__F22F22F12F12F11F16F11F16F11F16F11F16(Leaf *_r, float _f4_c,
                                                 float _f6_c, float _f8_c,
                                                 float _f10_c,
                                                 unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  Leaf *_r_f2 = (Leaf *)(_r);
  Leaf *_r_f3 = (Leaf *)(_r);
  Leaf *_r_f4 = (Leaf *)(_r);
  Leaf *_r_f5 = (Leaf *)(_r);
  Leaf *_r_f6 = (Leaf *)(_r);
  Leaf *_r_f7 = (Leaf *)(_r);
  Leaf *_r_f8 = (Leaf *)(_r);
  Leaf *_r_f9 = (Leaf *)(_r);
  Leaf *_r_f10 = (Leaf *)(_r);
  Leaf *_r_f11 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    _r_f0->coeff->differentiate();
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->differentiate();
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->coeff->square();
  }
_label_B1F2_Exit:
  if (truncate_flags & 0b1000) {
    _r_f3->coeff->square();
  }
_label_B1F3_Exit:
  if (truncate_flags & 0b10000) {
    _r_f4->coeff->addCons(_f4_c);
  }
_label_B1F4_Exit:
  if (truncate_flags & 0b100000) {
    _r_f5->coeff->mulVar();
  }
_label_B1F5_Exit:
  if (truncate_flags & 0b1000000) {
    _r_f6->coeff->addCons(_f6_c);
  }
_label_B1F6_Exit:
  if (truncate_flags & 0b10000000) {
    _r_f7->coeff->mulVar();
  }
_label_B1F7_Exit:
  if (truncate_flags & 0b100000000) {
    _r_f8->coeff->addCons(_f8_c);
  }
_label_B1F8_Exit:
  if (truncate_flags & 0b1000000000) {
    _r_f9->coeff->mulVar();
  }
_label_B1F9_Exit:
  if (truncate_flags & 0b10000000000) {
    _r_f10->coeff->addCons(_f10_c);
  }
_label_B1F10_Exit:
  if (truncate_flags & 0b100000000000) {
    _r_f11->coeff->mulVar();
  }
_label_B1F11_Exit:
  return;
};
void _fuse__F6F9(Inner *_r, float _f0_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->l->__virtualStub10(_f0_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->r->__virtualStub11(_f0_c, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F20F20F7F7F6F9F6F9F6F9(Inner *_r, float _f4_c, float _f6_c,
                                   float _f8_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  Inner *_r_f2 = (Inner *)(_r);
  Inner *_r_f3 = (Inner *)(_r);
  Inner *_r_f4 = (Inner *)(_r);
  Inner *_r_f5 = (Inner *)(_r);
  Inner *_r_f6 = (Inner *)(_r);
  Inner *_r_f7 = (Inner *)(_r);
  Inner *_r_f8 = (Inner *)(_r);
  Inner *_r_f9 = (Inner *)(_r);
  if ((truncate_flags & 0b1111111111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 9));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 8));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 7));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 6));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->l->__virtualStub8(_f4_c, _f6_c, _f8_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111111111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 9));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 8));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 7));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 6));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->r->__virtualStub9(_f4_c, _f6_c, _f8_c, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F1F4(Node *_r, float _f0_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  return;
};
void _fuse__F11F16(Leaf *_r, float _f0_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    _r_f0->coeff->addCons(_f0_c);
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->mulVar();
  }
_label_B1F1_Exit:
  return;
};
void _fuse__F18F18F2F2F1F4F1F4F1F4F1F4(Node *_r, float _f4_c, float _f6_c,
                                       float _f8_c, float _f10_c,
                                       unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  Node *_r_f2 = (Node *)(_r);
  Node *_r_f3 = (Node *)(_r);
  Node *_r_f4 = (Node *)(_r);
  Node *_r_f5 = (Node *)(_r);
  Node *_r_f6 = (Node *)(_r);
  Node *_r_f7 = (Node *)(_r);
  Node *_r_f8 = (Node *)(_r);
  Node *_r_f9 = (Node *)(_r);
  Node *_r_f10 = (Node *)(_r);
  Node *_r_f11 = (Node *)(_r);
  return;
};
void _fuse__F22F22F12F12F11F16F11F16F11F16(Leaf *_r, float _f4_c, float _f6_c,
                                           float _f8_c,
                                           unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  Leaf *_r_f2 = (Leaf *)(_r);
  Leaf *_r_f3 = (Leaf *)(_r);
  Leaf *_r_f4 = (Leaf *)(_r);
  Leaf *_r_f5 = (Leaf *)(_r);
  Leaf *_r_f6 = (Leaf *)(_r);
  Leaf *_r_f7 = (Leaf *)(_r);
  Leaf *_r_f8 = (Leaf *)(_r);
  Leaf *_r_f9 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    _r_f0->coeff->differentiate();
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->differentiate();
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->coeff->square();
  }
_label_B1F2_Exit:
  if (truncate_flags & 0b1000) {
    _r_f3->coeff->square();
  }
_label_B1F3_Exit:
  if (truncate_flags & 0b10000) {
    _r_f4->coeff->addCons(_f4_c);
  }
_label_B1F4_Exit:
  if (truncate_flags & 0b100000) {
    _r_f5->coeff->mulVar();
  }
_label_B1F5_Exit:
  if (truncate_flags & 0b1000000) {
    _r_f6->coeff->addCons(_f6_c);
  }
_label_B1F6_Exit:
  if (truncate_flags & 0b10000000) {
    _r_f7->coeff->mulVar();
  }
_label_B1F7_Exit:
  if (truncate_flags & 0b100000000) {
    _r_f8->coeff->addCons(_f8_c);
  }
_label_B1F8_Exit:
  if (truncate_flags & 0b1000000000) {
    _r_f9->coeff->mulVar();
  }
_label_B1F9_Exit:
  return;
};
void _fuse__F20F20F7F7F6F9F6F9F6F9F6F9(Inner *_r, float _f4_c, float _f6_c,
                                       float _f8_c, float _f10_c,
                                       unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  Inner *_r_f2 = (Inner *)(_r);
  Inner *_r_f3 = (Inner *)(_r);
  Inner *_r_f4 = (Inner *)(_r);
  Inner *_r_f5 = (Inner *)(_r);
  Inner *_r_f6 = (Inner *)(_r);
  Inner *_r_f7 = (Inner *)(_r);
  Inner *_r_f8 = (Inner *)(_r);
  Inner *_r_f9 = (Inner *)(_r);
  Inner *_r_f10 = (Inner *)(_r);
  Inner *_r_f11 = (Inner *)(_r);
  if ((truncate_flags & 0b1111111111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 9));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 8));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 7));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 6));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->l->__virtualStub8(_f4_c, _f6_c, _f8_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b110000000000)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 11));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 10));
    _r_f11->l->__virtualStub10(_f10_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111111111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 9));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 8));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 7));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 6));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->r->__virtualStub9(_f4_c, _f6_c, _f8_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b110000000000)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 11));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 10));
    _r_f11->r->__virtualStub11(_f10_c, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F18F18F2F2F1F4F1F4F1F4(Node *_r, float _f4_c, float _f6_c,
                                   float _f8_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  Node *_r_f2 = (Node *)(_r);
  Node *_r_f3 = (Node *)(_r);
  Node *_r_f4 = (Node *)(_r);
  Node *_r_f5 = (Node *)(_r);
  Node *_r_f6 = (Node *)(_r);
  Node *_r_f7 = (Node *)(_r);
  Node *_r_f8 = (Node *)(_r);
  Node *_r_f9 = (Node *)(_r);
  return;
};
void Node::__virtualStub10(float _f0_c, unsigned int truncate_flags) {
  _fuse__F1F4(this, _f0_c, truncate_flags);
}
void Inner::__virtualStub10(float _f0_c, unsigned int truncate_flags) {
  _fuse__F6F9(this, _f0_c, truncate_flags);
}
void Leaf::__virtualStub10(float _f0_c, unsigned int truncate_flags) {
  _fuse__F11F16(this, _f0_c, truncate_flags);
}
void Node::__virtualStub11(float _f0_c, unsigned int truncate_flags) {
  _fuse__F1F4(this, _f0_c, truncate_flags);
}
void Inner::__virtualStub11(float _f0_c, unsigned int truncate_flags) {
  _fuse__F6F9(this, _f0_c, truncate_flags);
}
void Leaf::__virtualStub11(float _f0_c, unsigned int truncate_flags) {
  _fuse__F11F16(this, _f0_c, truncate_flags);
}
void Node::__virtualStub8(float _f4_c, float _f6_c, float _f8_c,
                          unsigned int truncate_flags) {
  _fuse__F18F18F2F2F1F4F1F4F1F4(this, _f4_c, _f6_c, _f8_c, truncate_flags);
}
void Inner::__virtualStub8(float _f4_c, float _f6_c, float _f8_c,
                           unsigned int truncate_flags) {
  _fuse__F20F20F7F7F6F9F6F9F6F9(this, _f4_c, _f6_c, _f8_c, truncate_flags);
}
void Leaf::__virtualStub8(float _f4_c, float _f6_c, float _f8_c,
                          unsigned int truncate_flags) {
  _fuse__F22F22F12F12F11F16F11F16F11F16(this, _f4_c, _f6_c, _f8_c,
                                        truncate_flags);
}
void Node::__virtualStub9(float _f4_c, float _f6_c, float _f8_c,
                          unsigned int truncate_flags) {
  _fuse__F18F18F2F2F1F4F1F4F1F4(this, _f4_c, _f6_c, _f8_c, truncate_flags);
}
void Inner::__virtualStub9(float _f4_c, float _f6_c, float _f8_c,
                           unsigned int truncate_flags) {
  _fuse__F20F20F7F7F6F9F6F9F6F9(this, _f4_c, _f6_c, _f8_c, truncate_flags);
}
void Leaf::__virtualStub9(float _f4_c, float _f6_c, float _f8_c,
                          unsigned int truncate_flags) {
  _fuse__F22F22F12F12F11F16F11F16F11F16(this, _f4_c, _f6_c, _f8_c,
                                        truncate_flags);
}
void Node::__virtualStub12(float _f4_c, float _f6_c, float _f8_c, float _f10_c,
                           unsigned int truncate_flags) {
  _fuse__F18F18F2F2F1F4F1F4F1F4F1F4(this, _f4_c, _f6_c, _f8_c, _f10_c,
                                    truncate_flags);
}
void Inner::__virtualStub12(float _f4_c, float _f6_c, float _f8_c, float _f10_c,
                            unsigned int truncate_flags) {
  _fuse__F20F20F7F7F6F9F6F9F6F9F6F9(this, _f4_c, _f6_c, _f8_c, _f10_c,
                                    truncate_flags);
}
void Leaf::__virtualStub12(float _f4_c, float _f6_c, float _f8_c, float _f10_c,
                           unsigned int truncate_flags) {
  _fuse__F22F22F12F12F11F16F11F16F11F16F11F16(this, _f4_c, _f6_c, _f8_c, _f10_c,
                                              truncate_flags);
}
void runExp1(Node *n) {

  // n->differentiate();
  // n->differentiate();
  // n->square();
  // n->square();
  // n->addConst(1);
  // n->mulVar();
  // n->addConst(1);
  // n->mulVar();
  // n->addConst(1);
  // n->mulVar();
  // n->addConst(1);
  // n->mulVar();

  // added by fuse transformer
  n->__virtualStub12(1, 1, 1, 1, 0b111111111111);
}

void _fuse__F15F16F16F16F17(Leaf *_r, float _f0_c, float _f0__s, float _f0__e,
                            float _f4__a, float _f4__b,
                            unsigned int truncate_flags);
void _fuse__F8F9F9F9F10(Inner *_r, float _f0_c, float _f0__s, float _f0__e,
                        float _f4__a, float _f4__b,
                        unsigned int truncate_flags);
void _fuse__F3F4F4F4F5(Node *_r, float _f0_c, float _f0__s, float _f0__e,
                       float _f4__a, float _f4__b, unsigned int truncate_flags);
void _fuse__F1F2F3F4F4F4F5(Node *_r, float _f0_c, float _f2_c, float _f2__s,
                           float _f2__e, float _f6__a, float _f6__b,
                           unsigned int truncate_flags);
void _fuse__F1F2(Node *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F11F12F15F16F16F16F17(Leaf *_r, float _f0_c, float _f2_c,
                                  float _f2__s, float _f2__e, float _f6__a,
                                  float _f6__b, unsigned int truncate_flags);
void _fuse__F6F7F8F9F9F9F10(Inner *_r, float _f0_c, float _f2_c, float _f2__s,
                            float _f2__e, float _f6__a, float _f6__b,
                            unsigned int truncate_flags);
void _fuse__F11F12(Leaf *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F13F14(Inner *_r, float _f0__s, float _f0__e, float _f1__s,
                   float _f1__e, unsigned int truncate_flags);
void _fuse__F6F7(Inner *_r, float _f0_c, unsigned int truncate_flags);
void _fuse__F15F16F16F16F17(Leaf *_r, float _f0_c, float _f0__s, float _f0__e,
                            float _f4__a, float _f4__b,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  Leaf *_r_f2 = (Leaf *)(_r);
  Leaf *_r_f3 = (Leaf *)(_r);
  Leaf *_r_f4 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0__s >= _r_f0->endDom || _f0__e <= _r_f0->startDom) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
    _r_f0->coeff->multConst(_f0_c);
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->mulVar();
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->coeff->mulVar();
  }
_label_B1F2_Exit:
  if (truncate_flags & 0b1000) {
    _r_f3->coeff->mulVar();
  }
_label_B1F3_Exit:
  float _f4_b_;
  float _f4_a_;
  if (truncate_flags & 0b10000) {
    if (_f4__a > _r_f4->endDom || _f4__b < _r_f4->startDom) {
      _r_f4->projectVal = 0.0;
      truncate_flags &= 0b11111101111;
      goto _label_B1F4_Exit;
    }
    _f4_b_ = _f4__b;
    if (_f4__b > _r_f4->endDom) {
      _f4_b_ = _r_f4->endDom;
    }
    _f4_a_ = _f4__a;
    if (_f4__a < _r_f4->startDom) {
      _f4_a_ = _r_f4->startDom;
    }
    _r_f4->projectVal = _r_f4->coeff->boundedIntegrate(_f4_a_, _f4_b_);
  }
_label_B1F4_Exit:
  return;
};
void _fuse__F8F9F9F9F10(Inner *_r, float _f0_c, float _f0__s, float _f0__e,
                        float _f4__a, float _f4__b,
                        unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  Inner *_r_f2 = (Inner *)(_r);
  Inner *_r_f3 = (Inner *)(_r);
  Inner *_r_f4 = (Inner *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0__s >= _r_f0->endDom || _f0__e <= _r_f0->startDom) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b1)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _fuse__F13F14(_r_f0, _f0__s, _f0__e, _f0__s, _f0__e, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    ;
  }
_label_B2F0_Exit:
  float _f4_a_;
  float _f4_b_;
  if (truncate_flags & 0b10000) {
    if (_f4__a > _r_f4->endDom || _f4__b < _r_f4->startDom) {
      _r_f4->projectVal = 0.0;
      truncate_flags &= 0b11111101111;
      goto _label_B2F4_Exit;
    }
    _f4_a_ = _f4__a;
    if (_f4__a < _r_f4->startDom) {
      _f4_a_ = _r_f4->startDom;
    }
    _f4_b_ = _f4__b;
    if (_f4__b > _r_f4->endDom) {
      _f4_b_ = _r_f4->endDom;
    }
  }
_label_B2F4_Exit:
  if ((truncate_flags & 0b11111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f4->r->__virtualStub2(_f0_c, _f0__s, _f0__e, _f4_a_, _f4_b_,
                             AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f4->l->__virtualStub3(_f0_c, _f0__s, _f0__e, _f4_a_, _f4_b_,
                             AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10000) {
    _r_f4->projectVal = _r_f4->l->projectVal + _r_f4->r->projectVal;
  }
_label_B4F4_Exit:
  return;
};
void _fuse__F3F4F4F4F5(Node *_r, float _f0_c, float _f0__s, float _f0__e,
                       float _f4__a, float _f4__b,
                       unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  Node *_r_f2 = (Node *)(_r);
  Node *_r_f3 = (Node *)(_r);
  Node *_r_f4 = (Node *)(_r);
  return;
};
void _fuse__F1F2F3F4F4F4F5(Node *_r, float _f0_c, float _f2_c, float _f2__s,
                           float _f2__e, float _f6__a, float _f6__b,
                           unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  Node *_r_f2 = (Node *)(_r);
  Node *_r_f3 = (Node *)(_r);
  Node *_r_f4 = (Node *)(_r);
  Node *_r_f5 = (Node *)(_r);
  Node *_r_f6 = (Node *)(_r);
  return;
};
void _fuse__F1F2(Node *_r, float _f0_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Node *_r_f0 = (Node *)(_r);
  Node *_r_f1 = (Node *)(_r);
  return;
};
void _fuse__F11F12F15F16F16F16F17(Leaf *_r, float _f0_c, float _f2_c,
                                  float _f2__s, float _f2__e, float _f6__a,
                                  float _f6__b, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  Leaf *_r_f2 = (Leaf *)(_r);
  Leaf *_r_f3 = (Leaf *)(_r);
  Leaf *_r_f4 = (Leaf *)(_r);
  Leaf *_r_f5 = (Leaf *)(_r);
  Leaf *_r_f6 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    _r_f0->coeff->addCons(_f0_c);
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->square();
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    if (_f2__s >= _r_f2->endDom || _f2__e <= _r_f2->startDom) {
      truncate_flags &= 0b11111111011;
      goto _label_B1F2_Exit;
    }
    _r_f2->coeff->multConst(_f2_c);
  }
_label_B1F2_Exit:
  if (truncate_flags & 0b1000) {
    _r_f3->coeff->mulVar();
  }
_label_B1F3_Exit:
  if (truncate_flags & 0b10000) {
    _r_f4->coeff->mulVar();
  }
_label_B1F4_Exit:
  if (truncate_flags & 0b100000) {
    _r_f5->coeff->mulVar();
  }
_label_B1F5_Exit:
  float _f6_a_;
  float _f6_b_;
  if (truncate_flags & 0b1000000) {
    if (_f6__a > _r_f6->endDom || _f6__b < _r_f6->startDom) {
      _r_f6->projectVal = 0.0;
      truncate_flags &= 0b11110111111;
      goto _label_B1F6_Exit;
    }
    _f6_a_ = _f6__a;
    if (_f6__a < _r_f6->startDom) {
      _f6_a_ = _r_f6->startDom;
    }
    _f6_b_ = _f6__b;
    if (_f6__b > _r_f6->endDom) {
      _f6_b_ = _r_f6->endDom;
    }
    _r_f6->projectVal = _r_f6->coeff->boundedIntegrate(_f6_a_, _f6_b_);
  }
_label_B1F6_Exit:
  return;
};
void _fuse__F6F7F8F9F9F9F10(Inner *_r, float _f0_c, float _f2_c, float _f2__s,
                            float _f2__e, float _f6__a, float _f6__b,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  Inner *_r_f2 = (Inner *)(_r);
  Inner *_r_f3 = (Inner *)(_r);
  Inner *_r_f4 = (Inner *)(_r);
  Inner *_r_f5 = (Inner *)(_r);
  Inner *_r_f6 = (Inner *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->l->__virtualStub0(_f0_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->r->__virtualStub1(_f0_c, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100) {
    if (_f2__s >= _r_f2->endDom || _f2__e <= _r_f2->startDom) {
      truncate_flags &= 0b11111111011;
      goto _label_B3F2_Exit;
    }
  }
_label_B3F2_Exit:
  if ((truncate_flags & 0b100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _fuse__F13F14(_r_f2, _f2__s, _f2__e, _f2__s, _f2__e, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100) {
    ;
  }
_label_B4F2_Exit:
  float _f6_b_;
  float _f6_a_;
  if (truncate_flags & 0b1000000) {
    if (_f6__a > _r_f6->endDom || _f6__b < _r_f6->startDom) {
      _r_f6->projectVal = 0.0;
      truncate_flags &= 0b11110111111;
      goto _label_B4F6_Exit;
    }
    _f6_b_ = _f6__b;
    if (_f6__b > _r_f6->endDom) {
      _f6_b_ = _r_f6->endDom;
    }
    _f6_a_ = _f6__a;
    if (_f6__a < _r_f6->startDom) {
      _f6_a_ = _r_f6->startDom;
    }
  }
_label_B4F6_Exit:
  if ((truncate_flags & 0b1111100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 6));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f6->r->__virtualStub2(_f2_c, _f2__s, _f2__e, _f6_a_, _f6_b_,
                             AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 6));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 5));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f6->l->__virtualStub3(_f2_c, _f2__s, _f2__e, _f6_a_, _f6_b_,
                             AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1000000) {
    _r_f6->projectVal = _r_f6->l->projectVal + _r_f6->r->projectVal;
  }
_label_B6F6_Exit:
  return;
};
void _fuse__F11F12(Leaf *_r, float _f0_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Leaf *_r_f0 = (Leaf *)(_r);
  Leaf *_r_f1 = (Leaf *)(_r);
  if (truncate_flags & 0b1) {
    _r_f0->coeff->addCons(_f0_c);
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->coeff->square();
  }
_label_B1F1_Exit:
  return;
};
void _fuse__F13F14(Inner *_r, float _f0__s, float _f0__e, float _f1__s,
                   float _f1__e, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->l->type == LEAF &&
        ((_f0__s > _r_f0->l->startDom && _f0__s < _r_f0->l->endDom) ||
         (_f0__e > _r_f0->l->startDom && _f0__e < _r_f0->l->endDom))) {
      if ((_f0__s > _r_f0->l->startDom && _f0__s < _r_f0->l->endDom) &&
          (_f0__e > _r_f0->l->startDom && _f0__e < _r_f0->l->endDom)) {
        float _f0_s1 = _r_f0->l->startDom;
        float _f0_e1 = _f0__s;
        float _f0_s2 = _f0_e1;
        float _f0_e2 = _f0__e;
        float _f0_s3 = _f0_e2;
        float _f0_e3 = _r_f0->l->endDom;
        class Leaf *const _f0_oldNode = static_cast<class Leaf *>(_r_f0->l);
        _r_f0->l = new Inner();
        class Inner *const _f0_newInner1 = static_cast<class Inner *>(_r_f0->l);
        _f0_newInner1->type = INNER;
        _f0_newInner1->startDom = _f0_s1;
        _f0_newInner1->endDom = _f0_e3;
        _f0_newInner1->l = new Leaf();
        static_cast<class Leaf *>(_f0_newInner1->l)->coeff = new Poly();
        _f0_newInner1->l->type = LEAF;
        _f0_newInner1->l->startDom = _f0_s1;
        _f0_newInner1->l->endDom = _f0_e1;
        static_cast<class Leaf *>(_f0_newInner1->l)
            ->coeff->setArray(_f0_oldNode->coeff->arr,
                              _f0_oldNode->coeff->size);
        _f0_newInner1->r = new Inner();
        class Inner *const _f0_newInner2 =
            static_cast<class Inner *>(_f0_newInner1->r);
        _f0_newInner2->type = INNER;
        _f0_newInner2->startDom = _f0_s2;
        _f0_newInner2->endDom = _f0_e3;
        _f0_newInner2->l = new Leaf();
        static_cast<class Leaf *>(_f0_newInner2->l)->coeff = new Poly();
        _f0_newInner2->l->type = LEAF;
        _f0_newInner2->l->startDom = _f0_s2;
        _f0_newInner2->l->endDom = _f0_e2;
        static_cast<class Leaf *>(_f0_newInner2->l)
            ->coeff->setArray(_f0_oldNode->coeff->arr,
                              _f0_oldNode->coeff->size);
        _f0_newInner2->r = new Leaf();
        static_cast<class Leaf *>(_f0_newInner2->r)->coeff = new Poly();
        _f0_newInner2->r->type = LEAF;
        _f0_newInner2->r->startDom = _f0_s3;
        _f0_newInner2->r->endDom = _f0_e3;
        static_cast<class Leaf *>(_f0_newInner2->r)
            ->coeff->setArray(_f0_oldNode->coeff->arr,
                              _f0_oldNode->coeff->size);
        delete _f0_oldNode;
      } else {
        float _f0_s1 = _r_f0->l->startDom;
        float _f0_e1;
        if (_f0__s > _r_f0->l->startDom && _f0__s < _r_f0->l->endDom) {
          _f0_e1 = _f0__s;
        } else {
          _f0_e1 = _f0__e;
        }
        float _f0_s2 = _f0_e1;
        float _f0_e2 = _r_f0->l->endDom;
        class Leaf *const _f0_oldNode = static_cast<class Leaf *>(_r_f0->l);
        _r_f0->l = new Inner();
        _r_f0->l->type = INNER;
        class Inner *const _f0_newInner = static_cast<class Inner *>(_r_f0->l);
        _f0_newInner->type = INNER;
        _f0_newInner->startDom = _f0_s1;
        _f0_newInner->endDom = _f0_e2;
        _f0_newInner->l = new Leaf();
        static_cast<class Leaf *>(_f0_newInner->l)->coeff = new Poly();
        _f0_newInner->l->type = LEAF;
        _f0_newInner->l->startDom = _f0_s1;
        _f0_newInner->l->endDom = _f0_e1;
        static_cast<class Leaf *>(_f0_newInner->l)
            ->coeff->setArray(_f0_oldNode->coeff->arr,
                              _f0_oldNode->coeff->size);
        _f0_newInner->r = new Leaf();
        static_cast<class Leaf *>(_f0_newInner->r)->coeff = new Poly();
        _f0_newInner->r->type = LEAF;
        _f0_newInner->r->startDom = _f0_s2;
        _f0_newInner->r->endDom = _f0_e2;
        static_cast<class Leaf *>(_f0_newInner->r)
            ->coeff->setArray(_f0_oldNode->coeff->arr,
                              _f0_oldNode->coeff->size);
        delete _f0_oldNode;
      }
    }
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    if (_r_f1->r->type == LEAF &&
        ((_f1__s > _r_f1->r->startDom && _f1__s < _r_f1->r->endDom) ||
         (_f1__e > _r_f1->r->startDom && _f1__e < _r_f1->r->endDom))) {
      if ((_f1__s > _r_f1->r->startDom && _f1__s < _r_f1->r->endDom) &&
          (_f1__e > _r_f1->r->startDom && _f1__e < _r_f1->r->endDom)) {
        float _f1_s1 = _r_f1->r->startDom;
        float _f1_e1 = _f1__s;
        float _f1_s2 = _f1_e1;
        float _f1_e2 = _f1__e;
        float _f1_s3 = _f1_e2;
        float _f1_e3 = _r_f1->r->endDom;
        class Leaf *const _f1_oldNode = static_cast<class Leaf *>(_r_f1->r);
        _r_f1->r = new Inner();
        class Inner *const _f1_newInner1 = static_cast<class Inner *>(_r_f1->r);
        _f1_newInner1->type = INNER;
        _f1_newInner1->startDom = _f1_s1;
        _f1_newInner1->endDom = _f1_e3;
        _f1_newInner1->l = new Leaf();
        static_cast<class Leaf *>(_f1_newInner1->l)->coeff = new Poly();
        _f1_newInner1->l->type = LEAF;
        _f1_newInner1->l->startDom = _f1_s1;
        _f1_newInner1->l->endDom = _f1_e1;
        static_cast<class Leaf *>(_f1_newInner1->l)
            ->coeff->setArray(_f1_oldNode->coeff->arr,
                              _f1_oldNode->coeff->size);
        _f1_newInner1->r = new Inner();
        class Inner *const _f1_newInner2 =
            static_cast<class Inner *>(_f1_newInner1->r);
        _f1_newInner2->type = INNER;
        _f1_newInner2->startDom = _f1_s2;
        _f1_newInner2->endDom = _f1_e3;
        _f1_newInner2->l = new Leaf();
        static_cast<class Leaf *>(_f1_newInner2->l)->coeff = new Poly();
        _f1_newInner2->l->type = LEAF;
        _f1_newInner2->l->startDom = _f1_s2;
        _f1_newInner2->l->endDom = _f1_e2;
        static_cast<class Leaf *>(_f1_newInner2->l)
            ->coeff->setArray(_f1_oldNode->coeff->arr,
                              _f1_oldNode->coeff->size);
        _f1_newInner2->r = new Leaf();
        static_cast<class Leaf *>(_f1_newInner2->r)->coeff = new Poly();
        _f1_newInner2->r->type = LEAF;
        _f1_newInner2->r->startDom = _f1_s3;
        _f1_newInner2->r->endDom = _f1_e3;
        static_cast<class Leaf *>(_f1_newInner2->r)
            ->coeff->setArray(_f1_oldNode->coeff->arr,
                              _f1_oldNode->coeff->size);
        delete _f1_oldNode;
      } else {
        float _f1_s1 = _r_f1->r->startDom;
        float _f1_e1;
        if (_f1__s > _r_f1->r->startDom && _f1__s < _r_f1->r->endDom) {
          _f1_e1 = _f1__s;
        } else {
          _f1_e1 = _f1__e;
        }
        float _f1_s2 = _f1_e1;
        float _f1_e2 = _r_f1->r->endDom;
        class Leaf *const _f1_oldNode = static_cast<class Leaf *>(_r_f1->r);
        _r_f1->r = new Inner();
        _r_f1->r->type = INNER;
        class Inner *const _f1_newInner = static_cast<class Inner *>(_r_f1->r);
        _f1_newInner->type = INNER;
        _f1_newInner->startDom = _f1_s1;
        _f1_newInner->endDom = _f1_e2;
        _f1_newInner->l = new Leaf();
        static_cast<class Leaf *>(_f1_newInner->l)->coeff = new Poly();
        _f1_newInner->l->type = LEAF;
        _f1_newInner->l->startDom = _f1_s1;
        _f1_newInner->l->endDom = _f1_e1;
        static_cast<class Leaf *>(_f1_newInner->l)
            ->coeff->setArray(_f1_oldNode->coeff->arr,
                              _f1_oldNode->coeff->size);
        _f1_newInner->r = new Leaf();
        static_cast<class Leaf *>(_f1_newInner->r)->coeff = new Poly();
        _f1_newInner->r->type = LEAF;
        _f1_newInner->r->startDom = _f1_s2;
        _f1_newInner->r->endDom = _f1_e2;
        static_cast<class Leaf *>(_f1_newInner->r)
            ->coeff->setArray(_f1_oldNode->coeff->arr,
                              _f1_oldNode->coeff->size);
        delete _f1_oldNode;
      }
    }
  }
_label_B1F1_Exit:
  return;
};
void _fuse__F6F7(Inner *_r, float _f0_c, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Inner *_r_f0 = (Inner *)(_r);
  Inner *_r_f1 = (Inner *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->l->__virtualStub0(_f0_c, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->r->__virtualStub1(_f0_c, AdjustedTruncateFlags);
  }
  return;
};
void Node::__virtualStub0(float _f0_c, unsigned int truncate_flags) {
  _fuse__F1F2(this, _f0_c, truncate_flags);
}
void Inner::__virtualStub0(float _f0_c, unsigned int truncate_flags) {
  _fuse__F6F7(this, _f0_c, truncate_flags);
}
void Leaf::__virtualStub0(float _f0_c, unsigned int truncate_flags) {
  _fuse__F11F12(this, _f0_c, truncate_flags);
}
void Node::__virtualStub1(float _f0_c, unsigned int truncate_flags) {
  _fuse__F1F2(this, _f0_c, truncate_flags);
}
void Inner::__virtualStub1(float _f0_c, unsigned int truncate_flags) {
  _fuse__F6F7(this, _f0_c, truncate_flags);
}
void Leaf::__virtualStub1(float _f0_c, unsigned int truncate_flags) {
  _fuse__F11F12(this, _f0_c, truncate_flags);
}
void Node::__virtualStub3(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                          float _f4__b, unsigned int truncate_flags) {
  _fuse__F3F4F4F4F5(this, _f0_c, _f0__s, _f0__e, _f4__a, _f4__b,
                    truncate_flags);
}
void Inner::__virtualStub3(float _f0_c, float _f0__s, float _f0__e,
                           float _f4__a, float _f4__b,
                           unsigned int truncate_flags) {
  _fuse__F8F9F9F9F10(this, _f0_c, _f0__s, _f0__e, _f4__a, _f4__b,
                     truncate_flags);
}
void Leaf::__virtualStub3(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                          float _f4__b, unsigned int truncate_flags) {
  _fuse__F15F16F16F16F17(this, _f0_c, _f0__s, _f0__e, _f4__a, _f4__b,
                         truncate_flags);
}
void Node::__virtualStub2(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                          float _f4__b, unsigned int truncate_flags) {
  _fuse__F3F4F4F4F5(this, _f0_c, _f0__s, _f0__e, _f4__a, _f4__b,
                    truncate_flags);
}
void Inner::__virtualStub2(float _f0_c, float _f0__s, float _f0__e,
                           float _f4__a, float _f4__b,
                           unsigned int truncate_flags) {
  _fuse__F8F9F9F9F10(this, _f0_c, _f0__s, _f0__e, _f4__a, _f4__b,
                     truncate_flags);
}
void Leaf::__virtualStub2(float _f0_c, float _f0__s, float _f0__e, float _f4__a,
                          float _f4__b, unsigned int truncate_flags) {
  _fuse__F15F16F16F16F17(this, _f0_c, _f0__s, _f0__e, _f4__a, _f4__b,
                         truncate_flags);
}
void Node::__virtualStub4(float _f0_c, float _f2_c, float _f2__s, float _f2__e,
                          float _f6__a, float _f6__b,
                          unsigned int truncate_flags) {
  _fuse__F1F2F3F4F4F4F5(this, _f0_c, _f2_c, _f2__s, _f2__e, _f6__a, _f6__b,
                        truncate_flags);
}
void Inner::__virtualStub4(float _f0_c, float _f2_c, float _f2__s, float _f2__e,
                           float _f6__a, float _f6__b,
                           unsigned int truncate_flags) {
  _fuse__F6F7F8F9F9F9F10(this, _f0_c, _f2_c, _f2__s, _f2__e, _f6__a, _f6__b,
                         truncate_flags);
}
void Leaf::__virtualStub4(float _f0_c, float _f2_c, float _f2__s, float _f2__e,
                          float _f6__a, float _f6__b,
                          unsigned int truncate_flags) {
  _fuse__F11F12F15F16F16F16F17(this, _f0_c, _f2_c, _f2__s, _f2__e, _f6__a,
                               _f6__b, truncate_flags);
}
void runExp3(Node *n) {

  // n->addConst(3.5);
  // n->square();
  // n->rangeMulConst(0, -10000, 0);
  // n->mulVar();
  // n->mulVar();
  // n->mulVar();
  // n->boundedIntegrate(-100000, 100000);

  // added by fuse transformer
  n->__virtualStub4(3.5, 0, -10000, 0, -100000, 100000, 0b1111111);
}

// void runExp1(int n) {
//   Node *exp1 = new Inner();
//   exp1->type = INNER;
//   exp1->buildTree(1, 0, 4, 0, n);
//   exp1->addConst(1);

//   for (int i = 0; i < n; i += 7) {
//     exp1->rangeMulConst(i, i - 1, i);
//     exp1->rangeMulConst(i + 1, i, i + 1);
//     exp1->rangeMulConst(i + 2, i + 1, i + 2);
//     exp1->rangeMulConst(i + 3, i + 2, i + 3);
//     exp1->rangeMulConst(i + 4, i + 3, i + 4);
//     exp1->rangeMulConst(i + 5, i + 1, i + 5);
//     exp1->rangeMulConst(i + 6, i + 2, i + 6);
//     exp1->rangeMulConst(i + 7, i + 3, i + 7);
//   }
//   exp1->mulVar();
//   exp1->mulVar();

//   Node *exp2 = new Inner();
//   exp2->type = INNER;
//   exp2->buildTree(1, 0, 1, 0, n);
//   exp2->addConst(1);

//   for (int i = 0; i < n; i += 7) {
//     exp2->rangeMulConst(i, i - 1, i);
//     exp2->rangeMulConst(i + 1, i, i + 1);
//     exp2->rangeMulConst(i + 2, i + 1, i + 2);
//     exp2->rangeMulConst(i + 3, i + 2, i + 3);
//     exp2->rangeMulConst(i + 4, i + 3, i + 4);
//     exp2->rangeMulConst(i + 5, i + 1, i + 5);
//     exp2->rangeMulConst(i + 6, i + 2, i + 6);
//     exp2->rangeMulConst(i + 7, i + 3, i + 7);
//   }
//   exp2->mulVar();
//   exp2->boundedIntegrate(0, n);

//   auto res = exp1->projectVal + exp2->projectVal;
// }

int main(int argc, char **argv) {

  int n = atoi(argv[1]);
  int prog = atoi(argv[2]);

  auto T = new Inner();
  T->type = INNER;
  T->buildTree(n, 0, 4, -100000, 100000);

#ifdef PAPI
  start_counters();
#endif
  auto t1 = std::chrono::high_resolution_clock::now();
  if (prog == 1)
    runExp1(T);
  else if (prog == 2)
    runExp2(T);
  else if (prog == 3)
    runExp3(T);

  auto t2 = std::chrono::high_resolution_clock::now();
#ifdef PAPI
  read_counters();
  print_counters();
#endif
  printf(
      "Runtime: %llu microseconds\n",
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());

  return 0;
};
