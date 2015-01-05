#ifndef		BULLET_HPP
#define		BULLET_HPP
#include "Projectile.hpp"

class Bullet : public Projectile{
	public:
		Bullet(float x, float y, float alfa, int team);
		~Bullet();
		int get_dmg(int multiplier);
	private:
		const float speed;
};



#endif