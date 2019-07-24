#pragma once
#include <list>
#include <mutex>
#include "EventHandler.h"
#include <future>

template <typename... Args>
class Event
{
public:
	typedef EventHandler<Args...> handler_type;

	Event()
	{
	}

	// copy constructor
	Event(const Event& src)
	{
		std::lock_guard<std::mutex> lock(src.m_handlersLocker);

		m_handlers = src.m_handlers;
	}

	// move constructor
	Event(Event&& src)
	{
		std::lock_guard<std::mutex> lock(src.m_handlersLocker);

		m_handlers = std::move(src.m_handlers);
	}

	// copy assignment operator
	Event& operator=(const Event& src)
	{
		std::lock_guard<std::mutex> lock(m_handlersLocker);
		std::lock_guard<std::mutex> lock2(src.m_handlersLocker);

		m_handlers = src.m_handlers;

		return *this;
	}

	// move assignment operator
	Event& operator=(Event&& src)
	{
		std::lock_guard<std::mutex> lock(m_handlersLocker);
		std::lock_guard<std::mutex> lock2(src.m_handlersLocker);

		std::swap(m_handlers, src.m_handlers);

		return *this;
	}

	typename handler_type::handler_id_type add(const handler_type& handler)
	{
		std::lock_guard<std::mutex> lock(m_handlersLocker);

		m_handlers.push_back(handler);

		return handler.id();
	}

	inline typename handler_type::handler_id_type add(const typename handler_type::handler_func_type& handler)
	{
		return add(handler_type(handler));
	}

	bool remove(const handler_type& handler)
	{
		std::lock_guard<std::mutex> lock(m_handlersLocker);

		auto it = std::find(m_handlers.begin(), m_handlers.end(), handler);
		if (it != m_handlers.end())
		{
			m_handlers.erase(it);
			return true;
		}

		return false;
	}

	bool remove_id(const typename handler_type::handler_id_type& handlerId)
	{
		std::lock_guard<std::mutex> lock(m_handlersLocker);

		auto it = std::find_if(m_handlers.begin(), m_handlers.end(),
			[handlerId](const handler_type& handler) { return handler.id() == handlerId; });
		if (it != m_handlers.end())
		{
			m_handlers.erase(it);
			return true;
		}

		return false;
	}

	void call(Args... params) const
	{
		handler_collection_type handlersCopy = get_handlers_copy();

		call_impl(handlersCopy, params...);
	}

	std::future<void> call_async(Args... params) const
	{
		return std::async(std::launch::async, [this](Args... asyncParams) { call(asyncParams...); }, params...);
	}

	inline void operator()(Args... params) const
	{
		call(params...);
	}

	inline typename handler_type::handler_id_type operator+=(const handler_type& handler)
	{
		return add(handler);
	}

	inline typename handler_type::handler_id_type operator+=(const typename handler_type::handler_func_type& handler)
	{
		return add(handler);
	}

	inline bool operator-=(const handler_type& handler)
	{
		return remove(handler);
	}

protected:
	typedef std::list<handler_type> handler_collection_type;

	void call_impl(const handler_collection_type& handlers, Args... params) const
	{
		for (const auto& handler : handlers)
		{
			handler(params...);
		}
	}

	handler_collection_type get_handlers_copy() const
	{
		std::lock_guard<std::mutex> lock(m_handlersLocker);

		// Since the function return value is by copy, 
		// before the function returns (and destruct the lock_guard object),
		// it creates a copy of the m_handlers container.

		return m_handlers;
	}

private:
	handler_collection_type m_handlers;
	mutable std::mutex m_handlersLocker;
};

