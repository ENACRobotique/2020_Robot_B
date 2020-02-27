/*
 * PremiereRecolte.cpp
 *
 *  Created on: 23 mai 2019
 *      Author: robot
 */


#include "PremiereRecolte.h"
#include "TiretteState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

PremiereRecolte premiereRecolte = PremiereRecolte();

float traj_recolte1_purple[][2] = { {150,1200},
								{500,1200},
								{500,300}
};

float turn_recolte1_purple[] = {0,-90};

/*float traj_recolte1_yellow[][2] = { {150,1200},
								{500,1200},
								{500,300}
};

float turn_recolte1_yellow[] = {0,-90} */

PremiereRecolte::PremiereRecolte() {
	time_start = 0;
	trajectory_index = 0;
	flags = E_ULTRASOUND;
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
	angles.angleA = 80;
	angles.angleB = 100;
}

PremiereRecolte::~PremiereRecolte() {
	// TODO Auto-generated destructor stub
}

void PremiereRecolte::enter() {

	//Serial.println("Etat premiere recolte");

	if(tiretteState.get_color() == PURPLE){
		navigator.move_to(traj_recolte1_purple[0][0],traj_recolte1_purple[0][1]);
	}
	else{
		navigator.move_to(traj_recolte1_yellow[0][0],traj_recolte1_yellow[0][1]);
	}

}

void PremiereRecolte::leave() {

}

void PremiereRecolte::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(trajectory_index == 3){
			mandibuleGauche.write(MANDIBULE_GAUCHE_BAS);
			mandibuleDroite.write(MANDIBULE_GAUCHE_BAS);
			fsmSupervisor.setNextState(&premierRangement);
		}
		else{
			if(tiretteState.get_color() == PURPLE){
				navigator.turn_to(turn_recolte1_purple[trajectory_index]);
				trajectory_index += 1;
				navigator.move_to(traj_recolte1_purple[trajectory_index][0],traj_recolte1_purple[trajectory_index][1]);
			}
			else{
				navigator.turn_to(turn_recolte1_yellow[trajectory_index]);
				trajectory_index += 1;
				navigator.move_to(traj_recolte1_yellow[trajectory_index][0],traj_recolte1_yellow[trajectory_index][1]);
			}
		}
	}
}

void PremiereRecolte::reEnter(unsigned long interruptTime){
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

void PremiereRecolte::forceLeave(){

}

