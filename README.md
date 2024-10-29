✈️ Flight Simulation System
A C++ program simulating real-time flight operations, including passenger management, flight statuses, and environmental factors like fuel consumption and weather conditions. The system provides an interactive console interface, allowing users to view specific details such as flight statuses, passenger information, and weather conditions for each airplane.

🌟 Features
Real-Time Flight Status Updates: Each airplane in the simulation goes through realistic status changes (Idle, Taking Off, In Flight, Landing, Landed, and Maintenance).
Passenger Management: Track individual passenger details such as ticket class and baggage weight.
Dynamic Fuel Consumption: Fuel levels decrease based on airplane speed, with low-fuel warnings and realistic distance tracking.
Weather Simulation: Random weather conditions affect flight delays, with "Clear," "Rainy," and "Stormy" scenarios.
Interactive Console: Control the simulation in real-time with keyboard commands to pause, resume, and display specific information.
🚀 Getting Started
Prerequisites
Ensure you have a C++ compiler installed on your system, such as GCC or MSVC.

Cloning the Repository
Clone this repository to your local machine:

bash
Copy code
git clone https://github.com/your-username/flight-simulation-system.git
cd flight-simulation-system
Building the Program
Open a terminal in the project directory.

Compile the code using a C++ compiler:

bash
Copy code
g++ -o flight_simulation flight_simulation.cpp -std=c++11
Run the program:

bash
Copy code
./flight_simulation
For Windows users, run the compiled .exe file instead:

bash
Copy code
flight_simulation.exe
🕹️ Usage
Interactive Controls
Key	Action
f	Show detailed flight status for all airplanes
s	Show passenger information for each airplane
w	Display current weather condition for flights
p	Pause/resume the simulation
e	Exit the simulation
Example Output
lua
Copy code
+----------+----------+--------+---------+--------------+--------+-------+--------+
| FlightID | Capacity | Fuel   | Speed   | Status       | Dist.  | ETA   | Status |
+----------+----------+--------+---------+--------------+--------+-------+--------+
| ZEDB234  | 20       | 74.35% | 675.0 km/h | In Flight | 50 km | 110 min | On Time |
| ZYB234   | 40       | 89.50% | 472.5 km/h | Taking Off| 15 km | 130 min | Delayed |
+----------+----------+--------+---------+--------------+--------+-------+--------+

Passenger Details for ZEDB234:
+------------+-----------+---------------+
| Passenger  | Class     | Baggage Weight|
+------------+-----------+---------------+
| Passenger1 | Economy   | 20.3 kg       |
| Passenger2 | Business  | 10.8 kg       |
+------------+-----------+---------------+
🛠️ Code Structure
Airplane class: Manages airplane properties, statuses, passenger data, and fuel consumption.
Passenger struct: Holds individual passenger details.
Weather and Delay Handling: handleDelays() function simulates random weather conditions impacting flight delays.
📂 File Overview
flight_simulation.cpp: Core simulation program file with main logic and interactive features.
📜 License
This project is licensed under the MIT License.

🤝 Contributing
Contributions, issues, and feature requests are welcome! Feel free to check the issues page for open issues or submit a new issue to discuss potential improvements.
