class CBox {
public:
	vector<CBox*> contents;

	int width;
	int computedWidth;

	int height;
	int cumulativeHeight;
	int computedHeight;
}

void CBox::calcWidth() {

	computedWidth = width;
	for (auto c : contents) {
		c->calcWidth();
		computedWidth = max( computedWidth, c->computedWidth );
	}
}

void CBox::calcHeight() {
	cumulativeHeight = 0;
	for (auto c : contents) {
		c->calcHeight();
		cumulativeHeight += c->computedHeight;
	}
	computedHeight = max( height, cumulativeHeight );
}