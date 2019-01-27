#include "Form.hpp"



Form::Form()
{
}

void Form::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(title);
	for (auto & option : options) {
		window->draw(*option);
	}
	options[selected_option_index]->DrawSelection(window);
}

void Form::Update(std::shared_ptr<sf::RenderWindow> window)
{

}


Form::~Form()
{
}
