#pragma once

#include "BAD/Event/Event.h"
#include <sstream>
#include <cstdint>
namespace BAD{
class BAD_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint64_t p_height, uint64_t p_width)
		: m_height(p_height),
		  m_width(p_width) {};

		  inline uint64_t GetHeight() const { return m_height; }
		  inline uint64_t GetWidth() const { return m_width; }

		  EVENT_CLASS_TYPE(WindowResize);
		  EVENT_CLASS_CATEGORY(EventCategoryApplication);

		  std::string toString() const override {
				std::stringstream ss;
				ss << "WindowResize" << " : " << "(H: " << m_height << ", W: " << m_width << ")";
				return ss.str();
		  }

	protected:
		uint64_t m_height;
		uint64_t m_width;
};

class BAD_API WindowMoveEvent : public Event {
	public:
		WindowMoveEvent(uint64_t p_coordX, uint64_t p_coordY)
		: m_coordX(p_coordX),
		  m_coordY(p_coordY) {};

		  inline uint64_t GetX() const { return m_coordX; }
		  inline uint64_t GetY() const { return m_coordY; }

		  EVENT_CLASS_TYPE(WindowMoved);
		  EVENT_CLASS_CATEGORY(EventCategoryApplication);

		  std::string toString() const override {
				std::stringstream ss;
				ss << "WindowMoved" << " : " << "(" << m_coordX << ", " << m_coordY<< ")";
				return ss.str();
		  }

	protected:
		uint64_t m_coordX;
		uint64_t m_coordY;
};

class BAD_API WindowCloseEvent : public Event {
	public: 
		WindowCloseEvent();
};


class BAD_API WindowFocusEvent : public Event {
	public: 
		WindowFocusEvent();
};


class BAD_API WindowLoseFocusEvent : public Event {
	public: 
		WindowLoseFocusEvent();
};


class BAD_API AppTickEvent : public Event {
	public: 
		AppTickEvent();
};


class BAD_API AppUpdateEvent : public Event {
	public: 
		AppUpdateEvent();
};


class BAD_API AppRenderEvent : public Event {
	public: 
		AppRenderEvent();
};
}