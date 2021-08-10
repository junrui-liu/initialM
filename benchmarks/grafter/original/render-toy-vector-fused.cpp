class Box {
public:
  int width; // w0
  int computedWidth; // w

  int height; // h0
  int cumulativeHeight; // h1
  int computedHeight; // h
}

class Inner: public Box {
public:
  vector<Box*> contents; // cs
}
void Inner::fusedCalc() {
  computedWidth = width;
  cumulativeHeight = 0;
  for (auto c : contents) {
    c->fusedCalc();
    computedWidth = max( computedWidth, c->computedWidth );
    cumulativeHeight += c->computedHeight;
  }
  computedHeight = max( height, cumulativeHeight );
}

class Leaf: public Box {}
void Leaf::fusedCalc() {
  computedWidth = width;
  cumulativeHeight = 0;
  computedHeight = height;
}