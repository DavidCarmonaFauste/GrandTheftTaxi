#include "Bridge.h"
#include "Vehicle.h"


Bridge::Bridge (int w, int h, int x, int y) : Trigger(w, h, x, y){
}


Bridge::~Bridge () {
}

void Bridge::beginCallback (b2Contact * contact) {
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
			&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		contact->SetEnabled (true);
		Game::getInstance ()->getGameStateMachine ()->fromMainStateToLevel2 ();
	}
}

void Bridge::endCallback (b2Contact * contact) {
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
			&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		contact->SetEnabled (false);
	}
}
