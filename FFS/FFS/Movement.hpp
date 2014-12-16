#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP	
		
class Movement{
	public:
		Movement(int FPS);
		void start_move(float accelerartion);
		void stop_move();
		void instant_stop();
		void jump(float vy);
		float get_x();
		float get_y();
		float get_next_x();
		float get_next_y();
		void update();
		void move_to(float x, float y);

	private:
		float x,y;
		float vx,vy;
		float ax,ay;
		const float GRAVITATION;
		const int LOOP_PER_SECOND;
};


#endif