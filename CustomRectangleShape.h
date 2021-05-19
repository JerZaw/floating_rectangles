#ifndef CUSTOMRECTANGLESHAPE_H
#define CUSTOMRECTANGLESHAPE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

class CustomRectangleShape : public sf::RectangleShape
{
private:
    int speed_x=0;
    int speed_y=0;
    int rotation_speed=0;
    bool is_selected=false;
    sf::IntRect my_bounds;
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position): sf::RectangleShape(size){
        setPosition(position);
    }
    int read_speed_x(){
        return speed_x;
    }
    int read_speed_y(){
        return speed_y;
    }
    void setSpeed(int arg_speed_x, int arg_speed_y, int arg_rotation_speed){
        this->speed_x = arg_speed_x;
        this->speed_y = arg_speed_y;
        this->rotation_speed = arg_rotation_speed;
    }
    void animate(const sf::Time &elapsed){
        float t = float(elapsed.asSeconds());
        if(this->is_selected==false){
            bounce();
            this->move(speed_x * t, speed_y * t);
            this->rotate(rotation_speed * t);
        }
        else{
            this->speed_x=abs(speed_x);
            this->speed_y=abs(speed_y);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    &&this->getGlobalBounds().left+this->getGlobalBounds().width < this->my_bounds.left+this->my_bounds.width){
                this->move(speed_x * t, 0);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
                    &&this->getGlobalBounds().left > this->my_bounds.left){
                this->move(-speed_x * t, 0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                    &&this->getGlobalBounds().top+this->getGlobalBounds().height < this->my_bounds.top+this->my_bounds.height){
                this->move(0, speed_y * t);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                    &&this->getGlobalBounds().top > this->my_bounds.top){
                this->move(0, -speed_y * t);
            }
        }
    }

    void setBounds(int left_bound, int right_bound, int upper_bound, int lower_bound){
        sf::IntRect pomrect(left_bound,upper_bound,right_bound,lower_bound);
        this->my_bounds = pomrect;
    }
    void setBounds(sf::IntRect bounds_rectangle){
        this->my_bounds = bounds_rectangle;
    }

    void bounce(){
        if(this->getGlobalBounds().left <= this->my_bounds.left){
            this->speed_x=abs( this->speed_x);
        }
        else if (this->getGlobalBounds().left+this->getGlobalBounds().width >= this->my_bounds.left+this->my_bounds.width){
            this->speed_x=-abs( this->speed_x);
        }

        if(this->getGlobalBounds().top <= this->my_bounds.top){
            this->speed_y=abs( this->speed_x);
        }
        else if(this->getGlobalBounds().top+this->getGlobalBounds().height >= this->my_bounds.top+this->my_bounds.height){
            this->speed_y=-abs( this->speed_x);
        }
    }

    void select(){
        //this->setFillColor(sf::Color(rand()%250,rand()%250,rand()%250));
        this->is_selected = true;
    }
    void unselect(){
        this->is_selected = false;
        this->setFillColor(sf::Color(128,128,128));
    }
};


#endif // CUSTOMRECTANGLESHAPE_H
