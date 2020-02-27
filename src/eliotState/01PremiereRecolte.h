/*
 * PremiereRecolte.h
 *
 *  Created on: 23 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_PREMIERERECOLTE_H_
#define STATEMACHINE_PREMIERERECOLTE_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class PremiereRecolte : public AbstractState {
public:
	PremiereRecolte();
	virtual ~PremiereRecolte();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	void forceLeave();
	unsigned long get_time_start(){
		return time_start;
	}

private:
	int trajectory_index = 0;
	unsigned long time_start;
	USDistances usDistances;
};

extern PremiereRecolte premiereRecolte;


#endif /* STATEMACHINE_PREMIERERECOLTE_H_ */
