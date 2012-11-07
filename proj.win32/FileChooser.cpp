#include "Chooser.h"


FileChooser::FileChooser()
{
	Chooser::Chooser();
}

FileChooser::FileChooser(b2World* world)
{
	Chooser::Chooser();
	_world = world;

	endVertex=1;
	startVertex=0;
}

Segment* FileChooser::init(){

	
	//open file and get first segment
	//const char* level = CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("level1.plist"))->getCString();
	level = CCDictionary::createWithContentsOfFileThreadSafe(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("level1.plist"));
    platforms = (CCDictionary*)level->objectForKey("platforms");
    numplatforms = level->valueForKey("numplatforms")->intValue();
	currplatform=0;

	return getNextSegment();
}

Segment* FileChooser::makePlatform(int type,int x,int y,int w,int h){
	
	Segment* segment;
	CCPoint* startPos= new CCPoint(x,y);
	switch(type){
	case 1://forward straight line
		segment = dynamic_cast<Segment*>(new LineSegment (_world,*startPos,w,h));
		startVertex=0;
		endVertex=1;
		break;
	case 2://backward straight line
		segment = dynamic_cast<Segment*>(new LineSegment (_world,*startPos,w,h));
		startVertex=1;
		endVertex=0;
		break;
	}
	return segment;
}

Segment* FileChooser::getNextSegment(){
		
	if(currplatform<numplatforms){
	CCDictionary *platform = (CCDictionary*)platforms->objectForKey(std::to_string(currplatform));
    int type = platform->valueForKey("type")->intValue();
    int x = platform->valueForKey("x")->intValue();
    int y = platform->valueForKey("y")->intValue();
    int w = platform->valueForKey("w")->intValue();
    int h = platform->valueForKey("h")->intValue();
	
	Segment* segment=makePlatform(type,x,y,w,h);
	
	currplatform++;
	return segment;
	}
	else{
		return 0;
	}
}