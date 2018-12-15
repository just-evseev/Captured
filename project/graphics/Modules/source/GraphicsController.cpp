//
// Created by Святослав Кряжев on 25.11.2018.
//

#include "GraphicsController.h"


GraphicsController::GraphicsController(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MouseController> mouse)
                            : window(window), size(window->getSize()),
                              data(nullptr),
                              mouse(mouse), cursor(mouse),
                              hexSpace(window->getSize(), 59),
                              texturePack("./textures/packs/Neon.json") {
    texturePack.load();

    background.set_up(texturePack.get(BACKGROUND));
    background.setPosition(size.x / 2.f + 0.5f, size.y / 2.f);

    grid.set_up(texturePack.get(GRID));
    grid.setPosition(size.x / 2.f + 0.5f, size.y / 2.f);

    player.set_up(texturePack.get(PLAYER));
    player.setPosition(size.x / 2.f + 0.5f, size.y / 2.f);

    lightT.loadFromFile("./Contents/light.png");
    reflectionT.loadFromFile("./Contents/reflection.png");

    light.set_up(lightT);
    light.setPosition(size.x / 2.f + 0.5f, size.y / 2.f);

    reflection.set_up(reflectionT);
    reflection.setPosition(size.x / 2.f + 0.5f, size.y / 2.f);


    cursor.set_texture(texturePack.get(CURSOR));

//    std::clog << "GraphicsController: created" << std::endl;
}

GraphicsController::~GraphicsController() {
    // std::clog << "GraphicsController: destroyed" << std::endl;
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
            mov = RIGHT_UP;
        else if (angle >= 0.f && angle < 60.f)
            mov = RIGHT_DOWN;
        else if (angle >= 60.f && angle < 120.f)
            mov = DOWN;
        else if (angle >= 120.f && angle < 180.f)
            mov = LEFT_DOWN;
        else if (angle >= -180.f && angle < -120.f)
            mov = LEFT_UP;

        i = 20;
        grid.setPosition(size.x / 2.f, size.y / 2.f);
        hexSpace.freak(mov);
        hexSpace.set_movement(mov, sqrt(3.f) * 59 / 20);
        grid.set_movement(mov, sqrt(3.f) * 59 / 20);
    }
    --i;

    cursor.update();

    window->draw(background);

    window->draw(grid);
    grid.move();

    window->draw(hexSpace);
    hexSpace.move();

    window->draw(reflection);
    window->draw(light);
    window->draw(player);


    window->draw(cursor);

}