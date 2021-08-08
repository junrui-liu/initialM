class CBox {
public:
	CBox* next;
	CBox* firstContent;

	int width;
	int computedWidth;
	int cumulativeWidth; // helper for computedWidth of parent

	int height;
	int computedHeight;
	int cumulativeHeight; // helper for computedHeight of parent
}

void CBox::fusedCalc() {

	firstContent->fusedCalc();
	next->fusedCalc();
	computedWidth = max( width, firstContent->cumulativeWidth );
	cumulativeWidth = max( computedWidth, next->cumulativeWidth );
	computedHeight = max( height, firstContent->cumulativeHeight );
	cumulativeHeight = computedHeight + next->cumulativeHeight;

}