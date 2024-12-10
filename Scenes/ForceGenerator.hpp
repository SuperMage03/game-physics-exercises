#pragma once
#include <glm/glm.hpp>
#include "RigidBody.hpp"

// Abstract class for Force Generators
class ForceGenerator {
public:
    virtual ~ForceGenerator();
    virtual void updateForce(RigidBody& rb, float duration) = 0;
};

class GenericTorqueGenerator : public ForceGenerator {
public:
    GenericTorqueGenerator(const glm::vec3& torque);
    void updateForce(RigidBody& rb, float duration) override;
private:
    glm::vec3 _torque;
};

class ExternalForceGenerator : public ForceGenerator {
public:
    ExternalForceGenerator(const glm::vec3& force, const glm::vec3& world_position);
    void setForce(const glm::vec3& force, const glm::vec3& world_position);
    void updateForce(RigidBody& rb, float duration) override;
private:
    glm::vec3 _force;
    glm::vec3 _world_position;
};

class GravityForceGenerator : public ForceGenerator {
private:
    glm::vec3 _gravity_acceleration;
public:
    GravityForceGenerator(const glm::vec3& gravity_acceleration);
    void updateForce(RigidBody& rb, float duration) override;
};
