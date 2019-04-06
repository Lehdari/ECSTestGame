
#include "Window.hpp"
#include "ControlSystem.hpp"
#include "PhysicsComponent.hpp"

ControlComponent::ControlComponent(float movementAmount) :
    movementAmount(movementAmount)
{
}

ControlSystem::ControlSystem(const Window& window) :
    _window(window)
{
}

void ControlSystem::operator()(const EntityId& eId, ControlComponent& cc, PhysicsComponent& pc) {

    if (_window.isKeyPressed(Window::GameButton::MoveLeft)) {
        pc.pos.x -= cc.movementAmount;
    }
    if (_window.isKeyPressed(Window::GameButton::MoveRight)) {
        pc.pos.x += cc.movementAmount;
    }
}
