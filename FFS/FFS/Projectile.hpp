#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Movement.hpp"

class Projectile : public Movement{
	public:
		Projectile(int dmg,int life);
		~Projectile();
		void update();
		virtual int get_dmg(float multiplier);
		int get_team();
		bool is_alive();
		float get_alpha();
		int get_id();
		void set_alpha(float alpha);
		void set_id(int id);
protected:
		int id;
		const int dmg;
		int life;
		int team;
		float alpha;
};


#endif