/*
 * deuxiemeRecalage.h
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_DEUXIEMERECALAGE_H_
#define STATEMACHINE_DEUXIEMERECALAGE_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class DeuxiemeRecalage : public AbstractState {
public:
	DeuxiemeRecalage();
	virtual ~DeuxiemeRecalage();

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

extern DeuxiemeRecalage deuxiemeRecalage;


#endif /* STATEMACHINE_DEUXIEMERECALAGE_H_ */
