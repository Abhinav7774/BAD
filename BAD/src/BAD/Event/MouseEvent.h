#pragma once

#include "BAD/Event/Event.h"
#include <sstream>
#include <cstdint>

namespace BAD {
class BAD_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(uint64_t p_coordX, uint64_t p_coordY)
		 : m_coordX(p_coordX),
		   m_coordY(p_coordY) {};

		inline uint64_t GetX() const { return m_coordX; }
		inline uint64_t GetY() const { return m_coordY; }

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse);

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMoved" << " : (" << m_coordX << "," << m_coordY << ")";
			return ss.str();
		}
	protected:
		uint64_t m_coordX;
		uint64_t m_coordY;
};

class BAD_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(uint64_t p_offsetX, uint64_t p_offsetY)
		 : m_offsetX(p_offsetX),
		   m_offsetY(p_offsetY) {};

		inline uint64_t GetX() const { return m_offsetX; }
		inline uint64_t GetY() const { return m_offsetY; }

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse);

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolled" << " : (" << m_offsetX << "," << m_offsetY << ")";
			return ss.str();
		}
	protected:
		uint64_t m_offsetX;
		uint64_t m_offsetY;
};



class BAD_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const {
			return m_mouseButton;
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);

	protected:
		MouseButtonEvent(int p_mouseButton)
		: m_mouseButton(p_mouseButton) {}

		int m_mouseButton;
};

class BAD_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int p_mouseButton) 
		: MouseButtonEvent(p_mouseButton) {}

		EVENT_CLASS_TYPE(MouseButtonPressed);

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressed" << " : " << m_mouseButton;
			return ss.str();
		}	
};

class BAD_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int p_mouseButton) 
		: MouseButtonEvent(p_mouseButton) {}

		EVENT_CLASS_TYPE(MouseButtonReleased);

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased" << " : " << m_mouseButton;
			return ss.str();
		}	
};
}