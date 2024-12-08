#pragma once
#include <vector>
#include "CollisionContact.h"

class CollisionSolver {
public:
    virtual void resolveContacts(std::vector<CollisionContact>& contacts, float duration) = 0;
};

class ImpulseSolver : public CollisionSolver {
public:
    void resolveContacts(std::vector<CollisionContact>& contacts, float duration) override;
};
