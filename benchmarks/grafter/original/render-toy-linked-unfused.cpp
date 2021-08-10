class Box {
public:
  int width; // w0
  int cumulativeWidth; // w1
  int computedWidth; // w

  int height; // h0
  int cumulativeHeight; // h1
  int computedHeight; // h
}

class Inner: public Box {
public:
  Box* firstContent; // fc
  Box* next; // nx
}
void Inner::calcWidth() {
  firstContent->calcWidth();
  next->calcWidth();
  computedWidth = max( width, firstContent->cumulativeWidth );
  cumulativeWidth = max( computedWidth, next->cumulativeWidth );
}
void Inner::calcHeight() {
  firstContent->calcHeight();
  next->calcHeight();
  computedHeight = max( height, firstContent->cumulativeHeight );
  cumulativeHeight = computedHeight + next->cumulativeHeight;
}

class Leaf: public Box {
public:
  Box* next; // nx
}
void Leaf::calcWidth() {
  next->calcWidth();
  computedWidth = width;
  cumulativeWidth = max( computedWidth, next->cumulativeWidth );
}
void Leaf::calcHeight() {
  next->calcHeight();
  computedHeight = height;
  cumulativeHeight = computedHeight + next->cumulativeHeight;
}