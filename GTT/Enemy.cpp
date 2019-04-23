#include "Enemy.h"
#include "Reticule.h"


Enemy::Enemy(VehicleInfo r){
	this->setWidth(r.width);
	this->setHeight(r.height);

	bodyReadyToDestroy_ = false;

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(ENEMY_HP);
	addLogicComponent(health_);

	//Movement
	speed_ = 5;

	// Physics
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	phyO_->getBody()->SetUserData(this);
	//phyO_->getBody()->SetLinearDamping(2.0f);
	//phyO_->getBody()->SetAngularDamping(2.0f);
	addLogicComponent(phyO_);

	//IA
	Node* a = new Node(Vector2D(0, 0), "a");
	Node* b = new Node(Vector2D(400, 0), "b");
	Node* c = new Node(Vector2D(400, 400), "c");
	Node* d = new Node(Vector2D(0, 400), "d");
	Node* e = new Node(Vector2D(800, 0), "e");
	Node* f = new Node(Vector2D(-400, 0), "f");
	Node* g = new Node(Vector2D(-400, 400), "g");
	Node* h = new Node(Vector2D(800, 400), "h");
	Node* i = new Node(Vector2D(0, -400), "i");
	Node* j = new Node(Vector2D(400, -400), "j");

	vector<Node*>* route= new vector<Node*>;

	route->push_back(a);
	route->push_back(b);
	route->push_back(c);

	routemap_.addNode(a);
	routemap_.addNode(b);
	routemap_.addNode(c);
	routemap_.addNode(d);
	routemap_.addNode(e);
	routemap_.addNode(f);
	routemap_.addNode(g);
	routemap_.addNode(h);
	routemap_.addNode(i);
	routemap_.addNode(j);

	routemap_.connectNodes(a, b);
	routemap_.connectNodes(b, c);
	routemap_.connectNodes(c, d);
	routemap_.connectNodes(d, a);
	routemap_.connectNodes(f, a);
	routemap_.connectNodes(b, e);
	routemap_.connectNodes(a, i);
	routemap_.connectNodes(b, j);
	routemap_.connectNodes(i, j);
	routemap_.connectNodes(h, e);
	routemap_.connectNodes(h, c);
	routemap_.connectNodes(f, g);
	routemap_.connectNodes(d, g);

	patrolBehaviour_ = new IApatrol(GetPhyO(), &routemap_, speed_);
	//addLogicComponent(patrolBehaviour_);
	
}

void Enemy::Damage(double damage)
{
	health_->damage(damage);
	if (health_->getHealth() <= 0) Die();
}

void Enemy::Die()
{
	bodyReadyToDestroy_ = true;
}

void Enemy::update(Uint32 deltaTime)
{
	if (active_) {
		/*
		if (!paused_) {
			if (destinated_) {
				if (direction_.x < 0) {
					if (getCenter().x < destination_.x) {
						phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
						destinated_ = false;
						return;
					}
				}
				else if (direction_.x > 0) {
					if (getCenter().x > destination_.x) {
						phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
						destinated_ = false;
						return;
					}
				}
				else if (direction_.y < 0) {
					if (getCenter().y < destination_.y) {
						phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
						destinated_ = false;
						return;
					}
				}
				else if (direction_.y > 0) {
					if (getCenter().y > destination_.y) {
						phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
						destinated_ = false;
						return;
					}
				}
				direction_ = Vector2D(destination_.x - getCenter().x, destination_.y - getCenter().y);
				direction_.Normalize();
				float angle = atan2f(-direction_.x, direction_.y);
				angle += 90.0 / 180.0*M_PI;
				phyO_->getBody()->SetTransform(phyO_->getBody()->GetPosition(), angle);
				phyO_->getBody()->SetLinearVelocity(Vector2D(direction_.x * speed_, direction_.y * speed_));
			}
			else {
				destinated_ = true;
				if (node == nullptr) {
					node = routemap_.getNodes()[0];
					destination_ = node->position_;
				}
				else {
					if (node->isConnected()) {
						double a = rand() % 100;
						int c = a * 4 / 100.0;
						while (node->connections_[c] == nullptr) {
							a = rand() % 100;
							c = a * 4 / 100.0;
						}
						node = node->connections_[c];
						destination_ = node->position_;
					}
					else paused_ = true;
				}
				direction_ = Vector2D(destination_.x - getCenter().x, destination_.y - getCenter().y);
				direction_.Normalize();
			}
		}
		else phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
		*/
		if (bodyReadyToDestroy_) {
			delLogicComponent(phyO_);
			delete phyO_;
			phyO_ = nullptr;
			setActive(false);
		}
		Car::update(deltaTime);
	}
}

void Enemy::handleInput(Uint32 deltaTime, const SDL_Event & event)
{
	if (active_) {
		Car::handleInput(deltaTime, event);
	}
}


Enemy::~Enemy()
{
}
