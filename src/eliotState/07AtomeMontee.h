/*
 * AtomeMontee.h
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_ATOMEMONTEE_H_
#define STATEMACHINE_ATOMEMONTEE_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class AtomeMontee : public AbstractState {
public:
	AtomeMontee();
	virtual ~AtomeMontee();

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

extern AtomeMontee atomeMontee;


#endif /* STATEMACHINE_ATOMEMONTEE_H_ */
