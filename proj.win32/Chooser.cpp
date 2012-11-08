#include "Chooser.h"


Chooser::Chooser()
{

}

Segment* Chooser::getNextSegment(){
	return 0;
}
	
Segment* Chooser::init(){
	return 0;
}

int Chooser::getEndVertex(){
	return endVertex;
}
	
int	Chooser::getStartVertex(){
	return startVertex;
}

CCPoint Chooser::getOffset(){
	return offset;
}
