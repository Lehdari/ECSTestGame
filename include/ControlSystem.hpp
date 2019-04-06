#ifndef ECSTESTGAME_CONTROLSYSTEM_HPP
#define ECSTESTGAME_CONTROLSYSTEM_HPP

#include <System.hpp>

 // Forward declarations
class PhysicsComponent;
class Window;


class ControlComponent {

public:
    ControlComponent(float);
    float movementAmount;
};

TECS_SYSTEM(ControlSystem, ControlComponent, PhysicsComponent) {
public:
    ControlSystem(const Window&);

    void operator()(const EntityId&, ControlComponent&, PhysicsComponent&);

private:
    const Window& _window;
};

#endif //ECSTESTGAME_CONTROLSYSTEM_HPP
