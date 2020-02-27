/*
 * RecolteChaos.cpp
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */


#include "PremierRecalage.h"
#include "RecolteChaos.h"
#include "TiretteState.h"
#include "RangementChaos.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

RecolteChaos recolteChaos = RecolteChaos();

float traj_recolte2_purple[][2] = { {1000,780},
								{1000,1200},
};

/*float traj_recolte2_yellow[][2] = { {150,1200},
								{500,1200},
								{500,300}
};*/


RecolteChaos::RecolteChaos() {
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

RecolteChaos::~RecolteChaos() {
	// TODO Auto-generated destructor stub
}

void RecolteChaos::enter() {

	//Serial.println("Etat premiere recalage");

	if(tiretteState.get_color() == PURPLE){
		navigator.move_to(traj_recolte2_purple[0][0],traj_recolte2_purple[0][1]);
	}
	else{
		navigator.move_to(traj_recolte2_yellow[0][0],traj_recolte2_yellow[0][1]);
	}
}

void RecolteChaos::leave() {

}

void RecolteChaos::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(trajectory_index == 2){
			mandibuleGauche.write(MANDIBULE_GAUCHE_BAS);
			mandibuleDroite.write(MANDIBULE_GAUCHE_BAS);
			fsmSupervisor.setNextState(&rangementChaos);
		}
		else{
			if(tiretteState.get_color() == PURPLE){
				navigator.turn_to(90);
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

void RecolteChaos::reEnter(unsigned long interruptTime){
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

void RecolteChaos::forceLeave(){

}


