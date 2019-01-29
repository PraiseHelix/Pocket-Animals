#include "Form.hpp"




void Form::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->clear();
	
	window->display();
}

void Form::Update()
{

}


Form::~Form()
{
}
