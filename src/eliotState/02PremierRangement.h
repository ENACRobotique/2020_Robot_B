/*
 * PremierRangement.h
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_PREMIERRANGEMENT_H_
#define STATEMACHINE_PREMIERRANGEMENT_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class PremierRangement : public AbstractState {
public:
	PremierRangement();
	virtual ~PremierRangement();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	void forceLeave();
	unsigned long get_time_start(){
		return time_start;
	}

private:
	unsigned long time_start;
	USDistances usDistances;
};

extern PremierRangement premierRangement;


#endif /* STATEMACHINE_PREMIERRANGEMENT_H_ */
