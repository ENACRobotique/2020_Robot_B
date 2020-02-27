/*
 * PremierRecalage.h
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_PREMIERRECALAGE_H_
#define STATEMACHINE_PREMIERRECALAGE_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class PremierRecalage : public AbstractState {
public:
	PremierRecalage();
	virtual ~PremierRecalage();

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

extern PremierRecalage premierRecalage;


#endif /* STATEMACHINE_PREMIERRECALAGE_H_ */
