#ifndef AST
#define AST
#define __tree_structure__ __attribute__((annotate("tf_tree")))
#define __tree_child__ __attribute__((annotate("tf_child")))
#define __tree_traversal__ __attribute__((annotate("tf_fuse")))
#include <string>
enum ASTNodeType { STMT, EXPR, FUNCTION, SEQ };
enum ASTStmtType { ASSIGNMENT, IF, NOP, INC, DECR };
enum ASTExprType { CONSTANT, BINARY, VARREF };
enum ExprOperator { ADD, SUBTRACT };

#ifdef COUNT_VISITS
int _VISIT_COUNTER = 0;
#endif

class StatementNode;

class __tree_structure__ ASTNode {
public:
  ASTNodeType NodeType;
  __tree_traversal__ virtual void foldConstants() {}
  __tree_traversal__ virtual void replaceVarRefWithConst(int VarRefId,
                                                         int Val){};
  __tree_traversal__ virtual void propagateConstantsAssignments(){};
  __tree_traversal__ virtual void removeUnreachableBranches(){};
  __tree_traversal__ virtual void deleteChildren(){};
  __tree_traversal__ virtual void desugarInc(){};
  __tree_traversal__ virtual void desugarDecr(){};
  virtual int computeSize() { return 0; };
  virtual void print(){};
  bool ChangedFolding = false;
  bool ChangedPropagation = false;
};

class __tree_structure__ StmtListNode : public ASTNode {
public:
  __tree_child__ StatementNode *Stmt;
virtual void __virtualStub11(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub8(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub4(unsigned int truncate_flags);
virtual void __virtualStub7(unsigned int truncate_flags);
virtual void __virtualStub10(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub17(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub13(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub18(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub2(unsigned int truncate_flags);
virtual void __virtualStub19(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
virtual void __virtualStub20(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
virtual void __virtualStub28(unsigned int truncate_flags);
virtual void __virtualStub22(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
virtual void __virtualStub25(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
virtual void __virtualStub30(unsigned int truncate_flags);
virtual void __virtualStub23(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
virtual void __virtualStub26(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
};

class __tree_structure__ StmtListInner : public StmtListNode {
public:
  __tree_child__ StmtListNode *Next;
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void propagateConstantsAssignments() override;
  __tree_traversal__ void replaceVarRefWithConst(int VarRefId,
                                                 int Val) override;
  __tree_traversal__ void removeUnreachableBranches() override;
  __tree_traversal__ void desugarInc() override;
  __tree_traversal__ void desugarDecr() override;
  int computeSize() override;

  void print() override;
 void __virtualStub11(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub8(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub4(unsigned int truncate_flags)override;
 void __virtualStub7(unsigned int truncate_flags)override;
 void __virtualStub10(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub17(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub13(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub18(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub2(unsigned int truncate_flags)override;
 void __virtualStub19(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub20(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub28(unsigned int truncate_flags)override;
 void __virtualStub22(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub25(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub30(unsigned int truncate_flags)override;
 void __virtualStub23(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub26(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ StmtListEnd : public StmtListNode {
public:
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void replaceVarRefWithConst(int VarRefId,
                                                 int Val) override;
  __tree_traversal__ void propagateConstantsAssignments() override;
  __tree_traversal__ void removeUnreachableBranches() override;
  __tree_traversal__ void desugarInc() override;
  __tree_traversal__ void desugarDecr() override;
  int computeSize() override;

  void print() override;
 void __virtualStub11(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub8(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub4(unsigned int truncate_flags)override;
 void __virtualStub7(unsigned int truncate_flags)override;
 void __virtualStub10(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub17(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub13(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub18(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub2(unsigned int truncate_flags)override;
 void __virtualStub19(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub20(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub28(unsigned int truncate_flags)override;
 void __virtualStub22(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub25(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub30(unsigned int truncate_flags)override;
 void __virtualStub23(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub26(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ Function : public ASTNode {
public:
  std::string FunctionName = "not-set";
  __tree_child__ StmtListNode *StmtList;
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void propagateConstantsAssignments() override;
  __tree_traversal__ void removeUnreachableBranches() override;
  __tree_traversal__ void desugarInc() override;
  __tree_traversal__ void desugarDecr() override;
  int computeSize() override;

  void print() override;
virtual void __virtualStub1(unsigned int truncate_flags);
virtual void __virtualStub32(unsigned int truncate_flags);
};

class __tree_structure__ FunctionList : public ASTNode {
public:
  __tree_child__ Function *Content;
virtual void __virtualStub0(unsigned int truncate_flags);
virtual void __virtualStub31(unsigned int truncate_flags);
};

class __tree_structure__ FunctionListInner : public FunctionList {
public:
  __tree_child__ FunctionList *Next;
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void propagateConstantsAssignments() override;
  __tree_traversal__ void removeUnreachableBranches() override;
  __tree_traversal__ void desugarInc() override;
  __tree_traversal__ void desugarDecr() override;
  int computeSize() override;

  void print() override;
 void __virtualStub0(unsigned int truncate_flags)override;
 void __virtualStub31(unsigned int truncate_flags)override;
};

class __tree_structure__ FunctionListEnd : public FunctionList {
public:
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void propagateConstantsAssignments() override;
  __tree_traversal__ void removeUnreachableBranches() override;
  __tree_traversal__ void desugarInc() override;
  __tree_traversal__ void desugarDecr() override;
  int computeSize() override;

  void print() override;
 void __virtualStub0(unsigned int truncate_flags)override;
 void __virtualStub31(unsigned int truncate_flags)override;
};

class __tree_structure__ Program : public ASTNode {
public:
  __tree_child__ FunctionList *Functions;
  __tree_traversal__ void foldConstants();
  __tree_traversal__ void propagateConstantsAssignments();
  __tree_traversal__ void removeUnreachableBranches();
  __tree_traversal__ void desugarInc();
  __tree_traversal__ void desugarDecr();
  int computeSize();
  void print();
virtual void __virtualStub33(unsigned int truncate_flags);
};

class __tree_structure__ ExpressionNode : public ASTNode {
public:
  ASTExprType ExpressionType;
virtual void __virtualStub15(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub16(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
};

class __tree_structure__ BinaryExpr : public ExpressionNode {
public:
  __tree_child__ ExpressionNode *LHS = 0;
  __tree_child__ ExpressionNode *RHS = 0;
  ExprOperator Operator;
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void replaceVarRefWithConst(int VarRefId,

                                                 int Val) override;
  int computeSize() override;
  void print() override;
 void __virtualStub15(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub16(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ VarRefExpr : public ExpressionNode {
public:
  int VarId;
  int computeSize() override;

  void print() override;
 void __virtualStub15(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub16(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ ConstantExpr : public ExpressionNode {
public:
  int Value;
  int computeSize() override;

  void print() override;
 void __virtualStub15(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub16(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
};
class __tree_structure__ StatementNode : public ASTNode {
public:
  ASTStmtType StatementType;
virtual void __virtualStub5(unsigned int truncate_flags);
virtual void __virtualStub3(unsigned int truncate_flags);
virtual void __virtualStub6(unsigned int truncate_flags);
virtual void __virtualStub9(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub12(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub14(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags);
virtual void __virtualStub29(unsigned int truncate_flags);
virtual void __virtualStub27(unsigned int truncate_flags);
virtual void __virtualStub21(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
virtual void __virtualStub24(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags);
};

class __tree_structure__ AssignStmt : public StatementNode {
public:
  __tree_child__ VarRefExpr *Id;
  bool IsMutable;
  __tree_child__ ExpressionNode *AssignedExpr;
  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void replaceVarRefWithConst(int VarRefId,
                                                 int Val) override;
  int computeSize() override;

  void print() override;
 void __virtualStub5(unsigned int truncate_flags)override;
 void __virtualStub3(unsigned int truncate_flags)override;
 void __virtualStub6(unsigned int truncate_flags)override;
 void __virtualStub9(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub12(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub14(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub29(unsigned int truncate_flags)override;
 void __virtualStub27(unsigned int truncate_flags)override;
 void __virtualStub21(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub24(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ IncrStmt : public StatementNode {
public:
  __tree_child__ VarRefExpr *Id;
  int computeSize() override;

  void print() override;
 void __virtualStub5(unsigned int truncate_flags)override;
 void __virtualStub3(unsigned int truncate_flags)override;
 void __virtualStub6(unsigned int truncate_flags)override;
 void __virtualStub9(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub12(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub14(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub29(unsigned int truncate_flags)override;
 void __virtualStub27(unsigned int truncate_flags)override;
 void __virtualStub21(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub24(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ DecrStmt : public StatementNode {
public:
  __tree_child__ VarRefExpr *Id;
  int computeSize() override;

  void print() override;
 void __virtualStub5(unsigned int truncate_flags)override;
 void __virtualStub3(unsigned int truncate_flags)override;
 void __virtualStub6(unsigned int truncate_flags)override;
 void __virtualStub9(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub12(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub14(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub29(unsigned int truncate_flags)override;
 void __virtualStub27(unsigned int truncate_flags)override;
 void __virtualStub21(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub24(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ IfStmt : public StatementNode {
public:
  __tree_child__ ExpressionNode *Condition;
  __tree_child__ StmtListNode *ThenPart;
  __tree_child__ StmtListNode *ElsePart;

  __tree_traversal__ void foldConstants() override;
  __tree_traversal__ void replaceVarRefWithConst(int VarRefId,
                                                 int Val) override;
  __tree_traversal__ void propagateConstantsAssignments() override;

  __tree_traversal__ void removeUnreachableBranches() override;
  __tree_traversal__ void desugarInc() override;
  __tree_traversal__ void desugarDecr() override;
  int computeSize() override;

  void print() override;
 void __virtualStub5(unsigned int truncate_flags)override;
 void __virtualStub3(unsigned int truncate_flags)override;
 void __virtualStub6(unsigned int truncate_flags)override;
 void __virtualStub9(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub12(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub14(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub29(unsigned int truncate_flags)override;
 void __virtualStub27(unsigned int truncate_flags)override;
 void __virtualStub21(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub24(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

class __tree_structure__ NullStmt : public StatementNode {

public:
 void __virtualStub5(unsigned int truncate_flags)override;
 void __virtualStub3(unsigned int truncate_flags)override;
 void __virtualStub6(unsigned int truncate_flags)override;
 void __virtualStub9(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub12(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub14(int _f0_VarRefId, int _f0_Val, unsigned int truncate_flags)override;
 void __virtualStub29(unsigned int truncate_flags)override;
 void __virtualStub27(unsigned int truncate_flags)override;
 void __virtualStub21(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
 void __virtualStub24(int _f2_VarRefId, int _f2_Val, unsigned int truncate_flags)override;
};

#endif
