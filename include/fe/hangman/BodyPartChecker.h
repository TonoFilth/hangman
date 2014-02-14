#ifndef __BODY_PART_CHECKER_H__
#define __BODY_PART_CHECKER_H__

#include <iostream>
#include "fe/hangman/BodyPart.h"

namespace fe
{

class BodyPartChecker
{
private:
	static bool CheckBodyParts(const TBodyPartVec& bodyParts, TOrderVec& orders);
	static bool CheckJoints(const BodyPart& bodyPart, TOrderVec& orders);
	static bool CheckInvalidOrder(const TOrderVec& orders);
	static void CheckMissingReferences(const TBodyPartVec& bodyParts,
		const TOrderVec& bpOrders, const TOrderVec& jOrders);

	BodyPartChecker();
	~BodyPartChecker();
	BodyPartChecker(const BodyPartChecker& toCopy);
	BodyPartChecker& operator=(const BodyPartChecker& toCopy);

public:
	static bool Check(const TBodyPartVec& bodyParts);
};

}

#endif
