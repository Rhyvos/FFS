#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP	
		
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
		void update();
		void reset();
		void move_to(float x, float y);

	private:
		float x,y;
		float vx,vy;
		float maximum_vx,maximum_vy;
		float ax,ay;
		const float GRAVITATION;
		const int LOOP_PER_SECOND;
};


#endif