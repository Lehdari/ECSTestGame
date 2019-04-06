//
// Created by Lehdari on 29.9.2018.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Ecs.hpp>

#include "PhysicsSystem.hpp"
#include "SpriteComponent.hpp"
#include "SpriteRenderer.hpp"
#include "CollisionSystem.hpp"
#include "EventSystem.hpp"


class Window {
public:
    struct Settings {
        std::string     windowName;
        sf::VideoMode   videoMode;
        int64_t         framerateLimit;

        Settings(const std::string& windowName = "",
                 const sf::VideoMode& videoMode = sf::VideoMode(800, 600),
                 int64_t framerateLimit = 60) :
             windowName     (windowName),
             videoMode      (videoMode),
             framerateLimit (framerateLimit)
        {}
    };

    enum GameButton {
        MoveLeft,
        MoveRight,
        LaunchBall,
    };

    std::unordered_map<GameButton, int, std::hash<int>> _keybinds = {
        {MoveLeft, sf::Keyboard::Left},
        {MoveRight, sf::Keyboard::Right},
        {LaunchBall, sf::Keyboard::Space},
    };

    Window(const Settings& settings = Settings());

    bool isKeyPressed(const GameButton&) const;

    void loop(void);

private:
    Settings            _settings;
    sf::RenderWindow    _window;

    Ecs             _ecs;
    EventSystem     _eventSystem;
    PhysicsSystem   _physicsSystem;
    SpriteRenderer  _spriteRenderer;
    CollisionSystem _collisionSystem;

    sf::Texture _blockTexture;
    sf::Texture _ballTexture;

    uint64_t _playerId;
    uint64_t _ballId;

    void handleEvents(sf::Event& event);
    void runSystems(void);
    void render(void);
};


#endif	//	TYPES_HPP
