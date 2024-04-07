## Water Quality Monitoring System

This project monitors water quality parameters (temperature, TDS, and pH) using an ESP32 microcontroller and displays the data on a web interface.

### Features

* Collects data from temperature, TDS, and pH sensors connected to the ESP32.
* Transmits sensor data to a Node.js server over a serial connection.
* Processes received data on the Node.js server.
* Serves a real-time web page displaying the latest sensor readings.
* Provides a JSON endpoint (`/naman`) to access sensor data in JSON format.

### Hardware and Software

* ESP32 microcontroller
* Temperature sensor (e.g., DHT sensor)
* TDS sensor (e.g., analog TDS sensor)
* pH sensor (e.g., analog pH sensor)
* Jumper wires
* Breadboard (optional)
* Node.js and npm (Node Package Manager)

### Setting Up

1. **Install Node.js and npm:** Download and install Node.js from the official website ([https://nodejs.org/en](https://nodejs.org/en)). This will also install npm.

2. **Install dependencies:** Open a terminal in the project directory and run:

   ```bash
   npm install express serialport socket.io

3. **Connect sensors:** Refer to your sensor datasheets for specific wiring instructions. Connect the sensors to the ESP32 according to their power, ground, and signal pins.

4. **Configure ESP32 code:**  In the Arduino IDE, replace (`COM5`) in the (`SerialPort`) constructor with the actual COM port your ESP32 is connected to. You might need to modify the sensor libraries and data reading functions depending on your specific sensors.

5. **Run the Node.js server:** Open a terminal in the project directory and run:

   ```bash
   node server.js  // Replace 'server.js' with your actual Node.js script filename

### Using the System

* Open a web browser and navigate to (`http://localhost:3000`) to view the water quality data in a web page.
* The page will display the latest temperature, TDS, and pH readings in real-time.
* You can also access the sensor data in JSON format by navigating to (`http://localhost:3000/naman`)