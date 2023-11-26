#include "SFMLUtility.h"

#include <stdexcept>
#include <cassert>

namespace my_utility
{
	void ThrowingAssert(bool condition, const char* const msg)
	{
		if (condition)
		{
			return;
		}
		assert(msg != nullptr);
		throw std::runtime_error(msg);
	}

	EventTable::SpecialEvent::operator bool() const
	{
		return count != 0;
	}

	EventTable GetEvents(sf::RenderWindow& window)
	{
		EventTable events;
		auto it = events.events.before_begin();
		sf::Event current_event;
		while (window.pollEvent(current_event))
		{
			it = events.events.emplace_after(it, current_event);
			switch (current_event.type)
			{
			case sf::Event::EventType::Closed:
			{
				++events.Closed.count;
				events.Closed.last_happened = it;
			}
			break;
			case sf::Event::EventType::LostFocus:
			{
				++events.LostFocus.count;
				events.LostFocus.last_happened = it;
			}
			break;
			case sf::Event::EventType::GainedFocus:
			{
				++events.GainedFocus.count;
				events.GainedFocus.last_happened = it;
			}
			break;
			case sf::Event::EventType::MouseEntered:
			{
				++events.MouseEntered.count;
				events.MouseEntered.last_happened = it;
			}
			break;
			case sf::Event::EventType::MouseLeft:
			{
				++events.MouseLeft.count;
				events.MouseLeft.last_happened = it;
			}
			break;
			default:
				break;
			}
		}
		return events;
	}

	sf::Font LoadFont(const char* const filename)
	{
		assert(filename != nullptr);
		sf::Font font;
		ThrowingAssert(font.loadFromFile(filename), "cant load file");
		return font;
	}
}