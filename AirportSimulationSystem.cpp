#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>
#include <conio.h>  // For _getch() in Visual Studio

using namespace std;

random_device rd;
mt19937 rng(rd());
uniform_real_distribution<double> speedDist(200, 900);
uniform_real_distribution<double> fuelConsumptionDist(0.1, 1.5);
uniform_int_distribution<int> statusChangeDist(1, 10);
uniform_int_distribution<int> delayDist(0, 5);  // Random delay generator
uniform_int_distribution<int> weatherDist(1, 10); // Random weather impact

// Enum for various statuses
enum class AirplaneStatus { IDLE, TAKING_OFF, IN_FLIGHT, LANDING, LANDED, MAINTENANCE };

// Passenger struct for detailed passenger information
struct Passenger {
    string name;
    string ticketClass;
    double baggageWeight;
};

// Airplane class
class Airplane {
private:
    string id;
    int capacity;
    double fuelLevel;
    double speed;
    AirplaneStatus status;
    int passengerCount;
    vector<Passenger> passengers;
    double totalDistance;       // Distance traveled
    int estimatedArrivalTime;   // In minutes, randomly assigned initially
    int timeInCurrentStatus;    // Time spent in the current status
    bool delayed;               // If the flight has been delayed
    string weatherCondition;    // Holds current weather condition

public:
    // Constructor to initialize airplane details
    Airplane(string id, int capacity, int passengers, int estArrival)
        : id(id), capacity(capacity), fuelLevel(100.0), speed(0.0), status(AirplaneStatus::IDLE),
        passengerCount(passengers), totalDistance(0), estimatedArrivalTime(estArrival),
        timeInCurrentStatus(0), delayed(false), weatherCondition("Clear") {
        populatePassengers(); // Initialize passengers upon creation
    }

    // Accessor functions
    string getID() const { return id; }
    double getFuelLevel() const { return fuelLevel; }
    double getSpeed() const { return speed; }
    AirplaneStatus getStatus() const { return status; }
    string getWeatherCondition() const { return weatherCondition; }  // Add this function

    // Function to populate passengers with random names and ticket classes
    void populatePassengers() {
        vector<string> ticketClasses = { "Economy", "Business", "First" };
        uniform_real_distribution<double> baggageDist(5.0, 50.0); // Baggage weight range in kg

        for (int i = 0; i < passengerCount; ++i) {
            passengers.push_back({ "Passenger" + to_string(i + 1),
                                   ticketClasses[rng() % 3],
                                   baggageDist(rng) });
        }
    }

    // Method to update the airplane's current status
    void updateStatus() {
        // Cycle through statuses to simulate realistic airplane lifecycle
        switch (status) {
        case AirplaneStatus::IDLE: status = AirplaneStatus::TAKING_OFF; break;
        case AirplaneStatus::TAKING_OFF: status = AirplaneStatus::IN_FLIGHT; break;
        case AirplaneStatus::IN_FLIGHT: status = AirplaneStatus::LANDING; break;
        case AirplaneStatus::LANDING: status = AirplaneStatus::LANDED; break;
        case AirplaneStatus::LANDED: status = AirplaneStatus::MAINTENANCE; break;
        case AirplaneStatus::MAINTENANCE: status = AirplaneStatus::IDLE; break;
        }
        timeInCurrentStatus = 0;  // Reset time in new status
        updateSpeed();            // Adjust speed based on status
    }

    // Method to update the airplane's speed based on current status
    void updateSpeed() {
        if (status == AirplaneStatus::IN_FLIGHT) {
            speed = speedDist(rng);
        }
        else if (status == AirplaneStatus::TAKING_OFF) {
            speed = speedDist(rng) * 0.7;
        }
        else if (status == AirplaneStatus::LANDING) {
            speed = speedDist(rng) * 0.5;
        }
        else {
            speed = 0.0;
        }
    }

    // Simulate fuel consumption based on speed and status
    void consumeFuel() {
        if (speed > 0) {
            fuelLevel -= fuelConsumptionDist(rng) * (speed / 900.0);
            if (fuelLevel < 0.0) fuelLevel = 0.0;
            totalDistance += speed / 60;  // Distance traveled in 1 minute
        }
    }

    // Handle potential delays with weather impacts
    void handleDelays() {
        int weatherImpact = weatherDist(rng);
        if (weatherImpact <= 2) {
            weatherCondition = "Stormy";
            delayed = true;
            estimatedArrivalTime += 10;  // Add a delay due to weather
        }
        else if (weatherImpact <= 5) {
            weatherCondition = "Rainy";
            delayed = delayDist(rng) == 1;
        }
        else {
            weatherCondition = "Clear";
            delayed = false;
        }
    }

    // Print airplane's current status
    void printStatus() const {
        cout << "| " << setw(8) << id
            << " | " << setw(8) << passengerCount
            << " | " << setw(6) << fixed << setprecision(2) << fuelLevel << "%"
            << " | " << setw(5) << fixed << setprecision(1) << speed << " km/h"
            << " | " << setw(12) << statusToString(status)
            << " | " << setw(5) << totalDistance << " km"
            << " | " << setw(5) << estimatedArrivalTime << " min"
            << " | " << (delayed ? "Delayed" : "On Time")
            << " | " << weatherCondition << " |" << endl;
    }

    // Print individual passenger details for a specific flight
    void printPassengerInfo() const {
        cout << "+------------+-----------+---------------+" << endl;
        cout << "| Passenger  | Class     | Baggage Weight|" << endl;
        cout << "+------------+-----------+---------------+" << endl;
        for (const auto& passenger : passengers) {
            cout << "| " << setw(10) << passenger.name
                << " | " << setw(9) << passenger.ticketClass
                << " | " << setw(12) << passenger.baggageWeight << " kg |" << endl;
        }
        cout << "+------------+-----------+---------------+" << endl;
    }

    // Utility to convert enum status to a string
    string statusToString(AirplaneStatus status) const {
        switch (status) {
        case AirplaneStatus::IDLE: return "Idle";
        case AirplaneStatus::TAKING_OFF: return "Taking Off";
        case AirplaneStatus::IN_FLIGHT: return "In Flight";
        case AirplaneStatus::LANDING: return "Landing";
        case AirplaneStatus::LANDED: return "Landed";
        case AirplaneStatus::MAINTENANCE: return "Maintenance";
        default: return "Unknown";
        }
    }
};

int main() {
    // Initialize airplanes
    vector<Airplane> airplanes = {
        Airplane("ZEDB234", 80, 20, 120),
        Airplane("ZYB234", 80, 40, 150),
        Airplane("ZFGB234", 80, 40, 180)
    };

    bool running = true, paused = false;

    // Main simulation loop
    while (running) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == 'p' || choice == 'P') paused = !paused;      // Pause/resume
            if (choice == 'e' || choice == 'E') running = false;       // Exit
            if (choice == 'f' || choice == 'F') {                      // Show flight details
                for (const auto& airplane : airplanes) {
                    airplane.printStatus();
                }
            }
            if (choice == 's' || choice == 'S') {                      // Show all passenger info
                for (const auto& airplane : airplanes) {
                    airplane.printPassengerInfo();
                }
            }
            if (choice == 'w' || choice == 'W') {                      // Show weather conditions
                for (const auto& airplane : airplanes) {
                    cout << "Flight " << airplane.getID() << " weather: " << airplane.getWeatherCondition() << endl;
                }
            }
        }

        // Main update loop when not paused
        if (!paused) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            // Print table header
            cout << "Hello, welcome to the Airport Simulation system " << endl;
            cout << "To pause or resume - press 'p', to exit - press 'e' ,to show flight details press 'f', to show weather - press 'w'." << endl;

            cout << "+----------+----------+---------+------------+--------------+-----------+----------+-----------+" << endl;
            cout << "| FlightID | Capacity | Fuel    | Speed      | Status       | Dist.     | ETA      | Status    |" << endl;
            cout << "+----------+----------+---------+------------+--------------+-----------+----------+-----------+" << endl;

            // Update and display each airplane's status
            for (auto& airplane : airplanes) {
                if (statusChangeDist(rng) <= 3) {
                    airplane.updateStatus();
                }

                airplane.consumeFuel();
                airplane.handleDelays();
                airplane.printStatus();
            }

            cout << "+----------+----------+--------+---------+--------------+--------+-------+--------+" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    return 0;
}
