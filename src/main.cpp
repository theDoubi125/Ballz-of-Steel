#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

#include "event/event_handler.h"
#include "world/world.h"
#include "entity/building/tower.h"
#include "entity/ball/charging_ball.h"
#include "entity/building/wall.h"
#include "graphic/image_manager.h"
#include "player/player.h"
#include "player/game_manager.h"
#include "graphic/util.h"
#include "graphic/counter.h"

int main()
{
    Vec resolution = Vec(800, 600);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Ballz of Steel");

    EventHandler event(window);

    World world(resolution*4);

    JoypadPlayerController joypadController = JoypadPlayerController(event, 0, world.getDim(), Vec(0, 0));
    int *keys = new int[8];
    keys[DOWN] = sf::Keyboard::Down;
    keys[UP] = sf::Keyboard::Up;
    keys[LEFT] = sf::Keyboard::Left;
    keys[RIGHT] = sf::Keyboard::Right;
    keys[SELECT] = sf::Keyboard::A;
    keys[ORDER] = sf::Keyboard::Z;
    keys[ZOOM] = sf::Keyboard::Q;
    keys[DEZOOM] = sf::Keyboard::S;
    //, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::A, sf::Keyboard::Z});
    KeyboardPlayerController keyController = KeyboardPlayerController(event, keys, world.getDim(), Vec(0, 0));
    joypadController.setSpeed(0.1);
    keyController.setSpeed(5);
    Player *bluePlayer = new Player(joypadController, world, sf::Color::Blue, sf::Color(200, 255, 255, 255), sf::Color::Yellow, sf::Color::Red);
    Player *redPlayer = new Player(keyController, world, sf::Color::Red, sf::Color(255, 200, 100, 255), sf::Color::Yellow, sf::Color::Red);

    Vec A, B;
    int timePressed = 0;
//    bool zPressed = false, select = false;

    draw::initRenderEngine();

    std::vector<Player*> players;
    players.push_back(bluePlayer);
    players.push_back(redPlayer);

    GameManager game = GameManager(resolution, world, players);

    Vec::setRender(&window);

    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            world.addEntity(new Ball(rand()%2 ? *redPlayer : *bluePlayer, Vec(i*30, j*30), 15, 1, Vec(0, 0), 100));

    while (window.isOpen())
    {
        timePressed++;
        event.updateEvents();
        //gui.guiUpdate(event);

        window.clear(sf::Color::Black);
        game.update();
        world.update();
        //world.draw(window);
        //gui.render(window, event);
        game.draw(window);
        //view.setCenter(gui.getCamPos());
        //view.setSize(Vec(800+(2400-800)*(gui.getZoom()/10.0), 600+(1800-600)*(gui.getZoom()/10.0)));

        window.display();
        //window.clear(sf::Color::White);
        if(event.closed() || event.keyDown(sf::Keyboard::Escape))
            window.close();
    }

    return 0;
}
