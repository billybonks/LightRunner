#include "B2dPlay.h" 

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
	 end.Set(9,1);
	 DrawHill(start,end,1,10,2,5);
	  //GenSquare(2,1,B2DLayer::world);
	B2DLayer::Debug(true);
	return true;
 }  

void B2dPlay::DrawHill(b2Vec2 start,b2Vec2 end,int stepWidth,int width, int innerHeight,int peak){
	int steps = width/stepWidth;
	float inclinePerStep = peak/(steps/2);
	b2Vec2 vertices[4];
	b2Vec2  startPos = start;
	for(int i = 1;i<= steps;i++){
		if(i>steps/2){
			GetVertsInclineSquare(vertices,stepWidth,innerHeight,inclinePerStep,-1);
			GenSquare(vertices,world,startPos);
			startPos.x += vertices[1].x+(vertices[1].x/2);
			startPos.y += vertices[1].y-((vertices[1].y+inclinePerStep)/2);
		}else{
			GetVertsInclineSquare(vertices,stepWidth,innerHeight,inclinePerStep,+1);
			GenSquare(vertices,world,startPos);
			startPos.x += vertices[2].x+(vertices[2].x/2);
			startPos.y += vertices[2].y-((vertices[2].y+inclinePerStep)/2);
		}
	}
}



void B2dPlay::GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline,int slopeType){
	vertices[0].Set(-width/2, -height/2);
	vertices[1].Set(width/2, (-height/2)+(slopeType*(incline/2)));
	vertices[2].Set(width/2, (height/2)+(slopeType*(incline/2)));
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

 b2FixtureDef* B2dPlay::GenSquare(float width, float height,b2World* world)
 {
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(5.0f, 8.0f);
	body =B2DLayer::world->CreateBody(&bodyDef);
	int32 count = 4;
	b2PolygonShape polygon;
	b2Vec2 verts[4];
	GetVerts(verts,1,4);
	polygon.Set(verts, count);
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
	body->SetTransform( body->GetPosition(),newAngle * DEGTORAD);
	return NULL;
 }

 void B2dPlay::menuCloseCallback(CCObject* pSender){
 }
	
 void B2dPlay::ccTouchesBegan(CCSet* touches, cocos2d::CCEvent* event){
 }

void B2dPlay::update(float dt){
	float angle = body->GetAngle();
	//body->SetTransform( body->GetPosition(), angle+1 );
	B2DLayer::update(dt);
}


	//float B2dPlay::drawHill(int pixelStep,float xOffset,float yOffset,float width,float height,b2World* world) {
	//		float hillStartY=yOffset;
	//		float hillWidth=120+width;
	//		_realWidth += hillWidth;
	//		int numberOfSlices=hillWidth/pixelStep;
	//		b2Vec2 hillVector;
	//		float  randomHeight = height;
	//		_realHeight+=randomHeight;
	//		hillStartY-=randomHeight;
	//		for (int j =0; j<numberOfSlices/2; j++) {
	//			b2Vec2 hillVector [4];
	//			hillVector[0].Set((j*pixelStep+xOffset)/worldScale,480/worldScale));
	//			hillVector[0].Set((j*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*Math.cos(2*Math.PI/numberOfSlices*j))/worldScale));
	//			hillVector[0].Set(((j+1)*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*Math.cos(2*Math.PI/numberOfSlices*(j+1)))/worldScale));
	//			hillVector[0].Set(((j+1)*pixelStep+xOffset)/worldScale,480/worldScale));
	//			b2BodyDef* sliceBody ;
	//			b2Vec2 centre = findCentroid(hillVector,4);
	//			sliceBody->position.Set(centre.x,centre.y);
	//			for (int z=0; z<4; z++) {
	//				hillVector[z].Subtract(centre);
	//			}
	//			b2PolygonShape* slicePoly  ;
	//			slicePoly->Set(hillVector,4);
	//			b2FixtureDef* sliceFixture;
	//			sliceFixture->shape=slicePoly;
	//			b2Body* worldSlice=world->CreateBody(sliceBody);
	//			worldSlice->CreateFixture(sliceFixture);
	//		}
	//		for (j=numberOfSlices/2; j<numberOfSlices; j++) {
	//			hillVector=new Vector.<b2Vec2>();
	//			hillVector.push(new b2Vec2((j*pixelStep+xOffset)/worldScale,480/worldScale));
	//			hillVector.push(new b2Vec2((j*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*Math.cos(2*Math.PI/numberOfSlices*j))/worldScale));
	//			hillVector.push(new b2Vec2(((j+1)*pixelStep+xOffset)/worldScale,(hillStartY+randomHeight*Math.cos(2*Math.PI/numberOfSlices*(j+1)))/worldScale));
	//			hillVector.push(new b2Vec2(((j+1)*pixelStep+xOffset)/worldScale,480/worldScale));
	//			sliceBody=new b2BodyDef  ;
	//			centre=findCentroid(hillVector,hillVector.length);
	//			sliceBody.position.Set(centre.x,centre.y);
	//			for (z=0; z<hillVector.length; z++) {
	//				hillVector[z].Subtract(centre);
	//			}
	//			slicePoly=new b2PolygonShape  ;
	//			slicePoly.SetAsVector(hillVector,4);
	//			sliceFixture=new b2FixtureDef  ;
	//			sliceFixture.shape=slicePoly;
	//			worldSlice=world.CreateBody(sliceBody);
	//			worldSlice.CreateFixture(sliceFixture);
	//		}
	//		hillStartY=hillStartY+randomHeight;
	//		return (hillStartY);
	//	}

	//	 findCentroid(vs:Vector.<b2Vec2>, count:uint):b2Vec2 {
	//		var c:b2Vec2 = new b2Vec2();
	//		var area:Number=0.0;
	//		var p1X:Number=0.0;
	//		var p1Y:Number=0.0;
	//		var inv3:Number=1.0/3.0;
	//		for (var i:int = 0; i < count; ++i) {
	//			var p2:b2Vec2=vs[i];
	//			var p3:b2Vec2=i+1<count?vs[int(i+1)]:vs[0];
	//			var e1X:Number=p2.x-p1X;
	//			var e1Y:Number=p2.y-p1Y;
	//			var e2X:Number=p3.x-p1X;
	//			var e2Y:Number=p3.y-p1Y;
	//			var D:Number = (e1X * e2Y - e1Y * e2X);
	//			var triangleArea:Number=0.5*D;
	//			area+=triangleArea;
	//			c.x += triangleArea * inv3 * (p1X + p2.x + p3.x);
	//			c.y += triangleArea * inv3 * (p1Y + p2.y + p3.y);
	//		}
	//		c.x*=1.0/area;
	//		c.y*=1.0/area;
	//		return c;
	//	}