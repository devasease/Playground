#pragma once
#include <functional>
#include <atomic>


//https://www.codeproject.com/Articles/1256352/CppEvent-How-to-Implement-Events-using-Standard-Cp
//Need for https://www.glfw.org/docs/latest/group__window.html#gaa40cd24840daa8c62f36cafc847c72b6
/*
GLFWwindowsizefun glfwSetWindowSizeCallback	(	GLFWwindow * 	window,
GLFWwindowsizefun 	cbfun 
)
*/

template <typename... Args>
class EventHandler
{
public:
	typedef std::function<void(Args...)> handler_func_type;
	typedef unsigned int handler_id_type;

	explicit EventHandler(const handler_func_type& handlerFunc)
		: m_handlerFunc(handlerFunc)
	{
		m_handlerId = ++m_handlerIdCounter;
	}

	// copy constructor
	EventHandler(const EventHandler& src)
		: m_handlerFunc(src.m_handlerFunc), m_handlerId(src.m_handlerId)
	{
	}

	// move constructor
	EventHandler(EventHandler&& src) noexcept
		: m_handlerFunc(std::move(src.m_handlerFunc)), m_handlerId(src.m_handlerId)
	{
	}

	// copy assignment operator
	EventHandler& operator=(const EventHandler& src)
	{
		m_handlerFunc = src.m_handlerFunc;
		m_handlerId = src.m_handlerId;

		return *this;
	}

	// move assignment operator
	EventHandler& operator=(EventHandler&& src) noexcept
	{
		std::swap(m_handlerFunc, src.m_handlerFunc);
		m_handlerId = src.m_handlerId;

		return *this;
	}

	// function call operator
	void operator()(Args... params) const
	{
		if (m_handlerFunc)
		{
			m_handlerFunc(params...);
		}
	}

	bool operator==(const EventHandler& other) const
	{
		return m_handlerId == other.m_handlerId;
	}

	operator bool() const
	{
		return m_handlerFunc;
	}

	handler_id_type id() const
	{
		return m_handlerId;
	}

private:
	handler_func_type m_handlerFunc;
	handler_id_type m_handlerId;
	static std::atomic_uint m_handlerIdCounter;
};

template <typename... Args> std::atomic_uint EventHandler<Args...>::m_handlerIdCounter(0);

