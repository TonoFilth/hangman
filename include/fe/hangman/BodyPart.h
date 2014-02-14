#ifndef __BODY_PART_H__
#define __BODY_PART_H__

#include <vector>
#include <SFML/Graphics.hpp>

#include "fe/hangman/Joint.h"

namespace fe
{

class BodyPart;

extern const BodyPart InvalidBodyPart;

typedef std::vector<BodyPart> TBodyPartVec;
typedef std::vector<UI32>  	  TOrderVec;

const BodyPart& FindBodyPartByOrder(const TBodyPartVec& bodyParts, const UI32 order);
const Joint& FindJointByOrder(const TBodyPartVec& bodyParts, const UI32 order);

class BodyPart
{
private:
	UI32 		 m_Order;
	sf::IntRect  m_TxCoords;
	TJointVec 	 m_Joints;

	void Copy(const BodyPart& toCopy);

public:
	BodyPart(UI32 bOrder, const sf::IntRect& txCoords);
	BodyPart(const BodyPart& toCopy);
	BodyPart& operator=(const BodyPart& toCopy);
	~BodyPart();

	void AddJoint(const Joint& joint);

	UI32 GetOrder() const;
	sf::IntRect GetTextureCoords() const;
	TOrderVec GetJointOrders() const;
	TJointVec GetJoints() const;

	bool IsValid() const;
	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
