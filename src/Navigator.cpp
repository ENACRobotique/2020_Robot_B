/*
 * Trajectory.cpp
 *
 * Created on : 8 avril 2018
 * Author : Maxime
 */

#include "Navigator.h"

#include "Secondary2019Code.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "math.h"

Navigator navigator = Navigator();

Navigator::Navigator(){
	turn_done = false;
	displacement_done = false;
	trajectory_done = false;
	x_target = 0;
	y_target = 0;
	theta_target = 0;
	move_type = TURN;
	move_state = STOPPED;
}

void Navigator::move_to(float x, float y){
	x_target = x;
	y_target = y;
	move_type = DISPLACEMENT;
	move_state = INITIAL_TURN;
	trajectory_done = false;
	Serial.print("moving_to : ");
	Serial.print(x_target);
	Serial.print("\t");
	Serial.println(y_target);
}

void Navigator::turn_to(float theta){ // En degrés
	theta_target = center_radian(PI*theta/180);

	/*Serial.print("Angle: ");
	Serial.println(Odometry::get_pos_theta());
	Serial.print("moving_to : ");
	Serial.print(theta_target);
	Serial.print(" ( <  ");
	Serial.println(theta);*/

	move_type = TURN;
	move_state = INITIAL_TURN;
	trajectory_done = false;
}

void Navigator::throw_to(float x, float y, float theta){
	x_target = x;
	y_target = y;
	theta_target = theta;
	move_type = THROW;
	move_state = CRUISE;
	trajectory_done = false;
	/*Serial.print("throwing_to : ");
	Serial.print(x_target);
	Serial.print("\t");
	Serial.println(y_target);*/
}

float Navigator::compute_cons_speed()
{
	float speed_cons, dist_fore, t_stop, dist_objective;
	int sgn,MAX_ACCEL;

	if(move_type == THROW){
		MAX_ACCEL = ACCEL_MAX_THROW;
	}
	else{
		MAX_ACCEL = ACCEL_MAX;
	}
	sgn = scalaire(cos(Odometry::get_pos_theta()),sin(Odometry::get_pos_theta()),x_target - Odometry::get_pos_x(),y_target - Odometry::get_pos_y());

	/*Serial.print("Sens d'avancée:");
	Serial.print("\t");
	Serial.println(sgn);*/

	//Test de décélération (on suppose l'accélération minimale et on intègre deux fois)
	t_stop = Odometry::get_speed()/MAX_ACCEL;
	dist_fore = (Odometry::get_speed()*t_stop-1/2*MAX_ACCEL*pow(t_stop,2));
	/*dist_fore = Odometry::get_speed()*t_stop;*/

	dist_objective = sqrt(pow(x_target - Odometry::get_pos_x(),2) + pow(y_target - Odometry::get_pos_y(),2));

	//Si le point estimé est suffisamment proche du point voulu, on décélére, sinon on accélére jusqu'à la vitesse maximale.
	if(abs( dist_fore - dist_objective ) < ADMITTED_POSITION_ERROR){
		speed_cons = sgn*max(0,-MAX_ACCEL*NAVIGATOR_TIME_PERIOD + abs(Odometry::get_speed()));
	}
	else{
		if(dist_fore - dist_objective > 0){
			speed_cons = sgn*max(0,abs(Odometry::get_speed()) - MAX_ACCEL*NAVIGATOR_TIME_PERIOD);
		}
		else{
			speed_cons = sgn*min(SPEED_MAX,abs(Odometry::get_speed()) + MAX_ACCEL*NAVIGATOR_TIME_PERIOD);
		}
	}
/*	Serial.print("Distances estimées");
	Serial.print("\t");
	Serial.print(dist_fore - dist_objective);
	Serial.print("\t");
	Serial.print(dist_objective);
	Serial.print("\tspeed= ");
	Serial.println(Odometry::get_speed());*/
	return speed_cons;
}


float Navigator::compute_cons_omega()
{
	float omega_cons, angle_fore, alpha, t_rotation_stop;
	int sgn;

	if(move_type == DISPLACEMENT){
		alpha = Odometry::get_pos_theta() + center_axes(atan2((-y_target+Odometry::get_pos_y()),(-x_target+Odometry::get_pos_x())) - Odometry::get_pos_theta());
	}
	else{
		alpha = theta_target;
	}

	if (center_radian(alpha - Odometry::get_pos_theta()) > 0){
		sgn = 1;
	}
	else{
		sgn = -1;
	}
	t_rotation_stop = abs(Odometry::get_omega())/ACCEL_OMEGA_MAX;
	angle_fore = center_radian(Odometry::get_pos_theta() + sgn*(abs(Odometry::get_omega())*t_rotation_stop -1/2*ACCEL_OMEGA_MAX*pow(t_rotation_stop,2)));
	if(abs(center_radian(angle_fore - alpha)) < ADMITTED_ANGLE_ERROR){
		omega_cons = sgn*max(0,abs(Odometry::get_omega()) - NAVIGATOR_TIME_PERIOD*ACCEL_OMEGA_MAX);
	}
	else{
		if(sgn*(center_radian(alpha - angle_fore)) > 0){
			omega_cons = sgn*min(OMEGA_MAX, NAVIGATOR_TIME_PERIOD*ACCEL_OMEGA_MAX + abs(Odometry::get_omega()));
		}
		else{
			omega_cons = sgn*max(0,abs(Odometry::get_omega()) - NAVIGATOR_TIME_PERIOD*ACCEL_OMEGA_MAX);
		}
	}
	/*Serial.print("Consigne angle:");
	Serial.print(omega_cons);
	Serial.print("\t");
	Serial.print("Alpha:");
	Serial.print(alpha);
	Serial.print("\t");
	Serial.print("angle_fore:");
	Serial.println(angle_fore);*/

	return omega_cons;
}

void Navigator::update(){
	float omega_cons,speed_cons,alpha,distance;

	if(move_type == BRAKE){
		int sgn = scalaire(cos(Odometry::get_pos_theta()),sin(Odometry::get_pos_theta()),x_target - Odometry::get_pos_x(),y_target - Odometry::get_pos_y());
		speed_cons = sgn*max(0,abs(Odometry::get_speed()) - EMERGENCY_BRAKE*NAVIGATOR_TIME_PERIOD);
		if(abs(Odometry::get_speed()) < ADMITTED_SPEED_ERROR){
			move_state = STOPPED;
			speed_cons = 0;
		}
		MotorControl::set_cons(speed_cons,0);
	}
	else{
		switch(move_state){
		case INITIAL_TURN:
			if(move_type==DISPLACEMENT){
				alpha = Odometry::get_pos_theta() + center_axes(atan2((-y_target+Odometry::get_pos_y()),(-x_target+Odometry::get_pos_x())) - Odometry::get_pos_theta());
			}
			else{
				alpha = theta_target;
			}
			turn_done = ((abs(center_radian(Odometry::get_pos_theta() - alpha)) < ADMITTED_ANGLE_ERROR)&&(Odometry::get_omega() < ADMITTED_OMEGA_ERROR));

			if(turn_done){

				MotorControl::set_cons(0,0);
				switch(move_type){
				case TURN:
					move_state = STOPPED;
					trajectory_done = true;
					break;
				case DISPLACEMENT:
					move_state = CRUISE;
					break;
				case THROW:
					//Do nothing
					break;
				case BRAKE:
					//Do nothing
					break;
				}
				break;
			}

			omega_cons = compute_cons_omega();
			MotorControl::set_cons(0,omega_cons);

			MotorControl::set_cons(0,omega_cons);

			break;
		case CRUISE:
			distance = sqrt(pow(x_target - Odometry::get_pos_x(),2) + pow(y_target - Odometry::get_pos_y(),2));
			displacement_done = ((distance<ADMITTED_POSITION_ERROR)&&(Odometry::get_speed() < ADMITTED_SPEED_ERROR));
			if(displacement_done){
				MotorControl::set_cons(0,0);
				move_state=STOPPED;
				trajectory_done = true;
				break;
			}
			speed_cons=compute_cons_speed();
			omega_cons = compute_cons_omega();
			MotorControl::set_cons(speed_cons,omega_cons);
			break;
		case STOPPED:
			//do nothing
			break;
		}
	}
}

void Navigator::forceStop(){
	move_type = BRAKE;
}

bool Navigator::moveForward(){
	int dir = scalaire(cos(Odometry::get_pos_theta()),sin(Odometry::get_pos_theta()),x_target - Odometry::get_pos_x(),y_target - Odometry::get_pos_y());
	if(dir>0){
		return true;
	}
	else{
		return false;
	}
}


float Navigator::center_axes(float angle)
{
	/*Serial.print("center radian:");
		Serial.print("\t");
		Serial.print(angle);
		Serial.print("\t");*/
	if (abs(angle) > PI){
		if(angle<0){
			while(abs(angle)>PI){
				angle+=PI*2;
			}
		}
		else{
			while(abs(angle)>PI){
				angle-=2*PI;
			}
		}
	}
	if(abs(angle+PI) + ADMITTED_ANGLE_ERROR < abs(angle)){
		angle+=PI;
	}
	if(abs(angle-PI) + ADMITTED_ANGLE_ERROR< abs(angle)){
		angle-=PI;
	}
	/*Serial.println(angle);*/
	return angle;
}

float Navigator::center_radian(float angle)
{
	if (abs(angle) > PI){
		if(angle<0){
			while(abs(angle)>PI){
				angle+=PI*2;
			}
		}
		else{
			while(abs(angle)>PI){
				angle-=2*PI;
			}
		}
	}
	return angle;
}


int Navigator::scalaire(float x,float y,float x2,float y2){
	if(x*x2 + y*y2>0){
		return 1;
	}
	else{
		return -1;
	}
}

bool Navigator::isTrajectoryFinished(){
	return trajectory_done;
}
