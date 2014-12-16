#include <boost/thread.hpp>		
#include "Movement.hpp"


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
		}

		void Movement::start_move(float accelerartion){
			ax=accelerartion;
			boost::this_thread::sleep(boost::posix_time::milliseconds(500));
			ax=0;
		}

		void Movement::stop_move(){
			ax=-vx;
			boost::this_thread::sleep(boost::posix_time::milliseconds(500));
			ax=0;
		}

		void Movement::instant_stop(){
			vx=0;
			vy=0;
		}

		void Movement::jump(float vy){
			this->vy=vy;
			ay=-vy;
		}

		float Movement::get_x(){
			return x;
		}

		float Movement::get_y(){
			return y;
		}

		float Movement::get_next_x(){
			return x+(vx/LOOP_PER_SECOND);
		}

		float Movement::get_next_y(){
			return y+(vy/LOOP_PER_SECOND);
		}

		void Movement::update(){
			vx+=ax/LOOP_PER_SECOND;
			vy+=ay/LOOP_PER_SECOND;
			x+=vx/LOOP_PER_SECOND;
			y+=vy/LOOP_PER_SECOND;
		}

		void Movement::move_to(float x, float y){
			this->x=x;
			this->y=y;
		}