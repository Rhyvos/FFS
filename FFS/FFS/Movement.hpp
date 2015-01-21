#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP	
#include "Headers.h"

class Movement{
	public:
		Movement(int FPS);
		void start_move(float accelerartion);
		void stop_move();
		void instant_stop_x();
		void instant_stop_y();
		void jump(float vy);
		float get_x();
		float get_y();
		std::string get_string_x();
		std::string get_string_y();
		float get_next_x();
		float get_next_y();
		float get_vx();
		float get_vy();
		virtual void update();
		void reset();
		void move_to(float x, float y);
		void set_maximum_vx(float vx);
		void set_maximum_vy(float vy);
		void fall();
		bool is_falling();
	protected:
		bool stop;
		bool falling;
		float x,y;
		float vx,vy;
		float ax,ay;
		const int LOOP_PER_SECOND;
		float maximum_vx,maximum_vy;
		const float GRAVITATION;
		
};


#endif