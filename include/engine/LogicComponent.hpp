//
// Created by Lehdari on 6.4.2019.
//

#ifndef ECSTESTGAME_LOGICCOMPONENT_HPP
#define ECSTESTGAME_LOGICCOMPONENT_HPP


#include <utility>
#include <Types.hpp>
#include <Ecs.hpp>


struct LogicComponent {
    friend class LogicSystem;
    friend class EventSystem;

    LogicComponent();

    LogicComponent(const LogicComponent& other);
    LogicComponent(LogicComponent&& other);
    LogicComponent operator=(const LogicComponent& other);
    LogicComponent operator=(LogicComponent&& other);

    ~LogicComponent();

    template <typename T_Logic, typename... T_Args>
    void addLogic(T_Args&&... args);

private:
    void*   _logic;
    void    (*_logicExecutor)(void*, Ecs& ecs, const EntityId& eId);
    void    (*_logicDeleter)(void*);
    void    (*_logicCopier)(void*, LogicComponent&);

    template <typename T_Logic>
    static void executeLogic(void* logic, Ecs& ecs, const EntityId& eId);

    template <typename T_Logic>
    static void deleteLogic(void* logic);

    template <typename T_Logic>
    static void copyLogic(void* logic, LogicComponent& lc);
};


DECLARE_COMPONENT_TEMPLATES(LogicComponent);


template <typename T_Logic, typename... T_Args>
void LogicComponent::addLogic(T_Args&&... args)
{
    _logic = new T_Logic(std::forward<T_Args>(args)...);
    _logicExecutor = &executeLogic<T_Logic>;
    _logicDeleter = &deleteLogic<T_Logic>;
    _logicCopier = &copyLogic<T_Logic>;
}


template <typename T_Logic>
void LogicComponent::executeLogic(void* logic, Ecs& ecs, const EntityId& eId)
{
    (*static_cast<T_Logic*>(logic))(ecs, eId);
}

template <typename T_Logic>
void LogicComponent::deleteLogic(void* logic)
{
    delete static_cast<T_Logic*>(logic);
}

template <typename T_Logic>
void LogicComponent::copyLogic(void* logic, LogicComponent& lc)
{
    lc.addLogic<T_Logic>(*static_cast<T_Logic*>(logic));
}


#endif //ECSTESTGAME_LOGICCOMPONENT_HPP
