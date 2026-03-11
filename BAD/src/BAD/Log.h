#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core.h"

namespace BAD{
	class BAD_API Log
	{
		private:
			static std::shared_ptr<spdlog::logger> m_coreLogger;
			static std::shared_ptr<spdlog::logger> m_clientLogger;
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return m_coreLogger;}
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){return m_clientLogger;}

	};
}

#define BAD_CORE_WARN(...) ::BAD::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BAD_CORE_ERROR(...) ::BAD::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BAD_CORE_CRITICAL(...) ::BAD::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define BAD_CORE_DBUG(...) ::BAD::Log::GetCoreLogger()->debug(__VA_ARGS__)

#define BAD_WARN(...) ::BAD::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BAD_ERROR(...) ::BAD::Log::GetClientLogger()->error(__VA_ARGS__)
#define BAD_CRITICAL(...) ::BAD::Log::GetClientLogger()->critical(__VA_ARGS__)
#define BAD_DBUG(...) ::BAD::Log::GetClientLogger()->debug(__VA_ARGS__)
