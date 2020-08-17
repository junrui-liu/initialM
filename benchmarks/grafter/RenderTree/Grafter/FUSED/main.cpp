#include "ComputeHeights.h"
#include "DocBuilder.h"
#include "Print.h"
#include "RenderTree.h"
#include "ResolveFlexWidths.h"
#include "ResolveRelativeWidth.h"
#include "SetFont.h"
#include "SetPositions.h"
#include <chrono>
#include <stdlib.h>
#include <sys/time.h>

#pragma clang diagnostic ignored "-Wwritable-strings"

#ifdef PAPI
#include <iostream>
using namespace std;
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

void _fuse__F69F70F71F72F73(PageListInner *_r,
                            struct FontInfo _f2_ParentFontStyle,
                            unsigned int truncate_flags);
void _fuse__F60F61F62(VerticalContainer *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags);
void _fuse__F54F59F56(Image *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F54F55F56(Element *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F51F52F53(ElementListEnd *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags);
void _fuse__F48F49F50(ElementListNode *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags);
void _fuse__F21F22(HorizontalContainerListNode *_r,
                   struct FontInfo _f1_FontStyle, unsigned int truncate_flags);
void _fuse__F1F2F3F4F5(Document *_r, unsigned int truncate_flags);
void _fuse__F54F57F56(TextBox *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F16F17F18F19F20(Page *_r, struct FontInfo _f2_ParentFontStyle,
                            unsigned int truncate_flags);
void _fuse__F35F36(HorizontalContainerListInner *_r,
                   struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F11F12F13F14F15(PageListEnd *_r,
                            struct FontInfo _f2_ParentFontStyle,
                            unsigned int truncate_flags);
void _fuse__F31F32(Element *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F23F24(HorizontalContainerListEnd *_r,
                   struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F66F67F68(ElementListInner *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags);
void _fuse__F6F7F8F9F10(PageListNode *_r, struct FontInfo _f2_FontStyle,
                        unsigned int truncate_flags);
void _fuse__F33F34(VerticalContainer *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F25F26(HorizontalContainer *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F27F28(ElementListNode *_r, struct FontInfo _f1_FontStyle,
                   unsigned int truncate_flags);
void _fuse__F29F30(ElementListEnd *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F54F58F56(List *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F45F46F47(HorizontalContainer *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags);
void _fuse__F37F38(ElementListInner *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags);
void _fuse__F63F64F65(HorizontalContainerListInner *_r, int _f0_PWidth,
                      int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F39F40F41(HorizontalContainerListNode *_r, int _f0_PWidth,
                      int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F42F43F44(HorizontalContainerListEnd *_r, int _f0_PWidth,
                      int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags);
void _fuse__F69F70F71F72F73(PageListInner *_r,
                            struct FontInfo _f2_ParentFontStyle,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  PageListInner *_r_f0 = (PageListInner *)(_r);
  PageListInner *_r_f1 = (PageListInner *)(_r);
  PageListInner *_r_f2 = (PageListInner *)(_r);
  PageListInner *_r_f3 = (PageListInner *)(_r);
  PageListInner *_r_f4 = (PageListInner *)(_r);
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
    _fuse__F16F17F18F19F20(_r_f0->Content, _f2_ParentFontStyle,
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
    _r_f0->NextPage->__virtualStub15(_f2_ParentFontStyle,
                                     AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F60F61F62(VerticalContainer *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  VerticalContainer *_r_f0 = (VerticalContainer *)(_r);
  VerticalContainer *_r_f1 = (VerticalContainer *)(_r);
  VerticalContainer *_r_f2 = (VerticalContainer *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == REL) {
      _r_f0->Width = _r_f0->RelWidth * _f0_PWidth;
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
    _r_f0->HorizList->__virtualStub11(_r_f0->Width, _f2_CurrX, _f2_CurrY,
                                      AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    _r_f1->Height = _r_f1->HorizList->AggregatedHeight;
  }
_label_B2F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->PosX = _f2_CurrX;
    _r_f2->PosY = _f2_CurrY;
  }
_label_B2F2_Exit:
  return;
};
void _fuse__F54F59F56(Image *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Element *_r_f0 = (Element *)(_r);
  Image *_r_f1 = (Image *)(_r);
  Element *_r_f2 = (Element *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == REL) {
      _r_f0->Width = _r_f0->RelWidth * _f0_PWidth;
    }
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->Height =
        _r_f1->Width * (_r_f1->ImageOriginalHeight / _r_f1->ImageOriginalWidth);
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->PosX = _f2_CurrX;
    _r_f2->PosY = _f2_CurrY;
  }
_label_B1F2_Exit:
  return;
};
void _fuse__F54F55F56(Element *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Element *_r_f0 = (Element *)(_r);
  Element *_r_f1 = (Element *)(_r);
  Element *_r_f2 = (Element *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == REL) {
      _r_f0->Width = _r_f0->RelWidth * _f0_PWidth;
    }
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->PosX = _f2_CurrX;
    _r_f2->PosY = _f2_CurrY;
  }
_label_B1F2_Exit:
  return;
};
void _fuse__F51F52F53(ElementListEnd *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ElementListEnd *_r_f0 = (ElementListEnd *)(_r);
  ElementListEnd *_r_f1 = (ElementListEnd *)(_r);
  ElementListEnd *_r_f2 = (ElementListEnd *)(_r);
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Content->__virtualStub10(_f0_PWidth, _f2_CurrX, _f2_CurrY,
                                    AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    _r_f1->MaxHeight = _r_f1->Content->Height;
  }
_label_B2F1_Exit:
  return;
};
void _fuse__F48F49F50(ElementListNode *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ElementListNode *_r_f0 = (ElementListNode *)(_r);
  ElementListNode *_r_f1 = (ElementListNode *)(_r);
  ElementListNode *_r_f2 = (ElementListNode *)(_r);
  return;
};
void _fuse__F21F22(HorizontalContainerListNode *_r,
                   struct FontInfo _f1_FontStyle, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainerListNode *_r_f0 = (HorizontalContainerListNode *)(_r);
  HorizontalContainerListNode *_r_f1 = (HorizontalContainerListNode *)(_r);
  return;
};
void _fuse__F1F2F3F4F5(Document *_r, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Document *_r_f0 = (Document *)(_r);
  Document *_r_f1 = (Document *)(_r);
  Document *_r_f2 = (Document *)(_r);
  Document *_r_f3 = (Document *)(_r);
  Document *_r_f4 = (Document *)(_r);
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
    _r_f0->PageList->__virtualStub0(_r_f2->FontStyle, AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F54F57F56(TextBox *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Element *_r_f0 = (Element *)(_r);
  TextBox *_r_f1 = (TextBox *)(_r);
  Element *_r_f2 = (Element *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == REL) {
      _r_f0->Width = _r_f0->RelWidth * _f0_PWidth;
    }
  }
_label_B1F0_Exit:
  int _f1_CharsTotalSpace;
  if (truncate_flags & 0b10) {
    _f1_CharsTotalSpace =
        computeTextHorizSpace(_r_f1->ContentText.Length, _r_f1->FontStyle.Size);
    _r_f1->Height = (_f1_CharsTotalSpace / _r_f1->Width);
    if (_f1_CharsTotalSpace % _r_f1->Width) {
      _r_f1->Height = _r_f1->Height + 1;
    }
    _r_f1->Height = _r_f1->Height * getCharHeight(_r_f1->FontStyle.Size);
    if (_r_f1->FontStyle.Size == (0 - 1)) {
      LogErrorFontNotSet();
    }
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->PosX = _f2_CurrX;
    _r_f2->PosY = _f2_CurrY;
  }
_label_B1F2_Exit:
  return;
};
void _fuse__F16F17F18F19F20(Page *_r, struct FontInfo _f2_ParentFontStyle,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Page *_r_f0 = (Page *)(_r);
  Page *_r_f1 = (Page *)(_r);
  Page *_r_f2 = (Page *)(_r);
  Page *_r_f3 = (Page *)(_r);
  Page *_r_f4 = (Page *)(_r);
  if (truncate_flags & 0b10) {
    if (_r_f1->WMode == REL) {
      LogError2();
      truncate_flags &= 0b11111111101;
      goto _label_B1F1_Exit;
    }
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    if (_r_f2->FontStyle.Size == (0 - 1)) {
      _r_f2->FontStyle.Size = _f2_ParentFontStyle.Size;
    }
    if (_r_f2->FontStyle.Color == (0 - 1)) {
      _r_f2->FontStyle.Color = _f2_ParentFontStyle.Color;
    }
    if (_r_f2->FontStyle.Type == (0 - 1)) {
      _r_f2->FontStyle.Type = _f2_ParentFontStyle.Type;
    }
  }
_label_B1F2_Exit:
  if ((truncate_flags & 0b101)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f2->HorizList->__virtualStub1(_r_f2->FontStyle, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == FLEX) {
      _r_f0->Width = _r_f0->HorizList->MaxWidth;
    }
  }
_label_B2F0_Exit:
  if (truncate_flags & 0b10000) {
    _r_f4->PosX = 0;
    _r_f4->PosY = 0;
  }
_label_B2F4_Exit:
  if ((truncate_flags & 0b11010)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 4));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 3));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    _r_f4->HorizList->__virtualStub8(_r_f1->Width, _r_f4->PosX, _r_f4->PosY,
                                     AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1000) {
    _r_f3->Height = _r_f3->HorizList->AggregatedHeight;
  }
_label_B3F3_Exit:
  return;
};
void _fuse__F35F36(HorizontalContainerListInner *_r,
                   struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainerListInner *_r_f0 = (HorizontalContainerListInner *)(_r);
  HorizontalContainerListInner *_r_f1 = (HorizontalContainerListInner *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _fuse__F25F26(_r_f0->Content, _f1_ParentFontStyle, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Next->__virtualStub5(_f1_ParentFontStyle, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->Content->Width > _r_f0->Next->MaxWidth) {
      _r_f0->MaxWidth = _r_f0->Content->Width;
    } else {
      _r_f0->MaxWidth = _r_f0->Next->MaxWidth;
    }
  }
_label_B3F0_Exit:
  return;
};
void _fuse__F11F12F13F14F15(PageListEnd *_r,
                            struct FontInfo _f2_ParentFontStyle,
                            unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  PageListEnd *_r_f0 = (PageListEnd *)(_r);
  PageListEnd *_r_f1 = (PageListEnd *)(_r);
  PageListEnd *_r_f2 = (PageListEnd *)(_r);
  PageListEnd *_r_f3 = (PageListEnd *)(_r);
  PageListEnd *_r_f4 = (PageListEnd *)(_r);
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
    _fuse__F16F17F18F19F20(_r_f0->Content, _f2_ParentFontStyle,
                           AdjustedTruncateFlags);
  }
  return;
};
void _fuse__F31F32(Element *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Element *_r_f0 = (Element *)(_r);
  Element *_r_f1 = (Element *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == FLEX) {
      LogError1();
    }
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    if (_r_f1->FontStyle.Size == (0 - 1)) {
      _r_f1->FontStyle.Size = _f1_ParentFontStyle.Size;
    }
    if (_r_f1->FontStyle.Color == (0 - 1)) {
      _r_f1->FontStyle.Color = _f1_ParentFontStyle.Color;
    }
    if (_r_f1->FontStyle.Type == (0 - 1)) {
      _r_f1->FontStyle.Type = _f1_ParentFontStyle.Type;
    }
  }
_label_B1F1_Exit:
  return;
};
void _fuse__F23F24(HorizontalContainerListEnd *_r,
                   struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainerListEnd *_r_f0 = (HorizontalContainerListEnd *)(_r);
  HorizontalContainerListEnd *_r_f1 = (HorizontalContainerListEnd *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _fuse__F25F26(_r_f0->Content, _f1_ParentFontStyle, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    _r_f0->MaxWidth = _r_f0->Content->Width;
  }
_label_B2F0_Exit:
  return;
};
void _fuse__F66F67F68(ElementListInner *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ElementListInner *_r_f0 = (ElementListInner *)(_r);
  ElementListInner *_r_f1 = (ElementListInner *)(_r);
  ElementListInner *_r_f2 = (ElementListInner *)(_r);
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Content->__virtualStub13(_f0_PWidth, _f2_CurrX, _f2_CurrY,
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
    _r_f2->Next->__virtualStub14(_f0_PWidth, _f2_CurrX + _r_f2->Content->Width,
                                 _f2_CurrY, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    if (_r_f1->Content->Height >= _r_f1->Next->MaxHeight) {
      _r_f1->MaxHeight = _r_f1->Content->Height;
    } else {
      _r_f1->MaxHeight = _r_f1->Next->MaxHeight;
    }
  }
_label_B3F1_Exit:
  return;
};
void _fuse__F6F7F8F9F10(PageListNode *_r, struct FontInfo _f2_FontStyle,
                        unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  PageListNode *_r_f0 = (PageListNode *)(_r);
  PageListNode *_r_f1 = (PageListNode *)(_r);
  PageListNode *_r_f2 = (PageListNode *)(_r);
  PageListNode *_r_f3 = (PageListNode *)(_r);
  PageListNode *_r_f4 = (PageListNode *)(_r);
  return;
};
void _fuse__F33F34(VerticalContainer *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  VerticalContainer *_r_f0 = (VerticalContainer *)(_r);
  VerticalContainer *_r_f1 = (VerticalContainer *)(_r);
  if (truncate_flags & 0b10) {
    if (_r_f1->FontStyle.Size == (0 - 1)) {
      _r_f1->FontStyle.Size = _f1_ParentFontStyle.Size;
    }
    if (_r_f1->FontStyle.Color == (0 - 1)) {
      _r_f1->FontStyle.Color = _f1_ParentFontStyle.Color;
    }
    if (_r_f1->FontStyle.Type == (0 - 1)) {
      _r_f1->FontStyle.Type = _f1_ParentFontStyle.Type;
    }
  }
_label_B1F1_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f1->HorizList->__virtualStub4(_r_f1->FontStyle, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == FLEX) {
      _r_f0->Width = _r_f0->HorizList->MaxWidth;
    }
  }
_label_B2F0_Exit:
  return;
};
void _fuse__F25F26(HorizontalContainer *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainer *_r_f0 = (HorizontalContainer *)(_r);
  HorizontalContainer *_r_f1 = (HorizontalContainer *)(_r);
  if (truncate_flags & 0b10) {
    if (_r_f1->FontStyle.Size == (0 - 1)) {
      _r_f1->FontStyle.Size = _f1_ParentFontStyle.Size;
    }
    if (_r_f1->FontStyle.Color == (0 - 1)) {
      _r_f1->FontStyle.Color = _f1_ParentFontStyle.Color;
    }
    if (_r_f1->FontStyle.Type == (0 - 1)) {
      _r_f1->FontStyle.Type = _f1_ParentFontStyle.Type;
    }
  }
_label_B1F1_Exit:
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f1->ElementsList->__virtualStub2(_r_f1->FontStyle,
                                        AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == FLEX) {
      _r_f0->Width = _r_f0->ElementsList->AccumulatedWidth;
    }
  }
_label_B2F0_Exit:
  return;
};
void _fuse__F27F28(ElementListNode *_r, struct FontInfo _f1_FontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ElementListNode *_r_f0 = (ElementListNode *)(_r);
  ElementListNode *_r_f1 = (ElementListNode *)(_r);
  return;
};
void _fuse__F29F30(ElementListEnd *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ElementListEnd *_r_f0 = (ElementListEnd *)(_r);
  ElementListEnd *_r_f1 = (ElementListEnd *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Content->__virtualStub3(_f1_ParentFontStyle, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    _r_f0->AccumulatedWidth = _r_f0->Content->Width;
  }
_label_B2F0_Exit:
  return;
};
void _fuse__F54F58F56(List *_r, int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  Element *_r_f0 = (Element *)(_r);
  List *_r_f1 = (List *)(_r);
  Element *_r_f2 = (Element *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == REL) {
      _r_f0->Width = _r_f0->RelWidth * _f0_PWidth;
    }
  }
_label_B1F0_Exit:
  if (truncate_flags & 0b10) {
    _r_f1->Height = computeListHeight(_r_f1->Items, _r_f1->FontStyle.Size,
                                      _r_f1->ItemMargin, _r_f1->Width);
    if (_r_f1->FontStyle.Size == (0 - 1)) {
      LogErrorFontNotSet();
    }
  }
_label_B1F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->PosX = _f2_CurrX;
    _r_f2->PosY = _f2_CurrY;
  }
_label_B1F2_Exit:
  return;
};
void _fuse__F45F46F47(HorizontalContainer *_r, int _f0_PWidth, int _f2_CurrX,
                      int _f2_CurrY, unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainer *_r_f0 = (HorizontalContainer *)(_r);
  HorizontalContainer *_r_f1 = (HorizontalContainer *)(_r);
  HorizontalContainer *_r_f2 = (HorizontalContainer *)(_r);
  if (truncate_flags & 0b1) {
    if (_r_f0->WMode == REL) {
      _r_f0->Width = _r_f0->RelWidth * _f0_PWidth;
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
    _r_f0->ElementsList->__virtualStub9(_r_f0->Width, _f2_CurrX, _f2_CurrY,
                                        AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    _r_f1->Height = _r_f1->ElementsList->MaxHeight;
  }
_label_B2F1_Exit:
  if (truncate_flags & 0b100) {
    _r_f2->PosX = _f2_CurrX;
    _r_f2->PosY = _f2_CurrY;
  }
_label_B2F2_Exit:
  return;
};
void _fuse__F37F38(ElementListInner *_r, struct FontInfo _f1_ParentFontStyle,
                   unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  ElementListInner *_r_f0 = (ElementListInner *)(_r);
  ElementListInner *_r_f1 = (ElementListInner *)(_r);
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Next->__virtualStub6(_f1_ParentFontStyle, AdjustedTruncateFlags);
  }
  if ((truncate_flags & 0b11)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _r_f0->Content->__virtualStub7(_f1_ParentFontStyle, AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b1) {
    _r_f0->AccumulatedWidth =
        _r_f0->Content->Width + _r_f0->Next->AccumulatedWidth;
  }
_label_B3F0_Exit:
  return;
};
void _fuse__F63F64F65(HorizontalContainerListInner *_r, int _f0_PWidth,
                      int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainerListInner *_r_f0 = (HorizontalContainerListInner *)(_r);
  HorizontalContainerListInner *_r_f1 = (HorizontalContainerListInner *)(_r);
  HorizontalContainerListInner *_r_f2 = (HorizontalContainerListInner *)(_r);
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _fuse__F45F46F47(_r_f0->Content, _f0_PWidth, _f2_CurrX, _f2_CurrY,
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
    _r_f2->Next->__virtualStub12(_f0_PWidth, _f2_CurrX,
                                 _f2_CurrY + _r_f2->Content->Height,
                                 AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    _r_f1->AggregatedHeight = 0;
    _r_f1->AggregatedHeight = _r_f1->AggregatedHeight + _r_f1->Content->Height;
    _r_f1->AggregatedHeight =
        _r_f1->AggregatedHeight + _r_f1->Next->AggregatedHeight;
  }
_label_B3F1_Exit:
  return;
};
void _fuse__F39F40F41(HorizontalContainerListNode *_r, int _f0_PWidth,
                      int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainerListNode *_r_f0 = (HorizontalContainerListNode *)(_r);
  HorizontalContainerListNode *_r_f1 = (HorizontalContainerListNode *)(_r);
  HorizontalContainerListNode *_r_f2 = (HorizontalContainerListNode *)(_r);
  return;
};
void _fuse__F42F43F44(HorizontalContainerListEnd *_r, int _f0_PWidth,
                      int _f2_CurrX, int _f2_CurrY,
                      unsigned int truncate_flags) {

#ifdef COUNT_VISITS
  _VISIT_COUNTER++;
#endif
  HorizontalContainerListEnd *_r_f0 = (HorizontalContainerListEnd *)(_r);
  HorizontalContainerListEnd *_r_f1 = (HorizontalContainerListEnd *)(_r);
  HorizontalContainerListEnd *_r_f2 = (HorizontalContainerListEnd *)(_r);
  if ((truncate_flags & 0b111)) /*call*/ {
    unsigned int AdjustedTruncateFlags = 0;
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 2));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 1));
    AdjustedTruncateFlags <<= 1;
    AdjustedTruncateFlags |= (0b01 & (truncate_flags >> 0));
    _fuse__F45F46F47(_r_f0->Content, _f0_PWidth, _f2_CurrX, _f2_CurrY,
                     AdjustedTruncateFlags);
  }
  if (truncate_flags & 0b10) {
    _r_f1->AggregatedHeight = _r_f1->Content->Height;
  }
_label_B2F1_Exit:
  return;
};
void PageListNode::__virtualStub0(struct FontInfo _f2_FontStyle,
                                  unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, _f2_FontStyle, truncate_flags);
}
void PageListEnd::__virtualStub0(struct FontInfo _f2_FontStyle,
                                 unsigned int truncate_flags) {
  _fuse__F11F12F13F14F15(this, _f2_FontStyle, truncate_flags);
}
void PageListInner::__virtualStub0(struct FontInfo _f2_FontStyle,
                                   unsigned int truncate_flags) {
  _fuse__F69F70F71F72F73(this, _f2_FontStyle, truncate_flags);
}
void PageListNode::__virtualStub15(struct FontInfo _f2_FontStyle,
                                   unsigned int truncate_flags) {
  _fuse__F6F7F8F9F10(this, _f2_FontStyle, truncate_flags);
}
void PageListEnd::__virtualStub15(struct FontInfo _f2_FontStyle,
                                  unsigned int truncate_flags) {
  _fuse__F11F12F13F14F15(this, _f2_FontStyle, truncate_flags);
}
void PageListInner::__virtualStub15(struct FontInfo _f2_FontStyle,
                                    unsigned int truncate_flags) {
  _fuse__F69F70F71F72F73(this, _f2_FontStyle, truncate_flags);
}
void HorizontalContainerListNode::__virtualStub1(struct FontInfo _f1_FontStyle,
                                                 unsigned int truncate_flags) {
  _fuse__F21F22(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListEnd::__virtualStub1(struct FontInfo _f1_FontStyle,
                                                unsigned int truncate_flags) {
  _fuse__F23F24(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListInner::__virtualStub1(struct FontInfo _f1_FontStyle,
                                                  unsigned int truncate_flags) {
  _fuse__F35F36(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListNode::__virtualStub5(struct FontInfo _f1_FontStyle,
                                                 unsigned int truncate_flags) {
  _fuse__F21F22(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListEnd::__virtualStub5(struct FontInfo _f1_FontStyle,
                                                unsigned int truncate_flags) {
  _fuse__F23F24(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListInner::__virtualStub5(struct FontInfo _f1_FontStyle,
                                                  unsigned int truncate_flags) {
  _fuse__F35F36(this, _f1_FontStyle, truncate_flags);
}
void ElementListNode::__virtualStub2(struct FontInfo _f1_FontStyle,
                                     unsigned int truncate_flags) {
  _fuse__F27F28(this, _f1_FontStyle, truncate_flags);
}
void ElementListEnd::__virtualStub2(struct FontInfo _f1_FontStyle,
                                    unsigned int truncate_flags) {
  _fuse__F29F30(this, _f1_FontStyle, truncate_flags);
}
void ElementListInner::__virtualStub2(struct FontInfo _f1_FontStyle,
                                      unsigned int truncate_flags) {
  _fuse__F37F38(this, _f1_FontStyle, truncate_flags);
}
void Element::__virtualStub3(struct FontInfo _f1_ParentFontStyle,
                             unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void TextBox::__virtualStub3(struct FontInfo _f1_ParentFontStyle,
                             unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void List::__virtualStub3(struct FontInfo _f1_ParentFontStyle,
                          unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void Image::__virtualStub3(struct FontInfo _f1_ParentFontStyle,
                           unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void VerticalContainer::__virtualStub3(struct FontInfo _f1_ParentFontStyle,
                                       unsigned int truncate_flags) {
  _fuse__F33F34(this, _f1_ParentFontStyle, truncate_flags);
}
void ElementListNode::__virtualStub6(struct FontInfo _f1_FontStyle,
                                     unsigned int truncate_flags) {
  _fuse__F27F28(this, _f1_FontStyle, truncate_flags);
}
void ElementListEnd::__virtualStub6(struct FontInfo _f1_FontStyle,
                                    unsigned int truncate_flags) {
  _fuse__F29F30(this, _f1_FontStyle, truncate_flags);
}
void ElementListInner::__virtualStub6(struct FontInfo _f1_FontStyle,
                                      unsigned int truncate_flags) {
  _fuse__F37F38(this, _f1_FontStyle, truncate_flags);
}
void Element::__virtualStub7(struct FontInfo _f1_ParentFontStyle,
                             unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void TextBox::__virtualStub7(struct FontInfo _f1_ParentFontStyle,
                             unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void List::__virtualStub7(struct FontInfo _f1_ParentFontStyle,
                          unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void Image::__virtualStub7(struct FontInfo _f1_ParentFontStyle,
                           unsigned int truncate_flags) {
  _fuse__F31F32(this, _f1_ParentFontStyle, truncate_flags);
}
void VerticalContainer::__virtualStub7(struct FontInfo _f1_ParentFontStyle,
                                       unsigned int truncate_flags) {
  _fuse__F33F34(this, _f1_ParentFontStyle, truncate_flags);
}
void HorizontalContainerListNode::__virtualStub4(struct FontInfo _f1_FontStyle,
                                                 unsigned int truncate_flags) {
  _fuse__F21F22(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListEnd::__virtualStub4(struct FontInfo _f1_FontStyle,
                                                unsigned int truncate_flags) {
  _fuse__F23F24(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListInner::__virtualStub4(struct FontInfo _f1_FontStyle,
                                                  unsigned int truncate_flags) {
  _fuse__F35F36(this, _f1_FontStyle, truncate_flags);
}
void HorizontalContainerListNode::__virtualStub8(int _f0_PWidth, int _f2_CurrX,
                                                 int _f2_CurrY,
                                                 unsigned int truncate_flags) {
  _fuse__F39F40F41(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListEnd::__virtualStub8(int _f0_PWidth, int _f2_CurrX,
                                                int _f2_CurrY,
                                                unsigned int truncate_flags) {
  _fuse__F42F43F44(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListInner::__virtualStub8(int _f0_PWidth, int _f2_CurrX,
                                                  int _f2_CurrY,
                                                  unsigned int truncate_flags) {
  _fuse__F63F64F65(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListNode::__virtualStub12(int _f0_PWidth, int _f2_CurrX,
                                                  int _f2_CurrY,
                                                  unsigned int truncate_flags) {
  _fuse__F39F40F41(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListEnd::__virtualStub12(int _f0_PWidth, int _f2_CurrX,
                                                 int _f2_CurrY,
                                                 unsigned int truncate_flags) {
  _fuse__F42F43F44(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListInner::__virtualStub12(
    int _f0_PWidth, int _f2_CurrX, int _f2_CurrY, unsigned int truncate_flags) {
  _fuse__F63F64F65(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void ElementListNode::__virtualStub9(int _f0_PWidth, int _f2_CurrX,
                                     int _f2_CurrY,
                                     unsigned int truncate_flags) {
  _fuse__F48F49F50(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void ElementListEnd::__virtualStub9(int _f0_PWidth, int _f2_CurrX,
                                    int _f2_CurrY,
                                    unsigned int truncate_flags) {
  _fuse__F51F52F53(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void ElementListInner::__virtualStub9(int _f0_PWidth, int _f2_CurrX,
                                      int _f2_CurrY,
                                      unsigned int truncate_flags) {
  _fuse__F66F67F68(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void Element::__virtualStub10(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                              unsigned int truncate_flags) {
  _fuse__F54F55F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void TextBox::__virtualStub10(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                              unsigned int truncate_flags) {
  _fuse__F54F57F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void List::__virtualStub10(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                           unsigned int truncate_flags) {
  _fuse__F54F58F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void Image::__virtualStub10(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                            unsigned int truncate_flags) {
  _fuse__F54F59F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void VerticalContainer::__virtualStub10(int _f0_PWidth, int _f2_CurrX,
                                        int _f2_CurrY,
                                        unsigned int truncate_flags) {
  _fuse__F60F61F62(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void Element::__virtualStub13(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                              unsigned int truncate_flags) {
  _fuse__F54F55F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void TextBox::__virtualStub13(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                              unsigned int truncate_flags) {
  _fuse__F54F57F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void List::__virtualStub13(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                           unsigned int truncate_flags) {
  _fuse__F54F58F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void Image::__virtualStub13(int _f0_PWidth, int _f2_CurrX, int _f2_CurrY,
                            unsigned int truncate_flags) {
  _fuse__F54F59F56(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void VerticalContainer::__virtualStub13(int _f0_PWidth, int _f2_CurrX,
                                        int _f2_CurrY,
                                        unsigned int truncate_flags) {
  _fuse__F60F61F62(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void ElementListNode::__virtualStub14(int _f0_PWidth, int _f2_CurrX,
                                      int _f2_CurrY,
                                      unsigned int truncate_flags) {
  _fuse__F48F49F50(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void ElementListEnd::__virtualStub14(int _f0_PWidth, int _f2_CurrX,
                                     int _f2_CurrY,
                                     unsigned int truncate_flags) {
  _fuse__F51F52F53(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void ElementListInner::__virtualStub14(int _f0_PWidth, int _f2_CurrX,
                                       int _f2_CurrY,
                                       unsigned int truncate_flags) {
  _fuse__F66F67F68(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListNode::__virtualStub11(int _f0_PWidth, int _f2_CurrX,
                                                  int _f2_CurrY,
                                                  unsigned int truncate_flags) {
  _fuse__F39F40F41(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListEnd::__virtualStub11(int _f0_PWidth, int _f2_CurrX,
                                                 int _f2_CurrY,
                                                 unsigned int truncate_flags) {
  _fuse__F42F43F44(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void HorizontalContainerListInner::__virtualStub11(
    int _f0_PWidth, int _f2_CurrX, int _f2_CurrY, unsigned int truncate_flags) {
  _fuse__F63F64F65(this, _f0_PWidth, _f2_CurrX, _f2_CurrY, truncate_flags);
}
void render(Document *Doc) {

#ifdef PAPI
  start_counters();
#endif
  auto t1 = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 1; i++) {
    // Doc->resolveFlexWidths();
    // Doc->resolveRelativeWidths();
    // Doc->setFont();
    // Doc->computeHeights();
    // Doc->setPositions();

    // added by fuse transformer
    _fuse__F1F2F3F4F5(Doc, 0b11111);
  }

  auto t2 = std::chrono::high_resolution_clock::now();
#ifdef PAPI
  read_counters();
  print_counters();
#endif

  printf(
      "Runtime: %llu microseconds\n",
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count());

  printf("Tree Size :%d\n", Doc->computeTreeSize());
}

int main(int argc, char **argv) {
  int N = atoi(argv[1]);
  int prog = atoi(argv[2]);

  Document *Doc;
  if (prog == 1)
    Doc = BuildDoc1(N);
  else if (prog == 2)
    Doc = BuildDoc2(N);
  else if (prog == 3)
    Doc = BuildDoc3(N, N / 5);
#ifndef BUILD_ONLY
  render(Doc);
#endif

#ifdef COUNT_VISITS
  printf("Node Visits: %d\n", _VISIT_COUNTER);
#endif
}
