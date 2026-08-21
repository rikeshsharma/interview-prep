#include <iostream>
// Target
class Logger {
public:
    virtual void Log(const std::string& message,
                     int level) = 0;

    virtual ~Logger() = default;
};
// The application expects:
// logger.Log("Download failed", 2);
// But the legacy library provides:
class LegacyLogger {
public:
    enum Severity {
        INFO,
        WARNING,
        ERROR
    };

    void Write(const char* message, Severity severity) {
        std::cout << "[" << severity << "] "
                  << message << '\n';
    }
};
/*
Your application uses levels:
0 → INFO
1 → WARNING
2 → ERROR
The legacy API uses:
INFO
WARNING
ERROR
Your task
Implement:
*/

class LegacyLoggerAdapter : public Logger {
    LegacyLogger& legacy_logger;
    int max_level = static_cast<int>(LegacyLogger::Severity::ERROR);
    public:
    LegacyLoggerAdapter(LegacyLogger& legacy) : legacy_logger(legacy) {}
    void Log(const std::string& message,
                     int level) override {
                      if(level < 0 || level > max_level) {
                        std::cout << "The severity level " << level << " not supported";
                        std::cout << "Max severity level " << max_level;
                        return;
                      }  
                      legacy_logger.Write(message.c_str(),
                                          static_cast<LegacyLogger::Severity>(level));
                     }
};

/*
It should adapt:
logger.Log("Download failed", 2);
into:
legacy_logger.Write("Download failed", LegacyLogger::ERROR);
Extra constraint
What should your adapter do if somebody calls:
logger.Log("Something happened", 7);
Think about that yourself. You need to decide how the adapter should handle an invalid level.
*/
