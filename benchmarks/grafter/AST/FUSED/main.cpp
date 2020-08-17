#include "AST.h"
#include "ASTBuilder.h"
#include "ConstantFolding.h"
#include "ConstantPropagationAssigment.h"
#include "DesugarDec.h"
#include "DesugarInc.h"
#include "Print.h"
#include "RemoveUnreachableBranches.h"
#include "computeSize.h"
#include <chrono>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>

#pragma clang diagnostic ignored "-Wdeprecated-declarations"

using namespace std;

#ifdef PAPI
#include <iostream>
#include <papi.h>
#define SIZE 3
string instance("Original");
int ret;
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

void _fuse__F41F42F27F28(IfStmt *_r, unsigned int truncate_flags);
void _fuse__F39F40F30F31(StmtListEnd *_r, unsigned int truncate_flags);
void _fuse__F6F7F8F9(ASTNode *_r, unsigned int truncate_flags);
void _fuse__F41F42F27F28F29(IfStmt *_r, unsigned int truncate_flags);
void _fuse__F6F7F8F26F10(AssignStmt *_r, unsigned int truncate_flags);
void _fuse__F32F8F9(ASTNode *_r, int _f0_VarRefId, int _f0_Val,
                    unsigned int truncate_flags);
void _fuse__F6F7F8F26(AssignStmt *_r, unsigned int truncate_flags);
void _fuse__F8F26(AssignStmt *_r, unsigned int truncate_flags);
void _fuse__F6F7F34(AssignStmt *_r, int _f2_VarRefId, int _f2_Val,
                    unsigned int truncate_flags);
void _fuse__F21F22F33(StmtListInner *_r, int _f2_VarRefId, int _f2_Val,
                      unsigned int truncate_flags);
void _fuse__F23F24(StmtListInner *_r, unsigned int truncate_flags);
void _fuse__F39F40F36(StmtListEnd *_r, int _f2_VarRefId, int _f2_Val,
                      unsigned int truncate_flags);
void _fuse__F33F23(StmtListInner *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags);
void _fuse__F8F26F10(AssignStmt *_r, unsigned int truncate_flags);
void _fuse__F36F30(StmtListEnd *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags);
void _fuse__F6F7F8F9F10(ASTNode *_r, unsigned int truncate_flags);
void _fuse__F30F31(StmtListEnd *_r, unsigned int truncate_flags);
void _fuse__F1F2F3F4F5(Program *_r, unsigned int truncate_flags);
void _fuse__F33F23F24(StmtListInner *_r, int _f0_VarRefId, int _f0_Val,
                      unsigned int truncate_flags);
void _fuse__F44F45F46F47F48(FunctionListEnd *_r, unsigned int truncate_flags);
void _fuse__F21F22F23F24(StmtListInner *_r, unsigned int truncate_flags);
void _fuse__F11F12F13F14F15(FunctionListInner *_r, unsigned int truncate_flags);
void _fuse__F36F30F31(StmtListEnd *_r, int _f0_VarRefId, int _f0_Val,
                      unsigned int truncate_flags);
void _fuse__F8F9F10(ASTNode *_r, unsigned int truncate_flags);
void _fuse__F6F7F34F8F26(AssignStmt *_r, int _f2_VarRefId, int _f2_Val,
                         unsigned int truncate_flags);
void _fuse__F32F8(ASTNode *_r, int _f0_VarRefId, int _f0_Val,
                  unsigned int truncate_flags);
void _fuse__F16F17F18F19F20(Function *_r, unsigned int truncate_flags);
void _fuse__F27F28F29(IfStmt *_r, unsigned int truncate_flags);
void _fuse__F21F22F23F24F25(StmtListInner *_r, unsigned int truncate_flags);
void _fuse__F6F7F32F8F9(ASTNode *_r, int _f2_VarRefId, int _f2_Val,
                        unsigned int truncate_flags);
void _fuse__F34F8(AssignStmt *_r, int _f0_VarRefId, int _f0_Val,
                  unsigned int truncate_flags);
void _fuse__F35F27(IfStmt *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags);
void _fuse__F34F8F26(AssignStmt *_r, int _f0_VarRefId, int _f0_Val,
                     unsigned int truncate_flags);
void _fuse__F32F9(ASTNode *_r, int _f0_VarRefId, int _f0_Val,
                  unsigned int truncate_flags);
void _fuse__F37F38(BinaryExpr *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags);
void _fuse__F39F40F36F30F31(StmtListEnd *_r, int _f2_VarRefId, int _f2_Val,
                            unsigned int truncate_flags);
void _fuse__F27F28(IfStmt *_r, unsigned int truncate_flags);
void _fuse__F21F22F33F23F24(StmtListInner *_r, int _f2_VarRefId, int _f2_Val,
                            unsigned int truncate_flags);
void _fuse__F6F7F32(ASTNode *_r, int _f2_VarRefId, int _f2_Val,
                    unsigned int truncate_flags);
void _fuse__F41F42F35(IfStmt *_r, int _f2_VarRefId, int _f2_Val,
                      unsigned int truncate_flags);
void _fuse__F35F27F28(IfStmt *_r, int _f0_VarRefId, int _f0_Val,
                      unsigned int truncate_flags);
void _fuse__F41F42F35F27F28(IfStmt *_r, int _f2_VarRefId, int _f2_Val,
                            unsigned int truncate_flags);
void _fuse__F8F9(ASTNode *_r, unsigned int truncate_flags);
void _fuse__F39F40F30F31F43(StmtListEnd *_r, unsigned int truncate_flags);
void _fuse__F41F42F27F28(IfStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  IfStmt *_r_f2 = (IfStmt *)(_r);
  IfStmt *_r_f3 = (IfStmt *)(_r);
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub28(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub30(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1000)) /*call*/ {
    _r_f3->Condition->foldConstants();
  }
  if (truncate_flags & 0b1000) {
    if (_r_f3->Condition->ExpressionType == BINARY) {
      class BinaryExpr *const _f3_Condition_ =
          static_cast<class BinaryExpr *>(_r_f3->Condition);
      if (_f3_Condition_->LHS->ExpressionType == CONSTANT &&
          _f3_Condition_->RHS->ExpressionType == CONSTANT) {
        int _f3_NewValue;
        if (_f3_Condition_->Operator == ADD) {
          _f3_NewValue =
              static_cast<class ConstantExpr *>(_f3_Condition_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f3_Condition_->RHS)->Value;
        }
        if (_f3_Condition_->Operator == SUBTRACT) {
          _f3_NewValue =
              static_cast<class ConstantExpr *>(_f3_Condition_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f3_Condition_->RHS)->Value;
        }
        delete _f3_Condition_->LHS;
        delete _f3_Condition_->RHS;
        delete _f3_Condition_;
        _r_f3->Condition = new ConstantExpr();
        _r_f3->Condition->NodeType = ASTNodeType::EXPR;
        _r_f3->Condition->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f3->Condition)->Value =
            _f3_NewValue;
      }
    }
  }
_label_B4F3_Exit:
  return;
};
void _fuse__F39F40F30F31(StmtListEnd *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f2 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f3 = (StmtListEnd *)(_r);
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Stmt->__virtualStub29(AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F6F7F8F9(ASTNode *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  ASTNode *_r_f3 = (ASTNode *)(_r);
  return;
};
void _fuse__F41F42F27F28F29(IfStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  IfStmt *_r_f2 = (IfStmt *)(_r);
  IfStmt *_r_f3 = (IfStmt *)(_r);
  IfStmt *_r_f4 = (IfStmt *)(_r);
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub28(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub30(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1000)) /*call*/ {
    _r_f3->Condition->foldConstants();
  }
  if (truncate_flags & 0b1000) {
    if (_r_f3->Condition->ExpressionType == BINARY) {
      class BinaryExpr *const _f3_Condition_ =
          static_cast<class BinaryExpr *>(_r_f3->Condition);
      if (_f3_Condition_->LHS->ExpressionType == CONSTANT &&
          _f3_Condition_->RHS->ExpressionType == CONSTANT) {
        int _f3_NewValue;
        if (_f3_Condition_->Operator == ADD) {
          _f3_NewValue =
              static_cast<class ConstantExpr *>(_f3_Condition_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f3_Condition_->RHS)->Value;
        }
        if (_f3_Condition_->Operator == SUBTRACT) {
          _f3_NewValue =
              static_cast<class ConstantExpr *>(_f3_Condition_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f3_Condition_->RHS)->Value;
        }
        delete _f3_Condition_->LHS;
        delete _f3_Condition_->RHS;
        delete _f3_Condition_;
        _r_f3->Condition = new ConstantExpr();
        _r_f3->Condition->NodeType = ASTNodeType::EXPR;
        _r_f3->Condition->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f3->Condition)->Value =
            _f3_NewValue;
      }
    }
  }
_label_B4F3_Exit:
  if (truncate_flags & 0b10000) {
    if (_r_f4->Condition->ExpressionType == CONSTANT) {
      class ConstantExpr *const _f4_ConstantCond =
          static_cast<class ConstantExpr *>(_r_f4->Condition);
      if (_f4_ConstantCond->Value == 0) {
        delete _r_f4->ThenPart;
        _r_f4->ThenPart = new StmtListEnd();
        _r_f4->ThenPart->NodeType = SEQ;
        _r_f4->ThenPart->Stmt = new NullStmt();
        _r_f4->ThenPart->Stmt->NodeType = STMT;
        _r_f4->ThenPart->Stmt->StatementType = NOP;
      }
      if (_f4_ConstantCond->Value != 0) {
        delete _r_f4->ElsePart;
        _r_f4->ElsePart = new StmtListEnd();
        _r_f4->ElsePart->NodeType = SEQ;
        _r_f4->ElsePart->Stmt = new NullStmt();
        _r_f4->ElsePart->Stmt->NodeType = STMT;
        _r_f4->ElsePart->Stmt->StatementType = NOP;
      }
    }
  }
_label_B4F4_Exit:
  if ((truncate_flags & 0b10000)) /*call*/ {
    _r_f4->ThenPart->removeUnreachableBranches();
  }
  if ((truncate_flags & 0b10000)) /*call*/ {
    _r_f4->ElsePart->removeUnreachableBranches();
  }
  return;
};
void _fuse__F6F7F8F26F10(AssignStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  AssignStmt *_r_f3 = (AssignStmt *)(_r);
  ASTNode *_r_f4 = (ASTNode *)(_r);
  if ((truncate_flags & 0b1000)) /*call*/ {
    _r_f3->AssignedExpr->foldConstants();
  }
  class BinaryExpr *_f3_AssignedExpr_;
  int _f3_NewValue;
  if (truncate_flags & 0b1000) {
    if (_r_f3->AssignedExpr->ExpressionType != BINARY) {
      truncate_flags &= 0b11111110111;
      goto _label_B2F3_Exit;
    }
    _f3_AssignedExpr_ = static_cast<class BinaryExpr *>(_r_f3->AssignedExpr);
    if (_f3_AssignedExpr_->LHS->ExpressionType != CONSTANT ||
        _f3_AssignedExpr_->RHS->ExpressionType != CONSTANT) {
      truncate_flags &= 0b11111110111;
      goto _label_B2F3_Exit;
    }
    if (_f3_AssignedExpr_->Operator == ADD) {
      _f3_NewValue =
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->LHS)->Value +
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->RHS)->Value;
    }
    if (_f3_AssignedExpr_->Operator == SUBTRACT) {
      _f3_NewValue =
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->LHS)->Value -
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->RHS)->Value;
    }
    delete _f3_AssignedExpr_->LHS;
    delete _f3_AssignedExpr_->RHS;
    delete _r_f3->AssignedExpr;
    _r_f3->AssignedExpr = new ConstantExpr();
    static_cast<class ConstantExpr *>(_r_f3->AssignedExpr)->Value =
        _f3_NewValue;
    _r_f3->AssignedExpr->NodeType = ASTNodeType::EXPR;
    _r_f3->AssignedExpr->ExpressionType = ASTExprType::CONSTANT;
  }
_label_B2F3_Exit:
  return;
};
void _fuse__F32F8F9(ASTNode *_r, int _f0_VarRefId, int _f0_Val,
                    unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  return;
};
void _fuse__F6F7F8F26(AssignStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  AssignStmt *_r_f3 = (AssignStmt *)(_r);
  if ((truncate_flags & 0b1000)) /*call*/ {
    _r_f3->AssignedExpr->foldConstants();
  }
  class BinaryExpr *_f3_AssignedExpr_;
  int _f3_NewValue;
  if (truncate_flags & 0b1000) {
    if (_r_f3->AssignedExpr->ExpressionType != BINARY) {
      truncate_flags &= 0b11111110111;
      goto _label_B2F3_Exit;
    }
    _f3_AssignedExpr_ = static_cast<class BinaryExpr *>(_r_f3->AssignedExpr);
    if (_f3_AssignedExpr_->LHS->ExpressionType != CONSTANT ||
        _f3_AssignedExpr_->RHS->ExpressionType != CONSTANT) {
      truncate_flags &= 0b11111110111;
      goto _label_B2F3_Exit;
    }
    if (_f3_AssignedExpr_->Operator == ADD) {
      _f3_NewValue =
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->LHS)->Value +
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->RHS)->Value;
    }
    if (_f3_AssignedExpr_->Operator == SUBTRACT) {
      _f3_NewValue =
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->LHS)->Value -
          static_cast<class ConstantExpr *>(_f3_AssignedExpr_->RHS)->Value;
    }
    delete _f3_AssignedExpr_->LHS;
    delete _f3_AssignedExpr_->RHS;
    delete _r_f3->AssignedExpr;
    _r_f3->AssignedExpr = new ConstantExpr();
    static_cast<class ConstantExpr *>(_r_f3->AssignedExpr)->Value =
        _f3_NewValue;
    _r_f3->AssignedExpr->NodeType = ASTNodeType::EXPR;
    _r_f3->AssignedExpr->ExpressionType = ASTExprType::CONSTANT;
  }
_label_B2F3_Exit:
  return;
};
void _fuse__F8F26(AssignStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  AssignStmt *_r_f1 = (AssignStmt *)(_r);
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->AssignedExpr->foldConstants();
  }
  class BinaryExpr *_f1_AssignedExpr_;
  int _f1_NewValue;
  if (truncate_flags & 0b10) {
    if (_r_f1->AssignedExpr->ExpressionType != BINARY) {
      truncate_flags &= 0b11111111101;
      goto _label_B2F1_Exit;
    }
    _f1_AssignedExpr_ = static_cast<class BinaryExpr *>(_r_f1->AssignedExpr);
    if (_f1_AssignedExpr_->LHS->ExpressionType != CONSTANT ||
        _f1_AssignedExpr_->RHS->ExpressionType != CONSTANT) {
      truncate_flags &= 0b11111111101;
      goto _label_B2F1_Exit;
    }
    if (_f1_AssignedExpr_->Operator == ADD) {
      _f1_NewValue =
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->LHS)->Value +
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->RHS)->Value;
    }
    if (_f1_AssignedExpr_->Operator == SUBTRACT) {
      _f1_NewValue =
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->LHS)->Value -
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->RHS)->Value;
    }
    delete _f1_AssignedExpr_->LHS;
    delete _f1_AssignedExpr_->RHS;
    delete _r_f1->AssignedExpr;
    _r_f1->AssignedExpr = new ConstantExpr();
    static_cast<class ConstantExpr *>(_r_f1->AssignedExpr)->Value =
        _f1_NewValue;
    _r_f1->AssignedExpr->NodeType = ASTNodeType::EXPR;
    _r_f1->AssignedExpr->ExpressionType = ASTExprType::CONSTANT;
  }
_label_B2F1_Exit:
  return;
};
void _fuse__F6F7F34(AssignStmt *_r, int _f2_VarRefId, int _f2_Val,
                    unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  AssignStmt *_r_f2 = (AssignStmt *)(_r);
  if (truncate_flags & 0b100) {
    if (_r_f2->AssignedExpr->ExpressionType == VARREF &&
        static_cast<class VarRefExpr *>(_r_f2->AssignedExpr)->VarId ==
            _f2_VarRefId) {
      delete _r_f2->AssignedExpr;
      _r_f2->AssignedExpr = new ConstantExpr();
      static_cast<class ConstantExpr *>(_r_f2->AssignedExpr)->ExpressionType =
          CONSTANT;
      static_cast<class ConstantExpr *>(_r_f2->AssignedExpr)->Value = _f2_Val;
    }
  }
_label_B1F2_Exit:
  if ((truncate_flags & 0b100)) /*call*/ {
    _r_f2->AssignedExpr->replaceVarRefWithConst(_f2_VarRefId, _f2_Val);
  }
  return;
};
void _fuse__F21F22F33(StmtListInner *_r, int _f2_VarRefId, int _f2_Val,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  StmtListInner *_r_f2 = (StmtListInner *)(_r);
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Stmt->desugarDecr();
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Stmt->StatementType == DECR) {
      int _f0_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f0->Stmt)->Id)
                             ->VarId;
      delete _r_f0->Stmt;
      _r_f0->Stmt = new AssignStmt();
      class AssignStmt *const _f0_Assignment =
          static_cast<class AssignStmt *>(_r_f0->Stmt);
      _f0_Assignment->StatementType = ASSIGNMENT;
      _f0_Assignment->NodeType = STMT;
      _f0_Assignment->AssignedExpr = new BinaryExpr();
      class BinaryExpr *const _f0_BinExp =
          static_cast<class BinaryExpr *>(_f0_Assignment->AssignedExpr);
      _f0_BinExp->ExpressionType = BINARY;
      _f0_BinExp->NodeType = EXPR;
      _f0_BinExp->Operator = SUBTRACT;
      _f0_BinExp->LHS = new VarRefExpr();
      _f0_BinExp->LHS->NodeType = EXPR;
      _f0_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f0_BinExp->LHS)->VarId = _f0_Variable;
      _f0_BinExp->RHS = new ConstantExpr();
      _f0_BinExp->RHS->NodeType = EXPR;
      _f0_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f0_BinExp->RHS)->Value = 1;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->Stmt->desugarInc();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Stmt->StatementType == INC) {
      int _f1_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f1->Stmt)->Id)
                             ->VarId;
      delete _r_f1->Stmt;
      _r_f1->Stmt = new AssignStmt();
      class AssignStmt *const _f1_Assignment =
          static_cast<class AssignStmt *>(_r_f1->Stmt);
      _f1_Assignment->StatementType = ASSIGNMENT;
      _f1_Assignment->NodeType = STMT;
      _f1_Assignment->AssignedExpr = new BinaryExpr();
      _f1_Assignment->Id = new VarRefExpr();
      _f1_Assignment->Id->NodeType = EXPR;
      _f1_Assignment->Id->ExpressionType = VARREF;
      _f1_Assignment->Id->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_Assignment->Id)->VarId = _f1_Variable;
      class BinaryExpr *const _f1_BinExp =
          static_cast<class BinaryExpr *>(_f1_Assignment->AssignedExpr);
      _f1_BinExp->ExpressionType = BINARY;
      _f1_BinExp->NodeType = EXPR;
      _f1_BinExp->Operator = ADD;
      _f1_BinExp->LHS = new VarRefExpr();
      _f1_BinExp->LHS->NodeType = EXPR;
      _f1_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_BinExp->LHS)->VarId = _f1_Variable;
      _f1_BinExp->RHS = new ConstantExpr();
      _f1_BinExp->RHS->NodeType = EXPR;
      _f1_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f1_BinExp->RHS)->Value = 1;
    }
  }
_label_B3F1_Exit:
  if (truncate_flags & 0b100) {
    if (_f2_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111011;
      goto _label_B3F2_Exit;
    }
  }
_label_B3F2_Exit:
  if ((truncate_flags & 0b100)) /*call*/ {
    _r_f2->Stmt->replaceVarRefWithConst(_f2_VarRefId, _f2_Val);
  }
  if (truncate_flags & 0b100) {
    if (_r_f2->Stmt->StatementType == IF ||
        (_r_f2->Stmt->StatementType == ASSIGNMENT &&
         static_cast<class VarRefExpr *>(
             static_cast<class AssignStmt *>(_r_f2->Stmt)->Id)
                 ->VarId == _f2_VarRefId)) {
      truncate_flags &= 0b11111111011;
      goto _label_B4F2_Exit;
    }
  }
_label_B4F2_Exit:
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->Next->__virtualStub20(_f2_VarRefId, _f2_Val, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F23F24(StmtListInner *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  int _f0_VarRefId;
  int _f0_Value;
  if (truncate_flags & 0b1) {
    _f0_VarRefId = 0 - 1;
    _f0_VarRefId = 0 - 1;
    if (_r_f0->Stmt->StatementType == ASSIGNMENT) {
      if (static_cast<class AssignStmt *>(_r_f0->Stmt)
              ->AssignedExpr->ExpressionType == CONSTANT) {
        _f0_VarRefId = static_cast<class VarRefExpr *>(
                           static_cast<class AssignStmt *>(_r_f0->Stmt)->Id)
                           ->VarId;
        _f0_Value =
            static_cast<class ConstantExpr *>(
                static_cast<class AssignStmt *>(_r_f0->Stmt)->AssignedExpr)
                ->Value;
      }
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f1->Stmt->__virtualStub5(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Next->__virtualStub8(_f0_VarRefId, _f0_Value, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    ;
  }
_label_B3F0_Exit:
  return;
};
void _fuse__F39F40F36(StmtListEnd *_r, int _f2_VarRefId, int _f2_Val,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f2 = (StmtListEnd *)(_r);
  if (truncate_flags & 0b100) {
    if (_f2_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111011;
      goto _label_B1F2_Exit;
    }
  }
_label_B1F2_Exit:
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->Stmt->__virtualStub21(_f2_VarRefId, _f2_Val, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F33F23(StmtListInner *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Stmt->__virtualStub9(_f0_VarRefId, _f0_Val, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Stmt->StatementType == IF ||
        (_r_f0->Stmt->StatementType == ASSIGNMENT &&
         static_cast<class VarRefExpr *>(
             static_cast<class AssignStmt *>(_r_f0->Stmt)->Id)
                 ->VarId == _f0_VarRefId)) {
      truncate_flags &= 0b11111111110;
      goto _label_B2F0_Exit;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Next->replaceVarRefWithConst(_f0_VarRefId, _f0_Val);
  }
  int _f1_VarRefId;
  int _f1_Value;
  if (truncate_flags & 0b10) {
    _f1_VarRefId = 0 - 1;
    _f1_VarRefId = 0 - 1;
    if (_r_f1->Stmt->StatementType == ASSIGNMENT) {
      if (static_cast<class AssignStmt *>(_r_f1->Stmt)
              ->AssignedExpr->ExpressionType == CONSTANT) {
        _f1_VarRefId = static_cast<class VarRefExpr *>(
                           static_cast<class AssignStmt *>(_r_f1->Stmt)->Id)
                           ->VarId;
        _f1_Value =
            static_cast<class ConstantExpr *>(
                static_cast<class AssignStmt *>(_r_f1->Stmt)->AssignedExpr)
                ->Value;
      }
    }
  }
_label_B3F1_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    _r_f1->Next->__virtualStub11(_f1_VarRefId, _f1_Value,
                                 AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    ;
  }
_label_B4F1_Exit:
  return;
};
void _fuse__F8F26F10(AssignStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  AssignStmt *_r_f1 = (AssignStmt *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->AssignedExpr->foldConstants();
  }
  class BinaryExpr *_f1_AssignedExpr_;
  int _f1_NewValue;
  if (truncate_flags & 0b10) {
    if (_r_f1->AssignedExpr->ExpressionType != BINARY) {
      truncate_flags &= 0b11111111101;
      goto _label_B2F1_Exit;
    }
    _f1_AssignedExpr_ = static_cast<class BinaryExpr *>(_r_f1->AssignedExpr);
    if (_f1_AssignedExpr_->LHS->ExpressionType != CONSTANT ||
        _f1_AssignedExpr_->RHS->ExpressionType != CONSTANT) {
      truncate_flags &= 0b11111111101;
      goto _label_B2F1_Exit;
    }
    if (_f1_AssignedExpr_->Operator == ADD) {
      _f1_NewValue =
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->LHS)->Value +
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->RHS)->Value;
    }
    if (_f1_AssignedExpr_->Operator == SUBTRACT) {
      _f1_NewValue =
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->LHS)->Value -
          static_cast<class ConstantExpr *>(_f1_AssignedExpr_->RHS)->Value;
    }
    delete _f1_AssignedExpr_->LHS;
    delete _f1_AssignedExpr_->RHS;
    delete _r_f1->AssignedExpr;
    _r_f1->AssignedExpr = new ConstantExpr();
    static_cast<class ConstantExpr *>(_r_f1->AssignedExpr)->Value =
        _f1_NewValue;
    _r_f1->AssignedExpr->NodeType = ASTNodeType::EXPR;
    _r_f1->AssignedExpr->ExpressionType = ASTExprType::CONSTANT;
  }
_label_B2F1_Exit:
  return;
};
void _fuse__F36F30(StmtListEnd *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Stmt->__virtualStub12(_f0_VarRefId, _f0_Val, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F6F7F8F9F10(ASTNode *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  ASTNode *_r_f3 = (ASTNode *)(_r);
  ASTNode *_r_f4 = (ASTNode *)(_r);
  return;
};
void _fuse__F30F31(StmtListEnd *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Stmt->__virtualStub6(AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F1F2F3F4F5(Program *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Program *_r_f0 = (Program *)(_r);
  Program *_r_f1 = (Program *)(_r);
  Program *_r_f2 = (Program *)(_r);
  Program *_r_f3 = (Program *)(_r);
  Program *_r_f4 = (Program *)(_r);
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
    _r_f0->Functions->__virtualStub0(AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F33F23F24(StmtListInner *_r, int _f0_VarRefId, int _f0_Val,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  StmtListInner *_r_f2 = (StmtListInner *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Stmt->__virtualStub9(_f0_VarRefId, _f0_Val, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Stmt->StatementType == IF ||
        (_r_f0->Stmt->StatementType == ASSIGNMENT &&
         static_cast<class VarRefExpr *>(
             static_cast<class AssignStmt *>(_r_f0->Stmt)->Id)
                 ->VarId == _f0_VarRefId)) {
      truncate_flags &= 0b11111111110;
      goto _label_B2F0_Exit;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Next->replaceVarRefWithConst(_f0_VarRefId, _f0_Val);
  }
  int _f1_VarRefId;
  int _f1_Value;
  if (truncate_flags & 0b10) {
    _f1_VarRefId = 0 - 1;
    _f1_VarRefId = 0 - 1;
    if (_r_f1->Stmt->StatementType == ASSIGNMENT) {
      if (static_cast<class AssignStmt *>(_r_f1->Stmt)
              ->AssignedExpr->ExpressionType == CONSTANT) {
        _f1_VarRefId = static_cast<class VarRefExpr *>(
                           static_cast<class AssignStmt *>(_r_f1->Stmt)->Id)
                           ->VarId;
        _f1_Value =
            static_cast<class ConstantExpr *>(
                static_cast<class AssignStmt *>(_r_f1->Stmt)->AssignedExpr)
                ->Value;
      }
    }
  }
_label_B3F1_Exit:
  if ((truncate_flags & 0b100)) /*call*/ {
    _r_f2->Stmt->foldConstants();
  }
  if ((truncate_flags & 0b110)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    _r_f1->Next->__virtualStub8(_f1_VarRefId, _f1_Value, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    ;
  }
_label_B5F1_Exit:
  return;
};
void _fuse__F44F45F46F47F48(FunctionListEnd *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  FunctionListEnd *_r_f0 = (FunctionListEnd *)(_r);
  FunctionListEnd *_r_f1 = (FunctionListEnd *)(_r);
  FunctionListEnd *_r_f2 = (FunctionListEnd *)(_r);
  FunctionListEnd *_r_f3 = (FunctionListEnd *)(_r);
  FunctionListEnd *_r_f4 = (FunctionListEnd *)(_r);
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
    _r_f0->Content->__virtualStub32(AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F21F22F23F24(StmtListInner *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  StmtListInner *_r_f2 = (StmtListInner *)(_r);
  StmtListInner *_r_f3 = (StmtListInner *)(_r);
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Stmt->desugarDecr();
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Stmt->StatementType == DECR) {
      int _f0_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f0->Stmt)->Id)
                             ->VarId;
      delete _r_f0->Stmt;
      _r_f0->Stmt = new AssignStmt();
      class AssignStmt *const _f0_Assignment =
          static_cast<class AssignStmt *>(_r_f0->Stmt);
      _f0_Assignment->StatementType = ASSIGNMENT;
      _f0_Assignment->NodeType = STMT;
      _f0_Assignment->AssignedExpr = new BinaryExpr();
      class BinaryExpr *const _f0_BinExp =
          static_cast<class BinaryExpr *>(_f0_Assignment->AssignedExpr);
      _f0_BinExp->ExpressionType = BINARY;
      _f0_BinExp->NodeType = EXPR;
      _f0_BinExp->Operator = SUBTRACT;
      _f0_BinExp->LHS = new VarRefExpr();
      _f0_BinExp->LHS->NodeType = EXPR;
      _f0_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f0_BinExp->LHS)->VarId = _f0_Variable;
      _f0_BinExp->RHS = new ConstantExpr();
      _f0_BinExp->RHS->NodeType = EXPR;
      _f0_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f0_BinExp->RHS)->Value = 1;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->Stmt->desugarInc();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Stmt->StatementType == INC) {
      int _f1_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f1->Stmt)->Id)
                             ->VarId;
      delete _r_f1->Stmt;
      _r_f1->Stmt = new AssignStmt();
      class AssignStmt *const _f1_Assignment =
          static_cast<class AssignStmt *>(_r_f1->Stmt);
      _f1_Assignment->StatementType = ASSIGNMENT;
      _f1_Assignment->NodeType = STMT;
      _f1_Assignment->AssignedExpr = new BinaryExpr();
      _f1_Assignment->Id = new VarRefExpr();
      _f1_Assignment->Id->NodeType = EXPR;
      _f1_Assignment->Id->ExpressionType = VARREF;
      _f1_Assignment->Id->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_Assignment->Id)->VarId = _f1_Variable;
      class BinaryExpr *const _f1_BinExp =
          static_cast<class BinaryExpr *>(_f1_Assignment->AssignedExpr);
      _f1_BinExp->ExpressionType = BINARY;
      _f1_BinExp->NodeType = EXPR;
      _f1_BinExp->Operator = ADD;
      _f1_BinExp->LHS = new VarRefExpr();
      _f1_BinExp->LHS->NodeType = EXPR;
      _f1_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_BinExp->LHS)->VarId = _f1_Variable;
      _f1_BinExp->RHS = new ConstantExpr();
      _f1_BinExp->RHS->NodeType = EXPR;
      _f1_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f1_BinExp->RHS)->Value = 1;
    }
  }
_label_B3F1_Exit:
  int _f2_VarRefId;
  int _f2_Value;
  if (truncate_flags & 0b100) {
    _f2_VarRefId = 0 - 1;
    _f2_VarRefId = 0 - 1;
    if (_r_f2->Stmt->StatementType == ASSIGNMENT) {
      if (static_cast<class AssignStmt *>(_r_f2->Stmt)
              ->AssignedExpr->ExpressionType == CONSTANT) {
        _f2_VarRefId = static_cast<class VarRefExpr *>(
                           static_cast<class AssignStmt *>(_r_f2->Stmt)->Id)
                           ->VarId;
        _f2_Value =
            static_cast<class ConstantExpr *>(
                static_cast<class AssignStmt *>(_r_f2->Stmt)->AssignedExpr)
                ->Value;
      }
    }
  }
_label_B3F2_Exit:
  if ((truncate_flags & 0b1100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f3->Stmt->__virtualStub5(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->Next->__virtualStub19(_f2_VarRefId, _f2_Value,
                                 AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100) {
    ;
  }
_label_B5F2_Exit:
  return;
};
void _fuse__F11F12F13F14F15(FunctionListInner *_r,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  FunctionListInner *_r_f0 = (FunctionListInner *)(_r);
  FunctionListInner *_r_f1 = (FunctionListInner *)(_r);
  FunctionListInner *_r_f2 = (FunctionListInner *)(_r);
  FunctionListInner *_r_f3 = (FunctionListInner *)(_r);
  FunctionListInner *_r_f4 = (FunctionListInner *)(_r);
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
    _r_f0->Content->__virtualStub1(AdjustedTruncateFlags);
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
    _r_f0->Next->__virtualStub31(AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F36F30F31(StmtListEnd *_r, int _f0_VarRefId, int _f0_Val,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f2 = (StmtListEnd *)(_r);
  if (truncate_flags & 0b1) {
    if (_f0_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111110;
      goto _label_B1F0_Exit;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Stmt->__virtualStub14(_f0_VarRefId, _f0_Val, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F8F9F10(ASTNode *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  return;
};
void _fuse__F6F7F34F8F26(AssignStmt *_r, int _f2_VarRefId, int _f2_Val,
                         unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  AssignStmt *_r_f2 = (AssignStmt *)(_r);
  ASTNode *_r_f3 = (ASTNode *)(_r);
  AssignStmt *_r_f4 = (AssignStmt *)(_r);
  if (truncate_flags & 0b100) {
    if (_r_f2->AssignedExpr->ExpressionType == VARREF &&
        static_cast<class VarRefExpr *>(_r_f2->AssignedExpr)->VarId ==
            _f2_VarRefId) {
      delete _r_f2->AssignedExpr;
      _r_f2->AssignedExpr = new ConstantExpr();
      static_cast<class ConstantExpr *>(_r_f2->AssignedExpr)->ExpressionType =
          CONSTANT;
      static_cast<class ConstantExpr *>(_r_f2->AssignedExpr)->Value = _f2_Val;
    }
  }
_label_B1F2_Exit:
  if ((truncate_flags & 0b10100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f4->AssignedExpr->__virtualStub15(_f2_VarRefId, _f2_Val,
                                         AdjustedTruncateFlags);
  }
  class BinaryExpr *_f4_AssignedExpr_;
  int _f4_NewValue;
  if (truncate_flags & 0b10000) {
    if (_r_f4->AssignedExpr->ExpressionType != BINARY) {
      truncate_flags &= 0b11111101111;
      goto _label_B2F4_Exit;
    }
    _f4_AssignedExpr_ = static_cast<class BinaryExpr *>(_r_f4->AssignedExpr);
    if (_f4_AssignedExpr_->LHS->ExpressionType != CONSTANT ||
        _f4_AssignedExpr_->RHS->ExpressionType != CONSTANT) {
      truncate_flags &= 0b11111101111;
      goto _label_B2F4_Exit;
    }
    if (_f4_AssignedExpr_->Operator == ADD) {
      _f4_NewValue =
          static_cast<class ConstantExpr *>(_f4_AssignedExpr_->LHS)->Value +
          static_cast<class ConstantExpr *>(_f4_AssignedExpr_->RHS)->Value;
    }
    if (_f4_AssignedExpr_->Operator == SUBTRACT) {
      _f4_NewValue =
          static_cast<class ConstantExpr *>(_f4_AssignedExpr_->LHS)->Value -
          static_cast<class ConstantExpr *>(_f4_AssignedExpr_->RHS)->Value;
    }
    delete _f4_AssignedExpr_->LHS;
    delete _f4_AssignedExpr_->RHS;
    delete _r_f4->AssignedExpr;
    _r_f4->AssignedExpr = new ConstantExpr();
    static_cast<class ConstantExpr *>(_r_f4->AssignedExpr)->Value =
        _f4_NewValue;
    _r_f4->AssignedExpr->NodeType = ASTNodeType::EXPR;
    _r_f4->AssignedExpr->ExpressionType = ASTExprType::CONSTANT;
  }
_label_B2F4_Exit:
  return;
};
void _fuse__F32F8(ASTNode *_r, int _f0_VarRefId, int _f0_Val,
                  unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  return;
};
void _fuse__F16F17F18F19F20(Function *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Function *_r_f0 = (Function *)(_r);
  Function *_r_f1 = (Function *)(_r);
  Function *_r_f2 = (Function *)(_r);
  Function *_r_f3 = (Function *)(_r);
  Function *_r_f4 = (Function *)(_r);
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
    _r_f0->StmtList->__virtualStub2(AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F27F28F29(IfStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  IfStmt *_r_f2 = (IfStmt *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub4(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub7(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->Condition->foldConstants();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Condition->ExpressionType == BINARY) {
      class BinaryExpr *const _f1_Condition_ =
          static_cast<class BinaryExpr *>(_r_f1->Condition);
      if (_f1_Condition_->LHS->ExpressionType == CONSTANT &&
          _f1_Condition_->RHS->ExpressionType == CONSTANT) {
        int _f1_NewValue;
        if (_f1_Condition_->Operator == ADD) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_Condition_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f1_Condition_->RHS)->Value;
        }
        if (_f1_Condition_->Operator == SUBTRACT) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_Condition_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f1_Condition_->RHS)->Value;
        }
        delete _f1_Condition_->LHS;
        delete _f1_Condition_->RHS;
        delete _f1_Condition_;
        _r_f1->Condition = new ConstantExpr();
        _r_f1->Condition->NodeType = ASTNodeType::EXPR;
        _r_f1->Condition->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f1->Condition)->Value =
            _f1_NewValue;
      }
    }
  }
_label_B4F1_Exit:
  if (truncate_flags & 0b100) {
    if (_r_f2->Condition->ExpressionType == CONSTANT) {
      class ConstantExpr *const _f2_ConstantCond =
          static_cast<class ConstantExpr *>(_r_f2->Condition);
      if (_f2_ConstantCond->Value == 0) {
        delete _r_f2->ThenPart;
        _r_f2->ThenPart = new StmtListEnd();
        _r_f2->ThenPart->NodeType = SEQ;
        _r_f2->ThenPart->Stmt = new NullStmt();
        _r_f2->ThenPart->Stmt->NodeType = STMT;
        _r_f2->ThenPart->Stmt->StatementType = NOP;
      }
      if (_f2_ConstantCond->Value != 0) {
        delete _r_f2->ElsePart;
        _r_f2->ElsePart = new StmtListEnd();
        _r_f2->ElsePart->NodeType = SEQ;
        _r_f2->ElsePart->Stmt = new NullStmt();
        _r_f2->ElsePart->Stmt->NodeType = STMT;
        _r_f2->ElsePart->Stmt->StatementType = NOP;
      }
    }
  }
_label_B4F2_Exit:
  if ((truncate_flags & 0b100)) /*call*/ {
    _r_f2->ThenPart->removeUnreachableBranches();
  }
  if ((truncate_flags & 0b100)) /*call*/ {
    _r_f2->ElsePart->removeUnreachableBranches();
  }
  return;
};
void _fuse__F21F22F23F24F25(StmtListInner *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  StmtListInner *_r_f2 = (StmtListInner *)(_r);
  StmtListInner *_r_f3 = (StmtListInner *)(_r);
  StmtListInner *_r_f4 = (StmtListInner *)(_r);
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Stmt->desugarDecr();
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Stmt->StatementType == DECR) {
      int _f0_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f0->Stmt)->Id)
                             ->VarId;
      delete _r_f0->Stmt;
      _r_f0->Stmt = new AssignStmt();
      class AssignStmt *const _f0_Assignment =
          static_cast<class AssignStmt *>(_r_f0->Stmt);
      _f0_Assignment->StatementType = ASSIGNMENT;
      _f0_Assignment->NodeType = STMT;
      _f0_Assignment->AssignedExpr = new BinaryExpr();
      class BinaryExpr *const _f0_BinExp =
          static_cast<class BinaryExpr *>(_f0_Assignment->AssignedExpr);
      _f0_BinExp->ExpressionType = BINARY;
      _f0_BinExp->NodeType = EXPR;
      _f0_BinExp->Operator = SUBTRACT;
      _f0_BinExp->LHS = new VarRefExpr();
      _f0_BinExp->LHS->NodeType = EXPR;
      _f0_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f0_BinExp->LHS)->VarId = _f0_Variable;
      _f0_BinExp->RHS = new ConstantExpr();
      _f0_BinExp->RHS->NodeType = EXPR;
      _f0_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f0_BinExp->RHS)->Value = 1;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->Stmt->desugarInc();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Stmt->StatementType == INC) {
      int _f1_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f1->Stmt)->Id)
                             ->VarId;
      delete _r_f1->Stmt;
      _r_f1->Stmt = new AssignStmt();
      class AssignStmt *const _f1_Assignment =
          static_cast<class AssignStmt *>(_r_f1->Stmt);
      _f1_Assignment->StatementType = ASSIGNMENT;
      _f1_Assignment->NodeType = STMT;
      _f1_Assignment->AssignedExpr = new BinaryExpr();
      _f1_Assignment->Id = new VarRefExpr();
      _f1_Assignment->Id->NodeType = EXPR;
      _f1_Assignment->Id->ExpressionType = VARREF;
      _f1_Assignment->Id->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_Assignment->Id)->VarId = _f1_Variable;
      class BinaryExpr *const _f1_BinExp =
          static_cast<class BinaryExpr *>(_f1_Assignment->AssignedExpr);
      _f1_BinExp->ExpressionType = BINARY;
      _f1_BinExp->NodeType = EXPR;
      _f1_BinExp->Operator = ADD;
      _f1_BinExp->LHS = new VarRefExpr();
      _f1_BinExp->LHS->NodeType = EXPR;
      _f1_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_BinExp->LHS)->VarId = _f1_Variable;
      _f1_BinExp->RHS = new ConstantExpr();
      _f1_BinExp->RHS->NodeType = EXPR;
      _f1_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f1_BinExp->RHS)->Value = 1;
    }
  }
_label_B3F1_Exit:
  int _f2_VarRefId;
  int _f2_Value;
  if (truncate_flags & 0b100) {
    _f2_VarRefId = 0 - 1;
    _f2_VarRefId = 0 - 1;
    if (_r_f2->Stmt->StatementType == ASSIGNMENT) {
      if (static_cast<class AssignStmt *>(_r_f2->Stmt)
              ->AssignedExpr->ExpressionType == CONSTANT) {
        _f2_VarRefId = static_cast<class VarRefExpr *>(
                           static_cast<class AssignStmt *>(_r_f2->Stmt)->Id)
                           ->VarId;
        _f2_Value =
            static_cast<class ConstantExpr *>(
                static_cast<class AssignStmt *>(_r_f2->Stmt)->AssignedExpr)
                ->Value;
      }
    }
  }
_label_B3F2_Exit:
  if ((truncate_flags & 0b11100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f3->Stmt->__virtualStub3(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b1111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->Next->__virtualStub19(_f2_VarRefId, _f2_Value,
                                 AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b10000)) /*call*/ {
    _r_f4->Next->removeUnreachableBranches();
  }
  if (truncate_flags & 0b100) {
    ;
  }
_label_B6F2_Exit:
  return;
};
void _fuse__F6F7F32F8F9(ASTNode *_r, int _f2_VarRefId, int _f2_Val,
                        unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  ASTNode *_r_f3 = (ASTNode *)(_r);
  ASTNode *_r_f4 = (ASTNode *)(_r);
  return;
};
void _fuse__F34F8(AssignStmt *_r, int _f0_VarRefId, int _f0_Val,
                  unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  AssignStmt *_r_f0 = (AssignStmt *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->AssignedExpr->ExpressionType == VARREF &&
        static_cast<class VarRefExpr *>(_r_f0->AssignedExpr)->VarId ==
            _f0_VarRefId) {
      delete _r_f0->AssignedExpr;
      _r_f0->AssignedExpr = new ConstantExpr();
      static_cast<class ConstantExpr *>(_r_f0->AssignedExpr)->ExpressionType =
          CONSTANT;
      static_cast<class ConstantExpr *>(_r_f0->AssignedExpr)->Value = _f0_Val;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->AssignedExpr->replaceVarRefWithConst(_f0_VarRefId, _f0_Val);
  }
  return;
};
void _fuse__F35F27(IfStmt *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Condition->replaceVarRefWithConst(_f0_VarRefId, _f0_Val);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub10(_f0_VarRefId, _f0_Val,
                                     AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub13(_f0_VarRefId, _f0_Val,
                                     AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F34F8F26(AssignStmt *_r, int _f0_VarRefId, int _f0_Val,
                     unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  AssignStmt *_r_f0 = (AssignStmt *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  AssignStmt *_r_f2 = (AssignStmt *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->AssignedExpr->ExpressionType == VARREF &&
        static_cast<class VarRefExpr *>(_r_f0->AssignedExpr)->VarId ==
            _f0_VarRefId) {
      delete _r_f0->AssignedExpr;
      _r_f0->AssignedExpr = new ConstantExpr();
      static_cast<class ConstantExpr *>(_r_f0->AssignedExpr)->ExpressionType =
          CONSTANT;
      static_cast<class ConstantExpr *>(_r_f0->AssignedExpr)->Value = _f0_Val;
    }
  }
_label_B1F0_Exit:
  if ((truncate_flags & 0b101)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->AssignedExpr->__virtualStub15(_f0_VarRefId, _f0_Val,
                                         AdjustedTruncateFlags);
  }
  class BinaryExpr *_f2_AssignedExpr_;
  int _f2_NewValue;
  if (truncate_flags & 0b100) {
    if (_r_f2->AssignedExpr->ExpressionType != BINARY) {
      truncate_flags &= 0b11111111011;
      goto _label_B2F2_Exit;
    }
    _f2_AssignedExpr_ = static_cast<class BinaryExpr *>(_r_f2->AssignedExpr);
    if (_f2_AssignedExpr_->LHS->ExpressionType != CONSTANT ||
        _f2_AssignedExpr_->RHS->ExpressionType != CONSTANT) {
      truncate_flags &= 0b11111111011;
      goto _label_B2F2_Exit;
    }
    if (_f2_AssignedExpr_->Operator == ADD) {
      _f2_NewValue =
          static_cast<class ConstantExpr *>(_f2_AssignedExpr_->LHS)->Value +
          static_cast<class ConstantExpr *>(_f2_AssignedExpr_->RHS)->Value;
    }
    if (_f2_AssignedExpr_->Operator == SUBTRACT) {
      _f2_NewValue =
          static_cast<class ConstantExpr *>(_f2_AssignedExpr_->LHS)->Value -
          static_cast<class ConstantExpr *>(_f2_AssignedExpr_->RHS)->Value;
    }
    delete _f2_AssignedExpr_->LHS;
    delete _f2_AssignedExpr_->RHS;
    delete _r_f2->AssignedExpr;
    _r_f2->AssignedExpr = new ConstantExpr();
    static_cast<class ConstantExpr *>(_r_f2->AssignedExpr)->Value =
        _f2_NewValue;
    _r_f2->AssignedExpr->NodeType = ASTNodeType::EXPR;
    _r_f2->AssignedExpr->ExpressionType = ASTExprType::CONSTANT;
  }
_label_B2F2_Exit:
  return;
};
void _fuse__F32F9(ASTNode *_r, int _f0_VarRefId, int _f0_Val,
                  unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  return;
};
void _fuse__F37F38(BinaryExpr *_r, int _f0_VarRefId, int _f0_Val,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  BinaryExpr *_r_f0 = (BinaryExpr *)(_r);
  BinaryExpr *_r_f1 = (BinaryExpr *)(_r);
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->LHS->replaceVarRefWithConst(_f0_VarRefId, _f0_Val);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->LHS->ExpressionType == VARREF &&
        static_cast<class VarRefExpr *>(_r_f0->LHS)->VarId == _f0_VarRefId) {
      delete _r_f0->LHS;
      _r_f0->LHS = new ConstantExpr();
      static_cast<class ConstantExpr *>(_r_f0->LHS)->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_r_f0->LHS)->Value = _f0_Val;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->LHS->foldConstants();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->LHS->ExpressionType == BINARY) {
      class BinaryExpr *const _f1_LHS_ =
          static_cast<class BinaryExpr *>(_r_f1->LHS);
      if (_f1_LHS_->LHS->ExpressionType == CONSTANT &&
          _f1_LHS_->RHS->ExpressionType == CONSTANT) {
        int _f1_NewValue;
        if (_f1_LHS_->Operator == ADD) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_LHS_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f1_LHS_->RHS)->Value;
        }
        if (_f1_LHS_->Operator == SUBTRACT) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_LHS_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f1_LHS_->RHS)->Value;
        }
        delete _f1_LHS_->LHS;
        delete _f1_LHS_->RHS;
        delete _r_f1->LHS;
        _r_f1->LHS = new ConstantExpr();
        _r_f1->LHS->NodeType = ASTNodeType::EXPR;
        _r_f1->LHS->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f1->LHS)->Value = _f1_NewValue;
      }
    }
  }
_label_B3F1_Exit:
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->RHS->replaceVarRefWithConst(_f0_VarRefId, _f0_Val);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->RHS->ExpressionType == VARREF &&
        static_cast<class VarRefExpr *>(_r_f0->RHS)->VarId == _f0_VarRefId) {
      delete _r_f0->RHS;
      _r_f0->RHS = new ConstantExpr();
      static_cast<class ConstantExpr *>(_r_f0->RHS)->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_r_f0->RHS)->Value = _f0_Val;
    }
  }
_label_B4F0_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->RHS->foldConstants();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->RHS->ExpressionType == BINARY) {
      class BinaryExpr *const _f1_RHS_ =
          static_cast<class BinaryExpr *>(_r_f1->RHS);
      if (_f1_RHS_->LHS->ExpressionType == CONSTANT &&
          _f1_RHS_->RHS->ExpressionType == CONSTANT) {
        int _f1_NewValue;
        if (_f1_RHS_->Operator == ADD) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_RHS_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f1_RHS_->RHS)->Value;
        }
        if (_f1_RHS_->Operator == SUBTRACT) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_RHS_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f1_RHS_->RHS)->Value;
        }
        delete _f1_RHS_->LHS;
        delete _f1_RHS_->RHS;
        delete _r_f1->RHS;
        _r_f1->RHS = new ConstantExpr();
        _r_f1->RHS->NodeType = ASTNodeType::EXPR;
        _r_f1->RHS->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f1->RHS)->Value = _f1_NewValue;
      }
    }
  }
_label_B5F1_Exit:
  return;
};
void _fuse__F39F40F36F30F31(StmtListEnd *_r, int _f2_VarRefId, int _f2_Val,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f2 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f3 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f4 = (StmtListEnd *)(_r);
  if (truncate_flags & 0b100) {
    if (_f2_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111011;
      goto _label_B1F2_Exit;
    }
  }
_label_B1F2_Exit:
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
    _r_f2->Stmt->__virtualStub24(_f2_VarRefId, _f2_Val, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F27F28(IfStmt *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub4(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub7(AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->Condition->foldConstants();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Condition->ExpressionType == BINARY) {
      class BinaryExpr *const _f1_Condition_ =
          static_cast<class BinaryExpr *>(_r_f1->Condition);
      if (_f1_Condition_->LHS->ExpressionType == CONSTANT &&
          _f1_Condition_->RHS->ExpressionType == CONSTANT) {
        int _f1_NewValue;
        if (_f1_Condition_->Operator == ADD) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_Condition_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f1_Condition_->RHS)->Value;
        }
        if (_f1_Condition_->Operator == SUBTRACT) {
          _f1_NewValue =
              static_cast<class ConstantExpr *>(_f1_Condition_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f1_Condition_->RHS)->Value;
        }
        delete _f1_Condition_->LHS;
        delete _f1_Condition_->RHS;
        delete _f1_Condition_;
        _r_f1->Condition = new ConstantExpr();
        _r_f1->Condition->NodeType = ASTNodeType::EXPR;
        _r_f1->Condition->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f1->Condition)->Value =
            _f1_NewValue;
      }
    }
  }
_label_B4F1_Exit:
  return;
};
void _fuse__F21F22F33F23F24(StmtListInner *_r, int _f2_VarRefId, int _f2_Val,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListInner *_r_f0 = (StmtListInner *)(_r);
  StmtListInner *_r_f1 = (StmtListInner *)(_r);
  StmtListInner *_r_f2 = (StmtListInner *)(_r);
  StmtListInner *_r_f3 = (StmtListInner *)(_r);
  StmtListInner *_r_f4 = (StmtListInner *)(_r);
  if ((truncate_flags & 0b1)) /*call*/ {
    _r_f0->Stmt->desugarDecr();
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Stmt->StatementType == DECR) {
      int _f0_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f0->Stmt)->Id)
                             ->VarId;
      delete _r_f0->Stmt;
      _r_f0->Stmt = new AssignStmt();
      class AssignStmt *const _f0_Assignment =
          static_cast<class AssignStmt *>(_r_f0->Stmt);
      _f0_Assignment->StatementType = ASSIGNMENT;
      _f0_Assignment->NodeType = STMT;
      _f0_Assignment->AssignedExpr = new BinaryExpr();
      class BinaryExpr *const _f0_BinExp =
          static_cast<class BinaryExpr *>(_f0_Assignment->AssignedExpr);
      _f0_BinExp->ExpressionType = BINARY;
      _f0_BinExp->NodeType = EXPR;
      _f0_BinExp->Operator = SUBTRACT;
      _f0_BinExp->LHS = new VarRefExpr();
      _f0_BinExp->LHS->NodeType = EXPR;
      _f0_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f0_BinExp->LHS)->VarId = _f0_Variable;
      _f0_BinExp->RHS = new ConstantExpr();
      _f0_BinExp->RHS->NodeType = EXPR;
      _f0_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f0_BinExp->RHS)->Value = 1;
    }
  }
_label_B2F0_Exit:
  if ((truncate_flags & 0b10)) /*call*/ {
    _r_f1->Stmt->desugarInc();
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Stmt->StatementType == INC) {
      int _f1_Variable = static_cast<class VarRefExpr *>(
                             static_cast<class IncrStmt *>(_r_f1->Stmt)->Id)
                             ->VarId;
      delete _r_f1->Stmt;
      _r_f1->Stmt = new AssignStmt();
      class AssignStmt *const _f1_Assignment =
          static_cast<class AssignStmt *>(_r_f1->Stmt);
      _f1_Assignment->StatementType = ASSIGNMENT;
      _f1_Assignment->NodeType = STMT;
      _f1_Assignment->AssignedExpr = new BinaryExpr();
      _f1_Assignment->Id = new VarRefExpr();
      _f1_Assignment->Id->NodeType = EXPR;
      _f1_Assignment->Id->ExpressionType = VARREF;
      _f1_Assignment->Id->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_Assignment->Id)->VarId = _f1_Variable;
      class BinaryExpr *const _f1_BinExp =
          static_cast<class BinaryExpr *>(_f1_Assignment->AssignedExpr);
      _f1_BinExp->ExpressionType = BINARY;
      _f1_BinExp->NodeType = EXPR;
      _f1_BinExp->Operator = ADD;
      _f1_BinExp->LHS = new VarRefExpr();
      _f1_BinExp->LHS->NodeType = EXPR;
      _f1_BinExp->LHS->ExpressionType = VARREF;
      static_cast<class VarRefExpr *>(_f1_BinExp->LHS)->VarId = _f1_Variable;
      _f1_BinExp->RHS = new ConstantExpr();
      _f1_BinExp->RHS->NodeType = EXPR;
      _f1_BinExp->RHS->ExpressionType = CONSTANT;
      static_cast<class ConstantExpr *>(_f1_BinExp->RHS)->Value = 1;
    }
  }
_label_B3F1_Exit:
  if (truncate_flags & 0b100) {
    if (_f2_VarRefId == (0 - 1)) {
      truncate_flags &= 0b11111111011;
      goto _label_B3F2_Exit;
    }
  }
_label_B3F2_Exit:
  if ((truncate_flags & 0b1100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f2->Stmt->__virtualStub9(_f2_VarRefId, _f2_Val, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100) {
    if (_r_f2->Stmt->StatementType == IF ||
        (_r_f2->Stmt->StatementType == ASSIGNMENT &&
         static_cast<class VarRefExpr *>(
             static_cast<class AssignStmt *>(_r_f2->Stmt)->Id)
                 ->VarId == _f2_VarRefId)) {
      truncate_flags &= 0b11111111011;
      goto _label_B4F2_Exit;
    }
  }
_label_B4F2_Exit:
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->Next->__virtualStub20(_f2_VarRefId, _f2_Val, AdjustedTruncateFlags);
  }
  int _f3_VarRefId;
  int _f3_Value;
  if (truncate_flags & 0b1000) {
    _f3_VarRefId = 0 - 1;
    _f3_VarRefId = 0 - 1;
    if (_r_f3->Stmt->StatementType == ASSIGNMENT) {
      if (static_cast<class AssignStmt *>(_r_f3->Stmt)
              ->AssignedExpr->ExpressionType == CONSTANT) {
        _f3_VarRefId = static_cast<class VarRefExpr *>(
                           static_cast<class AssignStmt *>(_r_f3->Stmt)->Id)
                           ->VarId;
        _f3_Value =
            static_cast<class ConstantExpr *>(
                static_cast<class AssignStmt *>(_r_f3->Stmt)->AssignedExpr)
                ->Value;
      }
    }
  }
_label_B5F3_Exit:
  if ((truncate_flags & 0b10000)) /*call*/ {
    _r_f4->Stmt->foldConstants();
  }
  if ((truncate_flags & 0b11000)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    _r_f3->Next->__virtualStub8(_f3_VarRefId, _f3_Value, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1000) {
    ;
  }
_label_B7F3_Exit:
  return;
};
void _fuse__F6F7F32(ASTNode *_r, int _f2_VarRefId, int _f2_Val,
                    unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  ASTNode *_r_f2 = (ASTNode *)(_r);
  return;
};
void _fuse__F41F42F35(IfStmt *_r, int _f2_VarRefId, int _f2_Val,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  IfStmt *_r_f2 = (IfStmt *)(_r);
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub22(_f2_VarRefId, _f2_Val,
                                     AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub23(_f2_VarRefId, _f2_Val,
                                     AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b100)) /*call*/ {
    _r_f2->Condition->replaceVarRefWithConst(_f2_VarRefId, _f2_Val);
  }
  return;
};
void _fuse__F35F27F28(IfStmt *_r, int _f0_VarRefId, int _f0_Val,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  IfStmt *_r_f2 = (IfStmt *)(_r);
  if ((truncate_flags & 0b101)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Condition->__virtualStub16(_f0_VarRefId, _f0_Val,
                                      AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b100) {
    if (_r_f2->Condition->ExpressionType == BINARY) {
      class BinaryExpr *const _f2_Condition_ =
          static_cast<class BinaryExpr *>(_r_f2->Condition);
      if (_f2_Condition_->LHS->ExpressionType == CONSTANT &&
          _f2_Condition_->RHS->ExpressionType == CONSTANT) {
        int _f2_NewValue;
        if (_f2_Condition_->Operator == ADD) {
          _f2_NewValue =
              static_cast<class ConstantExpr *>(_f2_Condition_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f2_Condition_->RHS)->Value;
        }
        if (_f2_Condition_->Operator == SUBTRACT) {
          _f2_NewValue =
              static_cast<class ConstantExpr *>(_f2_Condition_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f2_Condition_->RHS)->Value;
        }
        delete _f2_Condition_->LHS;
        delete _f2_Condition_->RHS;
        delete _f2_Condition_;
        _r_f2->Condition = new ConstantExpr();
        _r_f2->Condition->NodeType = ASTNodeType::EXPR;
        _r_f2->Condition->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f2->Condition)->Value =
            _f2_NewValue;
      }
    }
  }
_label_B2F2_Exit:
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ThenPart->__virtualStub17(_f0_VarRefId, _f0_Val,
                                     AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->ElsePart->__virtualStub18(_f0_VarRefId, _f0_Val,
                                     AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F41F42F35F27F28(IfStmt *_r, int _f2_VarRefId, int _f2_Val,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  IfStmt *_r_f0 = (IfStmt *)(_r);
  IfStmt *_r_f1 = (IfStmt *)(_r);
  IfStmt *_r_f2 = (IfStmt *)(_r);
  IfStmt *_r_f3 = (IfStmt *)(_r);
  IfStmt *_r_f4 = (IfStmt *)(_r);
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
    _r_f0->ThenPart->__virtualStub25(_f2_VarRefId, _f2_Val,
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
    _r_f0->ElsePart->__virtualStub26(_f2_VarRefId, _f2_Val,
                                     AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b10100)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    _r_f2->Condition->__virtualStub16(_f2_VarRefId, _f2_Val,
                                      AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10000) {
    if (_r_f4->Condition->ExpressionType == BINARY) {
      class BinaryExpr *const _f4_Condition_ =
          static_cast<class BinaryExpr *>(_r_f4->Condition);
      if (_f4_Condition_->LHS->ExpressionType == CONSTANT &&
          _f4_Condition_->RHS->ExpressionType == CONSTANT) {
        int _f4_NewValue;
        if (_f4_Condition_->Operator == ADD) {
          _f4_NewValue =
              static_cast<class ConstantExpr *>(_f4_Condition_->LHS)->Value +
              static_cast<class ConstantExpr *>(_f4_Condition_->RHS)->Value;
        }
        if (_f4_Condition_->Operator == SUBTRACT) {
          _f4_NewValue =
              static_cast<class ConstantExpr *>(_f4_Condition_->LHS)->Value -
              static_cast<class ConstantExpr *>(_f4_Condition_->RHS)->Value;
        }
        delete _f4_Condition_->LHS;
        delete _f4_Condition_->RHS;
        delete _f4_Condition_;
        _r_f4->Condition = new ConstantExpr();
        _r_f4->Condition->NodeType = ASTNodeType::EXPR;
        _r_f4->Condition->ExpressionType = ASTExprType::CONSTANT;
        static_cast<class ConstantExpr *>(_r_f4->Condition)->Value =
            _f4_NewValue;
      }
    }
  }
_label_B4F4_Exit:
  return;
};
void _fuse__F8F9(ASTNode *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ASTNode *_r_f0 = (ASTNode *)(_r);
  ASTNode *_r_f1 = (ASTNode *)(_r);
  return;
};
void _fuse__F39F40F30F31F43(StmtListEnd *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  StmtListEnd *_r_f0 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f1 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f2 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f3 = (StmtListEnd *)(_r);
  StmtListEnd *_r_f4 = (StmtListEnd *)(_r);
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
    _r_f0->Stmt->__virtualStub27(AdjustedTruncateFlags);
  }
  return;
};
void StatementNode::__virtualStub5(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void AssignStmt::__virtualStub5(unsigned int truncate_flags) {
  _fuse__F8F26(this, truncate_flags);
}
void IncrStmt::__virtualStub5(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void DecrStmt::__virtualStub5(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void IfStmt::__virtualStub5(unsigned int truncate_flags) {
  _fuse__F27F28(this, truncate_flags);
}
void NullStmt::__virtualStub5(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void StatementNode::__virtualStub3(unsigned int truncate_flags) {
  _fuse__F8F9F10(this, truncate_flags);
}
void AssignStmt::__virtualStub3(unsigned int truncate_flags) {
  _fuse__F8F26F10(this, truncate_flags);
}
void IncrStmt::__virtualStub3(unsigned int truncate_flags) {
  _fuse__F8F9F10(this, truncate_flags);
}
void DecrStmt::__virtualStub3(unsigned int truncate_flags) {
  _fuse__F8F9F10(this, truncate_flags);
}
void IfStmt::__virtualStub3(unsigned int truncate_flags) {
  _fuse__F27F28F29(this, truncate_flags);
}
void NullStmt::__virtualStub3(unsigned int truncate_flags) {
  _fuse__F8F9F10(this, truncate_flags);
}
void StmtListNode::__virtualStub11(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListInner::__virtualStub11(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F33F23(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListEnd::__virtualStub11(int _f0_VarRefId, int _f0_Val,
                                  unsigned int truncate_flags) {
  _fuse__F36F30(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListNode::__virtualStub8(int _f0_VarRefId, int _f0_Val,
                                  unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListInner::__virtualStub8(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F33F23F24(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListEnd::__virtualStub8(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F36F30F31(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StatementNode::__virtualStub6(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void AssignStmt::__virtualStub6(unsigned int truncate_flags) {
  _fuse__F8F26(this, truncate_flags);
}
void IncrStmt::__virtualStub6(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void DecrStmt::__virtualStub6(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void IfStmt::__virtualStub6(unsigned int truncate_flags) {
  _fuse__F27F28(this, truncate_flags);
}
void NullStmt::__virtualStub6(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void StmtListNode::__virtualStub4(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void StmtListInner::__virtualStub4(unsigned int truncate_flags) {
  _fuse__F23F24(this, truncate_flags);
}
void StmtListEnd::__virtualStub4(unsigned int truncate_flags) {
  _fuse__F30F31(this, truncate_flags);
}
void StmtListNode::__virtualStub7(unsigned int truncate_flags) {
  _fuse__F8F9(this, truncate_flags);
}
void StmtListInner::__virtualStub7(unsigned int truncate_flags) {
  _fuse__F23F24(this, truncate_flags);
}
void StmtListEnd::__virtualStub7(unsigned int truncate_flags) {
  _fuse__F30F31(this, truncate_flags);
}
void StatementNode::__virtualStub9(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void AssignStmt::__virtualStub9(int _f0_VarRefId, int _f0_Val,
                                unsigned int truncate_flags) {
  _fuse__F34F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void IncrStmt::__virtualStub9(int _f0_VarRefId, int _f0_Val,
                              unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void DecrStmt::__virtualStub9(int _f0_VarRefId, int _f0_Val,
                              unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void IfStmt::__virtualStub9(int _f0_VarRefId, int _f0_Val,
                            unsigned int truncate_flags) {
  _fuse__F35F27(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void NullStmt::__virtualStub9(int _f0_VarRefId, int _f0_Val,
                              unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StatementNode::__virtualStub12(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void AssignStmt::__virtualStub12(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F34F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void IncrStmt::__virtualStub12(int _f0_VarRefId, int _f0_Val,
                               unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void DecrStmt::__virtualStub12(int _f0_VarRefId, int _f0_Val,
                               unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void IfStmt::__virtualStub12(int _f0_VarRefId, int _f0_Val,
                             unsigned int truncate_flags) {
  _fuse__F35F27(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void NullStmt::__virtualStub12(int _f0_VarRefId, int _f0_Val,
                               unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StatementNode::__virtualStub14(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void AssignStmt::__virtualStub14(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F34F8F26(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void IncrStmt::__virtualStub14(int _f0_VarRefId, int _f0_Val,
                               unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void DecrStmt::__virtualStub14(int _f0_VarRefId, int _f0_Val,
                               unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void IfStmt::__virtualStub14(int _f0_VarRefId, int _f0_Val,
                             unsigned int truncate_flags) {
  _fuse__F35F27F28(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void NullStmt::__virtualStub14(int _f0_VarRefId, int _f0_Val,
                               unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void ExpressionNode::__virtualStub15(int _f0_VarRefId, int _f0_Val,
                                     unsigned int truncate_flags) {
  _fuse__F32F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void BinaryExpr::__virtualStub15(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F37F38(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void VarRefExpr::__virtualStub15(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F32F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void ConstantExpr::__virtualStub15(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void ExpressionNode::__virtualStub16(int _f0_VarRefId, int _f0_Val,
                                     unsigned int truncate_flags) {
  _fuse__F32F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void BinaryExpr::__virtualStub16(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F37F38(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void VarRefExpr::__virtualStub16(int _f0_VarRefId, int _f0_Val,
                                 unsigned int truncate_flags) {
  _fuse__F32F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void ConstantExpr::__virtualStub16(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListNode::__virtualStub10(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListInner::__virtualStub10(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F33F23(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListEnd::__virtualStub10(int _f0_VarRefId, int _f0_Val,
                                  unsigned int truncate_flags) {
  _fuse__F36F30(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListNode::__virtualStub17(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListInner::__virtualStub17(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F33F23F24(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListEnd::__virtualStub17(int _f0_VarRefId, int _f0_Val,
                                  unsigned int truncate_flags) {
  _fuse__F36F30F31(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListNode::__virtualStub13(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F8(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListInner::__virtualStub13(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F33F23(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListEnd::__virtualStub13(int _f0_VarRefId, int _f0_Val,
                                  unsigned int truncate_flags) {
  _fuse__F36F30(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListNode::__virtualStub18(int _f0_VarRefId, int _f0_Val,
                                   unsigned int truncate_flags) {
  _fuse__F32F8F9(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListInner::__virtualStub18(int _f0_VarRefId, int _f0_Val,
                                    unsigned int truncate_flags) {
  _fuse__F33F23F24(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void StmtListEnd::__virtualStub18(int _f0_VarRefId, int _f0_Val,
                                  unsigned int truncate_flags) {
  _fuse__F36F30F31(this, _f0_VarRefId, _f0_Val, truncate_flags);
}
void FunctionList::__virtualStub0(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void FunctionListInner::__virtualStub0(unsigned int truncate_flags) {
  _fuse__F11F12F13F14F15(this, truncate_flags);
}
void FunctionListEnd::__virtualStub0(unsigned int truncate_flags) {
  _fuse__F44F45F46F47F48(this, truncate_flags);
}
void Function::__virtualStub1(unsigned int truncate_flags) {
  _fuse__F16F17F18F19F20(this, truncate_flags);
}
void FunctionList::__virtualStub31(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void FunctionListInner::__virtualStub31(unsigned int truncate_flags) {
  _fuse__F11F12F13F14F15(this, truncate_flags);
}
void FunctionListEnd::__virtualStub31(unsigned int truncate_flags) {
  _fuse__F44F45F46F47F48(this, truncate_flags);
}
void Function::__virtualStub32(unsigned int truncate_flags) {
  _fuse__F16F17F18F19F20(this, truncate_flags);
}
void StmtListNode::__virtualStub2(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void StmtListInner::__virtualStub2(unsigned int truncate_flags) {
  _fuse__F21F22F23F24F25(this, truncate_flags);
}
void StmtListEnd::__virtualStub2(unsigned int truncate_flags) {
  _fuse__F39F40F30F31F43(this, truncate_flags);
}
void StmtListNode::__virtualStub19(int _f2_VarRefId, int _f2_Val,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListInner::__virtualStub19(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F21F22F33F23F24(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListEnd::__virtualStub19(int _f2_VarRefId, int _f2_Val,
                                  unsigned int truncate_flags) {
  _fuse__F39F40F36F30F31(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListNode::__virtualStub20(int _f2_VarRefId, int _f2_Val,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListInner::__virtualStub20(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F21F22F33(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListEnd::__virtualStub20(int _f2_VarRefId, int _f2_Val,
                                  unsigned int truncate_flags) {
  _fuse__F39F40F36(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StatementNode::__virtualStub29(unsigned int truncate_flags) {
  _fuse__F6F7F8F9(this, truncate_flags);
}
void AssignStmt::__virtualStub29(unsigned int truncate_flags) {
  _fuse__F6F7F8F26(this, truncate_flags);
}
void IncrStmt::__virtualStub29(unsigned int truncate_flags) {
  _fuse__F6F7F8F9(this, truncate_flags);
}
void DecrStmt::__virtualStub29(unsigned int truncate_flags) {
  _fuse__F6F7F8F9(this, truncate_flags);
}
void IfStmt::__virtualStub29(unsigned int truncate_flags) {
  _fuse__F41F42F27F28(this, truncate_flags);
}
void NullStmt::__virtualStub29(unsigned int truncate_flags) {
  _fuse__F6F7F8F9(this, truncate_flags);
}
void StatementNode::__virtualStub27(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void AssignStmt::__virtualStub27(unsigned int truncate_flags) {
  _fuse__F6F7F8F26F10(this, truncate_flags);
}
void IncrStmt::__virtualStub27(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void DecrStmt::__virtualStub27(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void IfStmt::__virtualStub27(unsigned int truncate_flags) {
  _fuse__F41F42F27F28F29(this, truncate_flags);
}
void NullStmt::__virtualStub27(unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, truncate_flags);
}
void StatementNode::__virtualStub21(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void AssignStmt::__virtualStub21(int _f2_VarRefId, int _f2_Val,
                                 unsigned int truncate_flags) {
  _fuse__F6F7F34(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void IncrStmt::__virtualStub21(int _f2_VarRefId, int _f2_Val,
                               unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void DecrStmt::__virtualStub21(int _f2_VarRefId, int _f2_Val,
                               unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void IfStmt::__virtualStub21(int _f2_VarRefId, int _f2_Val,
                             unsigned int truncate_flags) {
  _fuse__F41F42F35(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void NullStmt::__virtualStub21(int _f2_VarRefId, int _f2_Val,
                               unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StatementNode::__virtualStub24(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void AssignStmt::__virtualStub24(int _f2_VarRefId, int _f2_Val,
                                 unsigned int truncate_flags) {
  _fuse__F6F7F34F8F26(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void IncrStmt::__virtualStub24(int _f2_VarRefId, int _f2_Val,
                               unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void DecrStmt::__virtualStub24(int _f2_VarRefId, int _f2_Val,
                               unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void IfStmt::__virtualStub24(int _f2_VarRefId, int _f2_Val,
                             unsigned int truncate_flags) {
  _fuse__F41F42F35F27F28(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void NullStmt::__virtualStub24(int _f2_VarRefId, int _f2_Val,
                               unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListNode::__virtualStub28(unsigned int truncate_flags) {
  _fuse__F6F7F8F9(this, truncate_flags);
}
void StmtListInner::__virtualStub28(unsigned int truncate_flags) {
  _fuse__F21F22F23F24(this, truncate_flags);
}
void StmtListEnd::__virtualStub28(unsigned int truncate_flags) {
  _fuse__F39F40F30F31(this, truncate_flags);
}
void StmtListNode::__virtualStub22(int _f2_VarRefId, int _f2_Val,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListInner::__virtualStub22(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F21F22F33(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListEnd::__virtualStub22(int _f2_VarRefId, int _f2_Val,
                                  unsigned int truncate_flags) {
  _fuse__F39F40F36(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListNode::__virtualStub25(int _f2_VarRefId, int _f2_Val,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListInner::__virtualStub25(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F21F22F33F23F24(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListEnd::__virtualStub25(int _f2_VarRefId, int _f2_Val,
                                  unsigned int truncate_flags) {
  _fuse__F39F40F36F30F31(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListNode::__virtualStub30(unsigned int truncate_flags) {
  _fuse__F6F7F8F9(this, truncate_flags);
}
void StmtListInner::__virtualStub30(unsigned int truncate_flags) {
  _fuse__F21F22F23F24(this, truncate_flags);
}
void StmtListEnd::__virtualStub30(unsigned int truncate_flags) {
  _fuse__F39F40F30F31(this, truncate_flags);
}
void StmtListNode::__virtualStub23(int _f2_VarRefId, int _f2_Val,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F32(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListInner::__virtualStub23(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F21F22F33(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListEnd::__virtualStub23(int _f2_VarRefId, int _f2_Val,
                                  unsigned int truncate_flags) {
  _fuse__F39F40F36(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListNode::__virtualStub26(int _f2_VarRefId, int _f2_Val,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F32F8F9(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListInner::__virtualStub26(int _f2_VarRefId, int _f2_Val,
                                    unsigned int truncate_flags) {
  _fuse__F21F22F33F23F24(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void StmtListEnd::__virtualStub26(int _f2_VarRefId, int _f2_Val,
                                  unsigned int truncate_flags) {
  _fuse__F39F40F36F30F31(this, _f2_VarRefId, _f2_Val, truncate_flags);
}
void Program::__virtualStub33(unsigned int truncate_flags) {
  _fuse__F1F2F3F4F5(this, truncate_flags);
}
void optimize(vector<Program *> &ls) {

#ifdef PAPI
  start_counters();
#endif
  auto t1 = std::chrono::high_resolution_clock::now();
  for (auto *f : ls) {
    // f->print();
    // f->desugarDecr();
    // f->desugarInc();
    // f->propagateConstantsAssignments();
    // f->foldConstants();
    // f->removeUnreachableBranches();

    // added by fuse transformer
    f->__virtualStub33(0b11111);
    //   f->print();
  }
  auto t2 = std::chrono::high_resolution_clock::now();
#ifdef PAPI
  read_counters();
  print_counters();
#endif
  printf(
      "Runtime: %llu microseconds\n",
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());
  printf("Tree Size:%d\n", ls[0]->computeSize());
}

int main(int argc, char **argv) {
  // number of functions
  int FCount = atoi(argv[1]);

  int Prog = atoi(argv[2]);
  // how many tree to create
  int Itters = 1;
  vector<Program *> ls;
  ls.resize(Itters);

  for (int i = 0; i < Itters; i++) {
    switch (Prog) {
    case 1: // random function of regular size repeated many times (horiz AST)
      ls[i] = createProgram1(FCount);
      break;
    case 2: // the ast is a really large function (vert AST)
      ls[i] = createLargeFunctionProg(FCount);
      break;
    case 3: // the ast is a really large function (vert AST)
      ls[i] = createLongLiveRangeProg(FCount, FCount);
      break;
    default:
      break;
    }
  }
#ifndef BUILD_ONLY
  optimize(ls);
#endif

#ifdef COUNT_VISITS
  printf("Node Visits: %d\n", _VISIT_COUNTER);
#endif
}
