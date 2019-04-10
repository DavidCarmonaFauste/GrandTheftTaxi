#include "Shop.h"
#include "Vehicle.h"

Shop::Shop(int w, int h, int x, int y) : Trigger(w, h, x, y) {

}

Shop::~Shop() {

}

void Shop::beginCallback(b2Contact * contact) {
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::GetInstance()->GetPhyO()->getBody();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
		&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		Game::getInstance()->setState(NAME_SHOP_STATE);
	}
}

void Shop::endCallback(b2Contact * contact){
	
}
