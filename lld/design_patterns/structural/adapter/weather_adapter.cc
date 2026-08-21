#include <iostream>
/*
Adapter Exercise #2 — Weather Service
You're building a weather application.
Your application expects this interface:
*/
class WeatherService {
public:
    virtual double GetTemperatureCelsius() = 0;
    virtual ~WeatherService() = default;
};

// Your existing application uses it like this:

void PrintTemperature(WeatherService& service) {
    std::cout << "Temperature: "
              << service.GetTemperatureCelsius()
              << " C\n";
}

// However, you need to integrate this old third-party class:

class LegacyWeatherAPI {
public:
    double GetTemperatureFahrenheit() {
        return 86.0;
    }
};

// You cannot modify either WeatherService or LegacyWeatherAPI.
// Your task
// Implement:

class LegacyWeatherAdapter : public WeatherService {
  LegacyWeatherAPI &legacy_weather_api;
  public:
  LegacyWeatherAdapter(LegacyWeatherAPI& legacy_api) : legacy_weather_api(legacy_api) {}
  double GetTemperatureCelsius() override {
    return ((legacy_weather_api.GetTemperatureFahrenheit() - 32.0)/9)*5;
  }
};

// So that this works:
int main() {
    LegacyWeatherAPI legacy_api;

    LegacyWeatherAdapter adapter(legacy_api);

    PrintTemperature(adapter);

    return 0;
}

/*
The expected output is:
Temperature: 30 C
Requirements
Your adapter must:
Implement the WeatherService interface.
Contain/use LegacyWeatherAPI.
Convert Fahrenheit → Celsius.
Use the formula:
Celsius = (Fahrenheit - 32) × 5 / 9
Don't modify either existing class.
Use composition, not multiple inheritance.
Think about the roles
Before coding, identify:
WeatherService       → ?
LegacyWeatherAPI     → ?
LegacyWeatherAdapter → ?
PrintTemperature     → ?
And most importantly, identify exactly where the conversion should happen.
Don't over-engineer it. You should only need a small adapter class.
*/