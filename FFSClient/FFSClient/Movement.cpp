	
#include "Movement.hpp"


		Movement::Movement(int FPS):
		GRAVITATION(-250),
		LOOP_PER_SECOND(FPS)
		{
			stop=false;
			x=0.0;
			y=0.0;
			vx=0;
			vy=0;
			ax=0;
			ay=0;
			maximum_vx=120;
			maximum_vy=120;
			falling= false;
		}

		void Movement::start_move(float accelerartion){
			ax=accelerartion;
			stop=false;
		}

		void Movement::stop_move(){

			ax=-vx;
			stop=true;

			
		}

		void Movement::instant_stop_x(){
			vx=0;
			ax=0;
		}
		void Movement::instant_stop_y(){
			vy=0;
			ay=0;
			falling=false;

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
			if(vx+ax<-maximum_vx){
				vx=-maximum_vx;
				ax=0;
			}

			if(vy+ay>maximum_vy){
				vy=maximum_vy;
				ay=0;
			}

			if(stop==true&&vx*ax>=0){
				vx=0;
				ax=0;
				stop=false;
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
			maximum_vx=120;
			maximum_vy=120;
			falling=false;
		}

		void Movement::set_maximum_vx(float vx){
			maximum_vx=vx;
		}

		void Movement::set_maximum_vy(float vy){
			maximum_vy=vy;
		}

		void Movement::fall(){
			ay=GRAVITATION;
			falling=true;
		}

		bool Movement::is_falling(){
			return falling;
		}