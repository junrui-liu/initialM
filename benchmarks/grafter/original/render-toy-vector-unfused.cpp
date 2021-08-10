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
void Inner::calcWidth() {
  computedWidth = width;
  for (auto c : contents) {
    c->calcWidth();
    computedWidth = max( computedWidth, c->computedWidth );
  }
}
void Inner::calcHeight() {
  cumulativeHeight = 0;
  for (auto c : contents) {
    c->calcHeight();
    cumulativeHeight += c->computedHeight;
  }
  computedHeight = max( height, cumulativeHeight );
}

class Leaf: public Box {}
void Leaf::calcWidth() {
  computedWidth = width;
}
void Leaf::calcHeight() {
  cumulativeHeight = 0;
  computedHeight = height;
}