/*
 * AtomeMontee.cpp
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */


#include "DeuxiemeRecalage.h"
#include "AtomeMontee.h"
#include "TiretteState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

AtomeMontee atomeMontee = AtomeMontee();

float traj_montee_purple[][2] = { {600,1200},
								{150,1200},
								{150,1800},
								{1100,1800},
								{500,1800},
								{1063,1800}
};

float turn_montee_purple[] = {180,90,0};



/*float traj_montee_yellow[][2] = { {150,1200},
								{500,1200},
								{500,300}
};*/


AtomeMontee::AtomeMontee() {
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

AtomeMontee::~AtomeMontee() {
	// TODO Auto-generated destructor stub
}

void AtomeMontee::enter() {

	//Serial.println("Etat premiere recalage");

	if(tiretteState.get_color() == PURPLE){
		navigator.move_to(traj_montee_purple[0][0],traj_montee_purple[0][1]);
	}
	else{
		navigator.move_to(traj_montee_yellow[0][0],traj_montee_yellow[0][1]);
	}
}

void AtomeMontee::leave() {

}

void AtomeMontee::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(trajectory_index == 4){
			if(tiretteState.get_color() == PURPLE){
				Odometry::set_pos(1063,1800,0);
				navigator.move_to(traj_recolte2_purple[4][0],traj_recolte2_purple[4][1])
				mandibuleGauche.write(MANDIBULE_GAUCHE_BAS);
				mandibuleDroite.write(MANDIBULE_GAUCHE_BAS);
				navigator.move_to(traj_recolte2_purple[5][0],traj_recolte2_purple[5][1])
			}
			else{
				Odometry::set_pos(1063,1800,0);// TODO mesurer les valeurs du cote jaune
				navigator.move_to(traj_recolte2_purple[4][0],traj_recolte2_purple[4][1])
				mandibuleGauche.write(MANDIBULE_GAUCHE_BAS);
				mandibuleDroite.write(MANDIBULE_GAUCHE_BAS);
				navigator.move_to(traj_recolte2_purple[5][0],traj_recolte2_purple[5][1])
			}

			fsmSupervisor.setNextState(&DeadState);
		}
		else{
			if(tiretteState.get_color() == PURPLE){
				navigator.turn_to(turn_montee_purple[trajectory_index]);
				trajectory_index += 1;
				navigator.move_to(traj_recolte2_purple[trajectory_index][0],traj_recolte2_purple[trajectory_index][1]);
			}
			else{
				navigator.turn_to(90); //TODO verifier angle jaune
				trajectory_index += 1;
				navigator.move_to(traj_recolte2_yellow[trajectory_index][0],traj_recolte2_yellow[trajectory_index][1]);
			}
		}
	}
}

void AtomeMontee::reEnter(unsigned long interruptTime){
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

void AtomeMontee::forceLeave(){

}

