#include "SFMLUtility.h"
#include "Spline.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <utility>
#include <optional>
#include <map>

using my_utility::ThrowingAssert;
using my_utility::LoadFont;
using my_utility::GetEvents;
using my_figures::Spline3_2d;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920u/2, 1080u/2), "app.exe", 7);
	ThrowingAssert(window.isOpen(), "window is not open");

	sf::Font font = LoadFont("consolas.ttf");
	Spline3_2d spline
	{
		{0, 0},
		{100, 0},
		{100, 100},
		{0, 100},
	};

	const std::map<char, sf::Vector2f&> key_to_point =
	{
		{'1', spline.from},
		{'2', spline.mid_1},
		{'3', spline.mid_2},
		{'4', spline.to},
	};

	sf::Vector2f* current_point_ptr = nullptr;
	float circle_size = 10;
	int spline_parts = 30;


	sf::VertexArray line(sf::LineStrip, spline_parts + 1);
	for (int i = 0; i <= spline_parts; ++i)
	{
		line[i].color = sf::Color::Magenta;
	}

	while (true)
	{
		const auto&& event_table = GetEvents(window);

		if (event_table.Closed)
		{
			break;
		}

		for (const sf::Event& event : event_table.events)
		{
			if(event.type == sf::Event::EventType::TextEntered) // 4
			{
				auto&& found_it = key_to_point.find(static_cast<char>(event.text.unicode));
				if (found_it == key_to_point.end())
				{
					current_point_ptr = nullptr;
				}
				else
				{
					current_point_ptr = &found_it->second;
				}
			}
			else if(event.type == sf::Event::EventType::MouseButtonPressed) // 9
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)//0
				{
					if (current_point_ptr)
					{
						current_point_ptr->x = event.mouseButton.x;
						current_point_ptr->y = event.mouseButton.y;
					}
				}
			}
		}

		window.clear();

		sf::CircleShape gizmo(circle_size);

		gizmo.setFillColor(sf::Color::Red);
		gizmo.setPosition(spline.from - sf::Vector2f{ circle_size, circle_size });
		window.draw(gizmo);

		gizmo.setFillColor(sf::Color::Yellow);
		gizmo.setPosition(spline.mid_1 - sf::Vector2f{ circle_size, circle_size });
		window.draw(gizmo);

		gizmo.setFillColor(sf::Color::Green);
		gizmo.setPosition(spline.mid_2 - sf::Vector2f{ circle_size, circle_size });
		window.draw(gizmo);

		gizmo.setFillColor(sf::Color::Blue);
		gizmo.setPosition(spline.to - sf::Vector2f{ circle_size, circle_size });
		window.draw(gizmo);

		for (int i = 0; i <= spline_parts; ++i)
		{
			line[i].position = spline.GetPoint((1. / spline_parts) * i);
		}

		window.draw(line);

		window.display();
	}
	window.close();
}