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
void Inner::fusedCalc() {
  firstContent->fusedCalc();
  next->fusedCalc();
  computedWidth = max( width, firstContent->cumulativeWidth );
  cumulativeWidth = max( computedWidth, next->cumulativeWidth );
  computedHeight = max( height, firstContent->cumulativeHeight );
  cumulativeHeight = computedHeight + next->cumulativeHeight;
}

class Leaf: public Box {
public:
  Box* next; // nx
}
void Inner::fusedCalc() {
  next->fusedCalc();
  computedWidth = width;
  cumulativeWidth = max( computedWidth, next->cumulativeWidth );
  computedHeight = height;
  cumulativeHeight = computedHeight + next->cumulativeHeight;
}