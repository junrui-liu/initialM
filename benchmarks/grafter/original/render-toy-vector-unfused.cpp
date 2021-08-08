class CBox {
public:
	vector<CBox*> contents;

	int width;
	int computedWidth;

	int height;
	int cmumulativeHeight;
	int computedHeight;
}

void CBox::calcWidth() {

	computedWidth = width;
	for (auto c : contents) {
		c->calcWidth();
		computedWidth = max( width, c->computedWidth );
	}
}

void CBox::calcHeight() {
	cmumulativeHeight = 0;
	for (auto c : contents) {
		c->calcHeight();
		cmumulativeHeight += c->computedHeight;
	}
	computedHeight = max( height, cmumulativeHeight );
}