/*
 * deuxiemeRecalage.cpp
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */



#include "RangementChaos.h"
#include "DeuxiemeRecalage.h"
#include "TiretteState.h"
#include "AtomeMontee.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "odometry.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

DeuxiemeRecalage deuxiemeRecalage = DeuxiemeRecalage();

float traj_recalage2_purple[][2] = { {600,400},
								{600,1400}
};


/*float traj_recalage1_yellow[][2] = { {150,1200},
								{500,1200},
								{500,300}
};

float turn_recalage1_purple[] = {-180, 90}
*/

DeuxiemeRecalage::DeuxiemeRecalage() {
	trajectory_index = 0;
	time_start = 0;
	flags = E_ULTRASOUND;
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
	angles.angleA = 80;
	angles.angleB = 100;
}

DeuxiemeRecalage::~DeuxiemeRecalage() {
	// TODO Auto-generated destructor stub
}

void DeuxiemeRecalage::enter() {

	//Serial.println("Etat premiere recalage");

	if(tiretteState.get_color() == PURPLE){
		navigator.move_to(traj_recalage2_purple[0][0],traj_recalage2_purple[0][1]);
	}
	else{
		navigator.move_to(traj_recalage2_yellow[0][0],traj_recalage2_yellow[0][1]);
	}
}

void DeuxiemeRecalage::leave() {

}

void DeuxiemeRecalage::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(trajectory_index == 3){
			if(tiretteState.get_color() == PURPLE){
				Odometry::set_pos(600,1378,0);
			}
			else{
				Odometry::set_pos(25,780,0); //TODO regarder les mesure du cote jaune
			}
			fsmSupervisor.setNextState(&atomeMontee);
		}
		else{
			if(tiretteState.get_color() == PURPLE){
				navigator.turn_to(90);
				trajectory_index += 1;
				navigator.move_to(traj_recalage2_purple[trajectory_index][0],traj_recalage2_purple[trajectory_index][1]);
			}
			else{
				navigator.turn_to(90);
				trajectory_index += 1;
				navigator.move_to(traj_recalage2_yellow[trajectory_index][0],traj_recalage2_yellow[trajectory_index][1]);
			}
		}
	}
}

void DeuxiemeRecalage::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	/*if(digitalRead(COLOR) == GREEN){
		navigator.move_to(POS_X_WATER,POS_Y_WATER_GREEN);
	}
	else{
		navigator.move_to(POS_X_WATER,POS_Y_WATER_ORANGE);
	}*/
	Serial.println("reenter");
	if(digitalRead(COLOR) == GREEN){
		navigator.move_to(1500,-10000);
	}
	else{
		navigator.move_to(1500,-10000);
	}
}

void DeuxiemeRecalage::forceLeave(){

}

