# Greenhouse Temperature Control Using ESP32 and PID

An embedded systems project focused on automated greenhouse temperature regulation using an ESP32, a DHT11 temperature sensor, and a PID controller to adjust fan speed through PWM.

Developed as an academic project for the Embedded Systems course, this project applies concepts of control theory, electronics, and embedded programming to a practical temperature regulation system.

## Overview

The objective of this project is to maintain the temperature inside a small greenhouse close to a desired setpoint, even when a continuous heat source is present.

An incandescent lamp provides heat, while a ventilation fan removes it. An ESP32 continuously reads temperature measurements from a DHT11 sensor and uses a PID controller to determine the appropriate fan intensity.

Unlike a simple on/off control strategy, PID-based regulation adjusts the fan output according to the measured temperature error, aiming to reduce oscillations and improve temperature stability.

## System Architecture

The system consists of the following components:

- **ESP32 DevKit:** Microcontroller responsible for sensor readings and control calculations.
- **DHT11:** Sensor used to measure the greenhouse temperature.
- **PID Controller:** Calculates the control response based on the difference between the measured temperature and the desired setpoint.
- **PWM-Controlled Fan:** Regulates airflow to remove heat from the greenhouse.
- **MOSFET:** Used to switch and control the fan's electrical load.
- **Incandescent Lamp:** Provides the heat source for the greenhouse.
- **Breadboard and Auxiliary Components:** Used to assemble the circuit.

## How It Works

The system operates through a continuous feedback loop:

1. **Temperature Measurement:** The ESP32 reads the current temperature from the DHT11 sensor.
2. **Error Calculation:** The measured temperature is compared with the desired setpoint.
3. **PID Processing:** The controller calculates the appropriate response based on the temperature error.
4. **Fan Speed Adjustment:** The controller output is used to adjust the fan speed through PWM.
5. **Serial Monitoring:** Measurement and control data are transmitted through the serial interface for graphical analysis.

When the temperature rises above the desired value, the controller increases the fan intensity to remove heat. This feedback process helps the system approach and maintain the target temperature.

## Why PID Control?

Thermal systems have significant inertia, meaning their temperature does not change immediately after heating or cooling begins.

A simple on/off controller may cause excessive temperature oscillations because the system continues responding even after the control output changes.

The PID controller combines three control terms:

- **Proportional (P):** Responds to the current temperature error.
- **Integral (I):** Accounts for accumulated error over time.
- **Derivative (D):** Responds to changes in the error.

Together, these terms help produce smoother control responses, reduce oscillations, and improve temperature stability.

## Experimental Results

The project included experiments to observe the greenhouse's heating, cooling, and temperature control behavior.

### Heating Test

- **Duration:** 151 minutes.
- **Observed behavior:** The greenhouse heated for approximately 149 minutes before the temperature began to decrease and the system's thermal behavior changed.

### Cooling Test

- **Duration:** 90 minutes.
- **Observed behavior:** The greenhouse cooled for approximately 69 minutes before reaching a stable temperature of 16.5 °C.

### Temperature Control Test

During the control experiment, the temperature remained within the following observed range:

| Measurement | Temperature |
|---|---:|
| Minimum | 29.5 °C |
| Maximum | 30.7 °C |
| Total variation | 1.2 °C |

These measurements indicate that the system maintained the temperature within a relatively narrow range during the reported control test.

*The results above are based on the experiments documented in the project presentation.*

## Technologies and Concepts

- **C/C++ and Arduino IDE:** Embedded programming environment.
- **ESP32:** Microcontroller platform.
- **DHT11:** Temperature sensing.
- **PID Control:** Feedback-based temperature regulation.
- **PWM (Pulse Width Modulation):** Fan speed control.
- **MOSFET:** Electronic load switching.
- **Serial Communication:** Data output and monitoring.
- **Embedded Systems:** Integration of firmware, sensors, and electronic hardware.

## Repository Contents

This repository contains the source code for the PID temperature control component of the greenhouse project.

The experimental results and system description are based on the academic project presentation. A complete technical report and detailed hardware assembly documentation are not currently included in the repository.

## Future Improvements

Potential improvements to the project include:

- Documenting the PID parameters and tuning process.
- Adding the greenhouse circuit diagram and component connections.
- Including temperature-versus-time graphs from the experiments.
- Documenting the PWM configuration and control output limits.
- Adding detailed firmware setup and execution instructions.
- Evaluating the controller under different setpoints and environmental conditions.
- Exploring additional sensors and environmental control functions.

## Academic Context

Developed as part of an **Embedded Systems course** at **IFPR — Instituto Federal do Paraná**.

**Project contributors:**
- Alexandre Aleixo
- Gabriel Padilha
- Loise Natalia
- Kawan Dias
- Salomão Gabriel

---

*Applying embedded programming, control theory, and electronics to automated greenhouse temperature regulation.*
