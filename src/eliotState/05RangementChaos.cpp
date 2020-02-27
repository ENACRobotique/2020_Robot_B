/*
 * RangementChaos.cpp
 *
 *  Created on: 24 mai 2019
 *      Author: robot
 */


#include "RecolteChaos.h"
#include "RangementChaos.h"
#include "TiretteState.h"
#include "DeuxiemeRecalage.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

RangementChaos rangementChaos = RangementChaos();

float traj_rangement2_purple[][2] = { {500,550},
								{220,550},
};

/*float traj_rangement2_yellow[][2] = { {150,1200},
								{500,1200},
								{500,300}
};*/

RangementChaos::RangementChaos() {
	time_start = 0;
	flags = E_ULTRASOUND;
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
	angles.angleA = 80;
	angles.angleB = 100;
}

RangementChaos::~RangementChaos() {
	// TODO Auto-generated destructor stub
}

void RangementChaos::enter() {

	//Serial.println("Etat premiere recolte");

	if(tiretteState.get_color() == PURPLE){
		navigator.move_to(traj_rangement2_purple[0][0],traj_rangement2_purple[0][1]);
		navigator.turn_to(180);
		navigator.move_to(traj_rangement2_purple[1][0],traj_rangement2_purple[1][1]);
		mandibuleGauche.write(MANDIBULE_GAUCHE_HAUT);
		mandibuleDroite.write(MANDIBULE_DROITE_HAUT);
	}
	else{
		navigator.move_to(traj_rangement2_yellow[0][0],traj_rangement2_yellow[0][1]);
		navigator.turn_to(-180); //TODO voir les bonnes valeurs pour le cotes jaunes
		navigator.move_to(traj_rangement2_yellow[1][0],traj_rangement2_yellow[1][1]);
		mandibuleGauche.write(MANDIBULE_GAUCHE_HAUT);
		mandibuleDroite.write(MANDIBULE_DROITE_HAUT);
	}
}

void RangementChaos::leave() {

}

void RangementChaos::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&deuxiemeRecalage);
	}
}

void RangementChaos::reEnter(unsigned long interruptTime){
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

void RangementChaos::forceLeave(){

}

