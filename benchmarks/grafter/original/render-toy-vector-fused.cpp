class CBox {
public:
	vector<CBox*> contents;

	int width;
	int computedWidth;

	int height;
	int cmumulativeHeight;
	int computedHeight;
}

void CBox::fusedCalc() {

	computedWidth = width;
	cmumulativeHeight = 0;
	for (auto c : contents) {
		c->fusedCalc();
		computedWidth = max( computedWidth, c->computedWidth );
		cmumulativeHeight += c->computedHeight;
	}

	computedHeight = max( height, cmumulativeHeight );
}