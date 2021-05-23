
namespace MATD {
	namespace CORE {
		class Log {
		public:
			static void AddAppLogTrace(char* frmt, ...);
			static void AddAppLogInfo(char* frmt, ...);
			static void AddAppLogWarn(char* frmt, ...);
			static void AddAppLogError(char* frmt, ...);
			static void AddAppLogFatal(char* frmt, ...);
		};
	}
}

//Client log macros
#define MATD_TRACE(...)        ::MATD::CORE::Log::AddAppLogTrace(__VA_ARGS__)
#define MATD_INFO(...)         ::MATD::CORE::Log::AddAppLogInfo(__VA_ARGS__)
#define MATD_WARN(...)         ::MATD::CORE::Log::AddAppLogWarn(__VA_ARGS__)
#define MATD_ERROR(...)        ::MATD::CORE::Log::AddAppLogError(__VA_ARGS__)
#define MATD_FATAL(...)        ::MATD::CORE::Log::AddAppLogFatal(__VA_ARGS__)