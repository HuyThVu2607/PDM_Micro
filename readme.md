# PDM Microphone Interface with MCU

This project demonstrates how to interface a **PDM microphone** with an **MCU** to capture and process audio data. The provided code includes basic examples of how to read microphone samples, apply filtering (low-pass, high-pass, band-pass), and transmit data using **SEGGER RTT** for debugging.

## Table of Contents

- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Project Setup](#project-setup)
- [File Descriptions](#file-descriptions)
- [Configuration](#configuration)
- [Usage](#usage)
- [License](#license)

## Introduction

This project is aimed at providing a starting point for using a **PDM microphone** with an **MCU**. It demonstrates basic microphone sampling, filtering techniques, and debugging using **SEGGER RTT**.

The system is based on the **Simplicity Studio IDE** and uses the **Simplicity SDK** to interface with the **EFR32xG22** or other compatible **Silicon Labs** boards.

## Prerequisites

Before using this project, make sure you have the following tools installed:

- **Simplicity Studio IDE**: Used for development and debugging.
- **Simplicity SDK**: Required libraries and drivers for the project (version 2025.6.2).
- **IAR Embedded Workbench** (Optional): For compilation if using IAR toolchain.
- **J-Link Debugger**: For debugging via SEGGER RTT.

Ensure you have the correct **Silicon Labs** development board (e.g., **BGM220** or **EFR32xG22**), as specified in the `mox_v1.slcp` configuration file.

## Project Setup

1. **Clone the Repository**:
    - Clone the project to your local machine:
      ```bash
      git clone https://github.com/your-username/PDM_Micro.git
      ```
2. **Open the Project in Simplicity Studio**:
    - Launch **Simplicity Studio** and open the cloned project directory.

3. **Install Dependencies**:
    - Ensure you have the **Simplicity SDK** (version 2025.6.2) installed and correctly configured in Simplicity Studio.

4. **Configure the MCU**:
    - Use the provided **.slcp** file (`mox_v1.slcp`) to configure the system clock, PDM microphone settings, and other peripheral configurations.

## File Descriptions

- **`sl_mic.c`**: Contains functions for initializing the microphone and handling PDM data.
- **`sl_mic.h`**: Header file defining constants and function declarations for the microphone driver.
- **`SEGGER_RTT.c` and `SEGGER_RTT.h`**: These files are used for transmitting debug data over RTT to a terminal.
- **`mox_v1.slcp`**: Configuration file for Simplicity Studio to set up system clock and peripheral configurations.
- **`main.c`**: Main application file that initializes the microphone, applies filters, and outputs debug information.
- **`readme.md`**: This documentation file.

## Configuration

### Microphone Configuration

To configure the microphone sampling rate or other parameters, you need to modify the settings in the **`mox_v1.slcp`** file.

1. Open the `mox_v1.slcp` file.
2. Search for the **"micro"** keyword to locate the section responsible for configuring the microphone.
3. Adjust the settings under **Platform → Board Driver → PDM Microphone** for your specific requirements.

The current configuration sets the microphone to a sampling rate of **8000 Hz** and uses **1 channel** (mono).

### Filter Configuration

The project includes basic digital filters:

- **Low-pass filter**: Applied to attenuate high-frequency noise.
- **High-pass filter**: Applied to remove low-frequency noise.
- **Band-pass filter**: A combination of low-pass and high-pass filters, allowing only a certain frequency range.

You can adjust the filter coefficients (`alpha` for low-pass and `alpha_hp` for high-pass) in the main application code (file: `main.c`).

## Usage

1. **Build the Project**:
    - Open the project in **Simplicity Studio** and build the project by selecting **Build** → **Build All**.
   
2. **Flash the Firmware**:
    - Connect the **J-Link Debugger** and flash the firmware onto the target device.

3. **Run the Application**:
    - After programming, the application will start capturing microphone data, applying filters, and transmitting the filtered data via **SEGGER RTT**.

4. **Monitor Output via RTT**:
    - Use the **SEGGER RTT Viewer** or any terminal that supports RTT to view the debug data from the microphone.

### Example Debug Output

Once the application is running, you can observe the debug output in the RTT viewer. The filtered microphone data will be printed to the terminal.

Example:
