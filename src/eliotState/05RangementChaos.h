/*
 * RangementChaos.h
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */

#ifndef STATEMACHINE_RANGEMENTCHAOS_H_
#define STATEMACHINE_RANGEMENTCHAOS_H_


#include "AbstractState.h"
#include "../lib/USManager.h"


class RangementChaos : public AbstractState {
public:
	RangementChaos();
	virtual ~RangementChaos();

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

extern RangementChaos rangementChaos;


#endif /* STATEMACHINE_RANGEMENTCHAOS_H_ */
