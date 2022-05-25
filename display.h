#include<SFML/Graphics.hpp>
#include<iostream>


class display
{
private:
    sf::Image image;
    sf::RenderWindow* window;
    sf::Texture texture;
    sf::Sprite sprite;


public:
    display(int height, int width){
    window = new sf::RenderWindow(sf::VideoMode(height, width), "Display");
    this->image.create(height, width);
    window->display();
}
    ~display();
    void update_pixel(int x,int y, uint8_t r, uint8_t g, uint8_t b){
        this->image.setPixel(x,y, sf::Color(r,g,b));
    }
    void update_display(){
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        this->window->draw(sprite);
        this->window->display();
        sf::Event event;
        while (this->window->pollEvent(event)){
            if ((event.type == sf::Event::Closed))
                this->window->close();
        }
    }
    void update(int x, int y, uint8_t r, uint8_t g, uint8_t b){
        this->image.setPixel(x,y, sf::Color(r,g,b));
        

        texture.loadFromImage(image);
        sprite.setTexture(texture);

        this->window->draw(sprite);
        this->window->display();
        sf::Event event;
        while (this->window->pollEvent(event)){
            if ((event.type == sf::Event::Closed))
                this->window->close();
        }

        


    }
};



display::~display()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Display");
    this->image.create(800,800);
    window.display();
}