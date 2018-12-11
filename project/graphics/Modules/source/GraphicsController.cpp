//
// Created by Святослав Кряжев on 25.11.2018.
//

#include "GraphicsController.h"


GraphicsController::GraphicsController(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MouseController> mouse)
                            : window(window), size(window->getSize()),
                              data(nullptr),
                              mouse(mouse), cursor(mouse),
                              hexSpace(window->getSize(), 59){

    backgroundTexture.loadFromFile("./Contents/sprites/Fon.png");

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

    gridTexture.loadFromFile("./Contents/sprites/grid.png");

    gridSprite.setTexture(gridTexture);

    sf::Vector2f size1(gridTexture.getSize());

    gridSprite.setOrigin(size1.x / 2.f, size1.y / 2.f);
    gridSprite.setPosition(this->size.x / 2.f, this->size.y / 2.f);


    playerTexture.loadFromFile("./Contents/sprites/Igrok.png");

    playerSprite.setTexture(playerTexture);

    sf::Vector2f size(playerTexture.getSize());

    playerSprite.setOrigin(size.x / 2.f, size.y / 2.f);
    playerSprite.setPosition(this->size.x / 2.f, this->size.y / 2.f);

    areaTexture.loadFromFile("./Contents/sprites/territoria_bez_sveta.png");

    grid.set_texture(gridTexture);
    //grid.setPosition(this->size.x / 2.f, this->size.y / 2.f);


    std::clog << "GraphicsController: created" << std::endl;
}

GraphicsController::~GraphicsController() {
    std::clog << "GraphicsController: destroyed" << std::endl;
}

void GraphicsController::update(std::shared_ptr<DataPacket> data) {
    this->data = data;
    hexSpace.rebuild(data->areas, data->players);
}

void GraphicsController::draw() {
    if(!i) {
        float angle = mouse->get_angle_deg();

        if (angle >= -120.f && angle < -60.f)
            mov = UP;
        else if (angle >= -60.f && angle < 0.f)
            mov = LEFT_UP;
        else if (angle >= 0.f && angle < 60.f)
            mov = LEFT_DOWN;
        else if (angle >= 60.f && angle < 120.f)
            mov = DOWN;
        else if (angle >= 120.f && angle < 180.f)
            mov = RIGHT_DOWN;
        else if (angle >= -180.f && angle < -120.f)
            mov = RIGHT_UP;

        i = 20;
        grid.set_position(this->size.x / 2.f, this->size.y / 2.f);
        hexSpace.freak();
        hexSpace.set_movement(mov, sqrt(3.f) * 59 / 20);
        grid.set_movement(mov, sqrt(3.f) * 59 / 20);
    }
    --i;

    cursor.update();

    window->draw(backgroundSprite);

    window->draw(grid);
    grid.move();

    //window->draw(hexMap);
    window->draw(hexSpace);
    hexSpace.move();

    window->draw(playerSprite);

    window->draw(cursor);
}