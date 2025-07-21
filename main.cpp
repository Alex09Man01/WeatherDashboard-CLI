#include <iostream>
#include <string>
#include <cstdlib>

class WeatherDashboard {
private:
    std::string apiKey;
    std::string baseUrl;

public:
    WeatherDashboard() {
        apiKey = "41c656f69c3f4660bd5170549252107";
        baseUrl = "http://api.weatherapi.com/v1/current.json";
    }

    void displayWelcome() {
        std::cout << "=================================\n";
        std::cout << "    Weather Dashboard v1.0\n";
        std::cout << "=================================\n\n";
    }

    std::string makeHttpRequest(const std::string& url) {
        std::string command = "curl -s \"" + url + "\"";
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            std::cerr << "Error: Could not execute curl command\n";
            return "";
        }

        std::string result;
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }

        pclose(pipe);
        return result;
    }

    void getCurrentWeather(const std::string& city) {
        if(apiKey == "KEY_HERE") {
            std::cout << "Error: Please set your WeatherAPI key first!\n";
            std::cout << "Get one free at: https://www.weatherapi.com\n\n";
            return;
        }

        std::string url = baseUrl + "?key=" + apiKey + "&q=" + city + "&aqi=no";

        std::cout << "Getting weather for: " << city << "...\n";
        std::cout << "Request URL: " << url << "\n";

        std::string response = makeHttpRequest(url);

        if(!response.empty()) {
            std::cout << "Raw response:\n" << response << "\n\n";
        } else {
            std::cout << "Failed to get weather data!\n\n";
        }
    }

    void showMenu() {
        std::cout << "Options:\n";
        std::cout << "1. Get current weather\n";
        std::cout << "2. Exit\n";
        std::cout << "Choose option: ";
    }
};

int main() {
    WeatherDashboard dashboard;
    dashboard.displayWelcome();

    int choice;
    std::string city;

    do {
        dashboard.showMenu();
        std::cin >> choice;

        switch(choice) {
            case 1:
                std::cout << "Enter city name: ";
                std::cin.ignore(); 
                std::getline(std::cin, city);
                dashboard.getCurrentWeather(city);
                break;
            case 2:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option!\n\n";
        }

    } while(choice != 2);

    return 0;
}
