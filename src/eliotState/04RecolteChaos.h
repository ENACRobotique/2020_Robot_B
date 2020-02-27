/*
 * RecolteChaos.h
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_RECOLTECHAOS_H_
#define STATEMACHINE_RECOLTECHAOS_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class RecolteChaos : public AbstractState {
public:
	RecolteChaos();
	virtual ~RecolteChaos();

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

extern RecolteChaos recolteChaos;


#endif /* STATEMACHINE_RECOLTECHAOS_H_ */
