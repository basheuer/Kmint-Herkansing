#include "Edge.h"
#include "Node.h"

Edge::Edge(double startX, double startY, double endX, double endY)
{
	 startXPosition = startX;
	 startYPosition = startY;

	 endXPosition = endX;
	 endYPosition = endY;
	 mWeight = 1000;
}

int Edge::GetWeight()
{
	return mWeight;
}

void Edge::SetLeftConnectedNode(Node* node)
{
	mLeftConnectedNode = node;
}

void Edge::SetRightConnectedNode(Node* neighbourNode)
{
	mRightConnectedNode = neighbourNode;

}

Node* Edge::GetLeftConnectedNode()
{
	return mLeftConnectedNode;
}

Node* Edge::GetRightConnectedNode()
{
	return mRightConnectedNode;
}

Node* Edge::getOtherNode(Node* node)
{
	if (mLeftConnectedNode == node)
	{
		return mRightConnectedNode;
	}
	else if (mRightConnectedNode == node)
	{
		return mLeftConnectedNode;
	}
	else 
	{
		return nullptr;
	}
}

void Edge::Draw()
{
	
	FWApplication::GetInstance()->DrawLine((int)startXPosition, (int)startYPosition, (int)endXPosition, (int)endYPosition);
}

void Edge::Update(float deltaTime)
{
	
}

void Edge::OnCollision(IGameObject * collidedObject)
{
	
}

Edge::~Edge()
{

}