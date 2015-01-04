#include <boost/thread.hpp>		
#include "Movement.hpp"
#include <iostream>

		Movement::Movement(int FPS):
		GRAVITATION(-250),
		LOOP_PER_SECOND(FPS)
		{
			x=0.0;
			y=0.0;
			vx=0;
			vy=0;
			ax=0;
			ay=0;
			maximum_vx=60;
			maximum_vy=60;
		}

		void Movement::start_move(float accelerartion){
			ax=accelerartion;
		}

		void Movement::stop_move(){
			vx=0;
			ax=0;
			

			
		}

		void Movement::instant_stop_x(){
			vx=0;
			ax=0;
		}
		void Movement::instant_stop_y(){
			vy=0;
			ay=0;
		}

		void Movement::jump(float vy){
			this->vy=vy;
			ay=GRAVITATION;
		}

		float Movement::get_x(){
			return x;
		}

		float Movement::get_y(){
			return y;
		}

		std::string Movement::get_string_x(){
			return std::to_string(x);
		}

		std::string Movement::get_string_y(){
			return std::to_string(y);
		}


		float Movement::get_next_x(){
			return x+(vx/LOOP_PER_SECOND);
		}

		float Movement::get_next_y(){
			return y+(vy/LOOP_PER_SECOND);
		}

		void Movement::update(){
			if(vx+ax>maximum_vx){
				vx=maximum_vx;
				ax=0;
			}

			if(vy+ay>maximum_vy){
				vy=maximum_vy;
				ay=0;
			}
			vx+=ax/LOOP_PER_SECOND;
			vy+=ay/LOOP_PER_SECOND;
			x+=vx/LOOP_PER_SECOND;
			y+=vy/LOOP_PER_SECOND;
		}

		void Movement::move_to(float x, float y){
			this->x=x;
			this->y=y;
		}

		float Movement::get_vx(){
			return vx;
		}

		float Movement::get_vy(){
			return vy;
		}

		void Movement::reset(){
			x=0.0;
			y=0.0;
			vx=0;
			vy=0;
			ax=0;
			ay=0;
			maximum_vx=60;
			maximum_vy=60;
		}

