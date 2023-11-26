#pragma once
#include <SFML/Graphics.hpp>
#include <forward_list>

namespace my_utility
{
	void ThrowingAssert(bool condition, const char* const msg = "");

	struct EventTable
	{
		using EventIt = std::forward_list<sf::Event>::const_iterator;
		struct SpecialEvent
		{
			int count = 0;
			EventIt last_happened;
			operator bool() const;
		};

		SpecialEvent Closed;
		SpecialEvent LostFocus;
		SpecialEvent GainedFocus;
		SpecialEvent MouseEntered;
		SpecialEvent MouseLeft;

		std::forward_list<sf::Event> events;
	};

	EventTable GetEvents(sf::RenderWindow& window);

	sf::Font LoadFont(const char* const filename);
}

