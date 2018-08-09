#pragma once
#include "fwd.h"
#include "collision\aabb.h"

class IDamageDealer
{
public:

	virtual void StartAttack() { isAttacking = true; };
	virtual void StopAttack() { isAttacking = false; };

	bool IsAttacking() const { return isAttacking; }

protected:

	vector<AABB> damageBoxes;

private:

	bool isAttacking;
};