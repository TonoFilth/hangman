#ifndef __JOINT_H__
#define __JOINT_H__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "fe/types/BasicTypes.h"

namespace fe
{

class Joint;

typedef std::vector<Joint> TJointVec;

class Joint
{
private:
	UI32 		 m_Order;
	sf::Vector2f m_Coords;

	void Copy(const Joint& toCopy);

public:
	Joint(UI32 jOrder, const sf::Vector2f& jCoords);
	Joint(const Joint& toCopy);
	Joint& operator=(const Joint& toCopy);
	~Joint();

	UI32 GetOrder() const;
	sf::Vector2f GetCoords() const;

	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
