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
protected:
		const int dmg;
		int life;
		int team;
};


#endif