#include "B2dPlay.h" 
#include "LineSegment.h"

void B2dPlay::draw(){
	B2DLayer::draw();
}
// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool B2dPlay::init(){
	B2DLayer::init();
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2World *world = B2DLayer::world;
	b2Body* groundBody = B2DLayer::world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	this->scheduleUpdate();
	b2Vec2 start = b2Vec2::b2Vec2();
	start.Set(2,3);
	b2Vec2 end = b2Vec2::b2Vec2();
	end.Set(0,0);
	lineSegmentTest();
	B2DLayer::Debug(true);
	return true;
}  
//
void B2dPlay::lineSegmentTest(){
	b2Vec2 start = b2Vec2::b2Vec2();
	start.Set(120,100);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	StraightLineSegment segment(B2DLayer::world,start,120.0f,10.0f);
	//segment.GenerateNextBody();
	ContinuousLineSegment* child;
	EdgeLineSegment* edge = new EdgeLineSegment(world,b2Vec2(50.0f,100.0f),0,100);
	edge->InitilizeData();
	//edge->SetChild(new InclineLineSegment(B2DLayer::world,start,120.0f,50.0f,5),2);
	edge->SetChild(new StraightLineSegment(B2DLayer::world,start,120.0f,50.0f),2);
	child = edge->GetChild();
	//child->SetChild(new StraightLineSegment(B2DLayer::world,start,120.0f,50.0f),2);
	child->SetChild(new EdgeLineSegment(world,b2Vec2(50.0f,100.0f),100,40),2);
	child = child->GetChild();
	child->SetChild(new EdgeLineSegment(world,b2Vec2(100.0f,100.0f),100,-40),2);
	child = child->GetChild();
	//child->SetChild(new EdgeLineSegment(world,b2Vec2(100.0f,100.0f),100,-100),1);
	child->SetChild(new StraightLineSegment(B2DLayer::world,start,120.0f,50.0f),2);
	edge->GenerateNextBody();
	child = edge->GetChild();
	child->SetChild(new StraightLineSegment(B2DLayer::world,start,120.0f,50.0f),2);
	child = child->GetChild();
	child->SetChild(new EdgeLineSegment(world,b2Vec2(100.0f,100.0f),0,50),2);
	child = child->GetChild();
	child->SetChild(new EdgeLineSegment(world,b2Vec2(100.0f,100.0f),200,0),1);
	b2Vec2* vec = child->GetGameWorldVerticies(2);
	vec->x += 50;
	vec->y += 20;
	EdgeLineSegment* edge2 = new EdgeLineSegment(world,*vec,0,100);
	
	edge2->InitilizeData();
	//edge2->GenerateNextBody();
	// InclineLineSegment segment(B2DLayer::world,start,120.0f,360.0f,30.0f);
	//segment.InitilizeData();
	//segment.GetChild();
	//segment.SetChild(new StraightLineSegment(B2DLayer::world,start,120.0f,50.0f),&segment);
	//ContinuousLineSegment* child = segment.GetChild();
	//child->SetChild(new InclineLineSegment(B2DLayer::world,start,120.0f,50.0f,-10),child);
	//segment.GenerateBody();
	//// LineSegment segment(B2DLayer::world,start,10.0f,10.0f,240.0f);

	//LineSegment segment(B2DLayer::world,start,120.0f,15.0f,80.0f);

	//	 b2Vec2 Vert3 = segment.GetGameWorldVerticies(2);
	//	 start.Set((Vert3.x+40.0f),Vert3.y-5.0f);
	//	 //
	//	 LineSegment segment2(B2DLayer::world,start,10.0f,10.0f,80.0f);
	//	 segment2.GenerateBody(body);
	//
	//	 Vert3 = segment2.GetGameWorldVerticies(2);
	//	 start.Set((Vert3.x+5),Vert3.y-5.0f);
	//	 //LineSegment segment2(B2DLayer::world,start,120.0f,-10.0f,240.0f);
	//	 LineSegment segment3(B2DLayer::world,start,80.0f,-10.0f,80.0f);
	//	 segment3.GenerateBody(body);
	//
	//	 Vert3 = segment3.GetGameWorldVerticies(2);
	//	 start.Set((Vert3.x+4),Vert3.y-5.0f);
	//	 //LineSegment segment2(B2DLayer::world,start,120.0f,-10.0f,240.0f);
	//	 LineSegment segment4(B2DLayer::world,start,120.0f,10.0f,100.0f);
	//	 segment4.GenerateBody(body);
	//	 //start.Set(segment._GameWorldVerticies
	//	// body->SetTransform(body->GetPosition(),45 * DEGTORAD);
	//	// 	while(segment.GenerateNextBody(body)){
	//	//	//move boss
	//	//}
	//	// 	 start.Set(200,230);
	//	//LineSegment segment2(B2DLayer::world,start,120.0f,120.0f,80.0f);
	//	//	 		while(segment2.GenerateNextBody(body)){
	//	//	//move boss
	//	//}
	//	b2Body *body = NULL;
	//

}

void B2dPlay::DrawHill(b2Vec2 start,b2Vec2 end,float stepWidth,int width,int peak){
	int steps = width/stepWidth;
	float sideStepCount = steps/2;
	float inclinePerStep = peak/(sideStepCount);
	float innerHeight = peak/sideStepCount;
	b2Vec2 vertices[4];
	b2Vec2  startPos = start;
	for(int i = 1;i<= steps;i++){
		if(i>steps/2){
			GetVertsInclineSquare(vertices,stepWidth,innerHeight,(-1*inclinePerStep));
			GenSquare(vertices,world,startPos);
			startPos.x += vertices[1].x+(vertices[1].x);
			startPos.y +=-(((inclinePerStep/2)));
		}else{
			GetVertsInclineSquare(vertices,stepWidth,innerHeight,inclinePerStep);
			GenSquare(vertices,world,startPos);
			startPos.x += vertices[2].x+(vertices[2].x);
			startPos.y +=(inclinePerStep/2);
		}
	}
}



void B2dPlay::GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline){
	vertices[0].Set(-width/2, -height/2);
	vertices[1].Set(width/2, (-height/2)+(incline/2));
	vertices[2].Set(width/2, (height/2)+(incline/2));
	vertices[3].Set(-width/2, height/2);
}

void B2dPlay::GetVerts(b2Vec2 vertices[],float width,float height){
	//float width = 4;
	//float height = 1;
	//vert 1 
	//vertices[0].Set(-1.0f, -1.0f);
	//vertices[1].Set(1.0f, -1.0f);
	//vertices[2].Set(1.0f, 1.0f);
	//vertices[3].Set(-5.0f, 1.0f);
	vertices[0].Set(-width/2, -height/2);
	vertices[1].Set(width/2, -height/2);
	vertices[2].Set(width/2, height/2);
	vertices[3].Set(-width/2, height/2);
}

b2FixtureDef* B2dPlay::GenSquare(b2Vec2 vertices[],b2World* world,b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x,position.y);
	body =B2DLayer::world->CreateBody(&bodyDef);
	int32 count = 4;
	b2PolygonShape polygon;
	polygon.Set(vertices, count);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	//polygon.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &polygon;
	fixtureDef2.density = 1.0f;
	fixtureDef2.friction = 0.3f;
	body->CreateFixture(&fixtureDef2);
	float newAngle = 45;
	//body->SetTransform( body->GetPosition(),newAngle * DEGTORAD);
	return NULL;
}

//b2FixtureDef* B2dPlay::GenSquare(float width, float height,b2World* world)
//{
//b2BodyDef bodyDef;
//bodyDef.type = b2_kinematicBody;
//bodyDef.position.Set(5.0f, 8.0f);
//body =B2DLayer::world->CreateBody(&bodyDef);
//int32 count = 4;
//b2PolygonShape polygon;
//b2Vec2 verts[4];
//GetVerts(verts,1,4);
//polygon.Set(verts, count);
//b2FixtureDef fixtureDef;
//fixtureDef.shape = &polygon;
//fixtureDef.density = 1.0f;
//fixtureDef.friction = 0.3f;
////polygon.SetAsBox(1.0f, 1.0f);
//b2FixtureDef fixtureDef2;
//fixtureDef2.shape = &polygon;
//fixtureDef2.density = 1.0f;
//fixtureDef2.friction = 0.3f;
//body->CreateFixture(&fixtureDef2);
//float newAngle = 45;
//body->SetTransform( body->GetPosition(),newAngle * DEGTORAD);
//return NULL;
//}

void B2dPlay::menuCloseCallback(CCObject* pSender){
}

void B2dPlay::ccTouchesBegan(CCSet* touches, cocos2d::CCEvent* event){
}

void B2dPlay::update(float dt){
	//float angle = body->GetAngle();
	//body->SetTransform( body->GetPosition(), angle+1 );
	B2DLayer::update(dt);
}


float B2dPlay::drawHill(int pixelStep,float xOffset,float yOffset,float width,float height,b2World* world) {
	float worldScale = 50;	
	float hillStartY=yOffset;
	float hillWidth=120+width;
	int numberOfSlices=hillWidth/pixelStep;
	b2Vec2 hillVector;
	float  randomHeight = height;
	hillStartY-=randomHeight;
	for (int j =0; j<numberOfSlices/2; j++) {
		b2Vec2 hillVector [4];
		float p =j*pixelStep+xOffset;
		hillVector[0].Set((j*pixelStep+xOffset)/worldScale,480/worldScale);
		hillVector[1].Set((j*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*std::cos(2*PI/numberOfSlices*j)/worldScale));
		hillVector[2].Set(((j+1)*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*std::cos(2*PI/numberOfSlices*(j+1))/worldScale));
		hillVector[3].Set(((j+1)*pixelStep+xOffset)/worldScale,480/worldScale);
		b2BodyDef sliceBody ;
		b2Vec2 centre = findCentroid(hillVector,4);
		sliceBody.position.Set(0,0);//centre.x,centre.y);
		b2PolygonShape slicePoly  ;
		slicePoly.Set(hillVector,4);
		b2FixtureDef sliceFixture;
		sliceFixture.shape=&slicePoly;
		b2Body* worldSlice=world->CreateBody(&sliceBody);
		worldSlice->CreateFixture(&sliceFixture);
	}
	for (int j=numberOfSlices/2; j<numberOfSlices; j++) {
		b2Vec2 hillVector [4];
		hillVector[0].Set((j*pixelStep+xOffset)/worldScale,480/worldScale);
		hillVector[1].Set((j*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*std::cos(2*PI/numberOfSlices*j)/worldScale));
		hillVector[2].Set(((j+1)*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*std::cos(2*PI/numberOfSlices*(j+1))/worldScale));
		hillVector[3].Set(((j+1)*pixelStep+xOffset)/worldScale,480/worldScale);
		b2BodyDef sliceBody ;
		b2Vec2 centre = findCentroid(hillVector,4);
		sliceBody.position.Set(centre.x,centre.y);
		b2PolygonShape slicePoly  ;
		slicePoly.Set(hillVector,4);
		b2FixtureDef sliceFixture;
		sliceFixture.shape=&slicePoly;
		b2Body* worldSlice=world->CreateBody(&sliceBody);
		worldSlice->CreateFixture(&sliceFixture);
	}
	hillStartY=hillStartY+randomHeight;
	return (hillStartY);
}

b2Vec2 B2dPlay::findCentroid(b2Vec2 vs[], int count) {
	b2Vec2 c= b2Vec2::b2Vec2();
	float area=0.0;
	float p1X=0.0;
	float p1Y=0.0;
	float inv3=1.0f/3.0f;
	for (int i = 0; i < count; ++i) {
		b2Vec2 p2=vs[i];
		b2Vec2 p3=i+1<count?vs[int(i+1)]:vs[0];
		float e1X=p2.x-p1X;
		float e1Y=p2.y-p1Y;
		float e2X=p3.x-p1X;
		float e2Y=p3.y-p1Y;
		float D = (e1X * e2Y - e1Y * e2X);
		float triangleArea=0.5*D;
		area+=triangleArea;
		c.x += triangleArea * inv3 * (p1X + p2.x + p3.x);
		c.y += triangleArea * inv3 * (p1Y + p2.y + p3.y);
	}
	c.x*=1.0/area;
	c.y*=1.0/area;
	return c;
}