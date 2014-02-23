#ifndef __JOINT_H__
#define __JOINT_H__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "fe/types/BasicTypes.h"
#include "fe/types/AlignmentTypes.h"

namespace fe
{

class Joint;

extern const UI32 K_ROOT_ORDER;
extern const UI32 K_INVALID_ORDER;
extern const Joint InvalidJoint;

typedef std::vector<Joint> TJointVec;

class Joint
{
private:
	UI32 		 m_Order;
	sf::Vector2f m_Coords;
	THAlign 	 m_HAlign;
	TVAlign 	 m_VAlign;

	void Copy(const Joint& toCopy);

public:
	Joint(UI32 jOrder, const sf::Vector2f& jCoords,
		const THAlign hAlign = THAlign::LEFT, const TVAlign vAlign = TVAlign::TOP);
	Joint(const Joint& toCopy);
	Joint& operator=(const Joint& toCopy);
	~Joint();

	UI32 GetOrder() const;
	sf::Vector2f GetCoords() const;
	THAlign GetHorizontalAlignment() const;
	TVAlign GetVerticalAlignment() const;

	bool IsValid() const;
	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
