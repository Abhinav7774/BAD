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

		EventType GetEventType() const { return EventType::MouseMoved; }
		int GetCategoryFlag() const { return EventCategoryMouse; }
		const std::string GetEventName() const { return "MouseMoved"; }
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

		EventType GetEventType() const { return EventType::MouseScrolled; }
		int GetCategoryFlag() const { return EventCategoryMouse; }
		const std::string GetEventName() const { return "MouseScrolled"; }
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
		int GetCategoryFlag() const { return EventCategoryInput | EventCategoryMouse; }

	protected:
		MouseButtonEvent(int p_mouseButton)
		: m_mouseButton(p_mouseButton) {}

		int m_mouseButton;
};

class BAD_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int p_mouseButton) 
		: MouseButtonEvent(p_mouseButton) {}

		EventType GetEventType() const { return EventType::MouseButtonPressed; }
		const std::string GetEventName() const { return "MouseButtonPressed"; }
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

		EventType GetEventType() const { return EventType::MouseButtonReleased; }
		const std::string GetEventName() const { return "MouseButtonReleased"; }
		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased" << " : " << m_mouseButton;
			return ss.str();
		}	
};
}