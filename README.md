# Cloud-Enabled IoT Thermal Alert and Logging System

An embedded IoT project built on the **LPC2148 ARM7 microcontroller** that continuously monitors ambient temperature, logs data to the **ThingSpeak cloud**, and triggers local and remote alerts when a configurable thermal threshold is exceeded.

---

## Overview

This system bridges embedded hardware with cloud connectivity. The LM35 temperature sensor feeds real-time readings into the LPC2148, which processes the data, displays it on an LCD with an RTC timestamp, and pushes it to ThingSpeak over Wi-Fi (via ESP01). When the temperature crosses a user-defined set point, a buzzer fires locally and an alert is uploaded to a dedicated cloud field — all while the set point itself can be updated either physically through a keypad or remotely through the cloud.

---

## Features

- Real-time temperature monitoring using LM35 with ADC
- RTC-based timestamping on the LCD display
- Automatic cloud logging to ThingSpeak every 2 minutes
- Threshold-based alert: buzzer + cloud notification when overheating is detected
- Local set point update via 4×4 matrix keypad (triggered by external interrupt)
- Remote set point update from ThingSpeak cloud (polled at a defined interval)
- EEPROM persistence — set point survives power cycles
- Two independent ThingSpeak channels: one for temperature data, one for set point control

---

## Hardware Requirements

| Component | Purpose |
|---|---|
| LPC2148 (ARM7TDMI) | Main microcontroller |
| LM35 | Temperature sensor (analog, connected to ADC) |
| AT24C256 (EEPROM) | Non-volatile set point storage over I2C |
| ESP01 Wi-Fi Module | Cloud communication over UART |
| 16×2 LCD | Local display for temperature and status |
| 4×4 Matrix Keypad | Local set point entry |
| RTC (built-in LPC2148) | Timestamp for display |
| Buzzer / LED | Local alert output |
| Tactile Switch | External interrupt trigger for set point update |
| DB-9 / USB-UART Converter | Programming and serial debugging |

---

## Software Requirements

- Keil µVision IDE (ARM C compiler)
- Embedded C
- Flash Magic (for flashing `.hex` to LPC2148)

---

## Project Structure

```
MAJOR_PROJECT/
├── CLOUD_ENABLED_IOT_THERMAL_ALERT_AND_LOGGING_SYSTEM.c  # Main application logic
├── headers.h          # Global variables and all includes
├── init_devices.c/h   # Peripheral initialization
├── lm35.c/h           # Temperature reading via ADC
├── adc.c/h            # ADC driver
├── lcd.c/h            # LCD driver
├── kpm.c/h            # Keypad driver
├── uart.c/h           # UART driver (used for ESP01 communication)
├── esp01.c/h          # ESP01 Wi-Fi driver (ThingSpeak send/receive)
├── i2c_peripheral.c/h # I2C bus driver
├── i2c_eeprom.c/h     # EEPROM read/write (AT24C256)
├── rtc.c/h            # Real-Time Clock driver
├── alaram.c/h         # Buzzer/alert logic
├── EXT_Interrupt_Init.c/h  # External interrupt (switch) setup
├── defines.h          # Bit manipulation macros
├── delay.c/h          # Millisecond delay utilities
└── types.h            # Custom type definitions (u8, s8, f32, etc.)
```

---

## How It Works

### Startup
On power-up, all peripherals are initialized. The initial temperature set point is loaded from EEPROM address `0x0010` (or written there if first boot).

### Main Loop
Every iteration of the main loop:
1. Reads the current RTC time and displays it on the LCD
2. Reads temperature from the LM35 via ADC channel 1 (`degC = adcAVal * 100`)
3. Displays the temperature on the LCD

Every 2 minutes (tracked using RTC):
- Converts the float temperature to a string and sends it to ThingSpeak (Field 1)
- Reads the latest set point from the ThingSpeak set point channel and compares it against the EEPROM value — if different, the EEPROM is updated

### Alert Logic
If `temperature >= setpoint`:
- GPIO P0.16 goes HIGH → buzzer/LED activates
- Temperature value is pushed to the ThingSpeak alert field

### Local Set Point Update (Interrupt-Driven)
Pressing the hardware switch triggers an external interrupt. The ISR sets `isr_flag`. In the next main loop cycle:
- The new set point (entered via keypad) is written to ThingSpeak and saved to EEPROM
- `setpoint` variable is updated immediately

### Remote Set Point Update (Polled)
At each 2-minute interval, the system reads `channels/2308650/fields/1/last.txt` from ThingSpeak. If the value differs from the one in EEPROM, the EEPROM is overwritten and `setpoint` is updated. Values above 150.0 are treated as invalid and ignored.

---

## ThingSpeak Configuration

You need two ThingSpeak channels:

**Channel 1 — Temperature Monitoring**
- Field 1: Live temperature readings
- Write API key: update `esp01_sendToThingspeak()` in `esp01.c`

**Channel 2 — Set Point Control**
- Field 1: Desired temperature threshold (written remotely)
- Channel ID and Read API key: update `ReadSetpointFromESP_01()` in `esp01.c`

> Update the Wi-Fi credentials in `esp01_connectAP()` inside `esp01.c` before flashing.

---

## Getting Started

1. Clone or copy the project folder into Keil µVision
2. Update Wi-Fi SSID and password in `esp01.c`
3. Update ThingSpeak API keys for both channels in `esp01.c`
4. Build the project — resolve any missing header paths under Project > Options > C/C++ > Include Paths
5. Flash the generated `.hex` file to the LPC2148 using Flash Magic (UART0, 9600 baud or as configured)
6. Open the ThingSpeak channel dashboards to monitor live data

---

## Module Testing Order (Recommended)

If you're building this from scratch, test each module independently before integrating:

1. LCD — display characters, strings, integers
2. Keypad — read key values and show on LCD
3. UART interrupt — verify interrupt-driven receive with Flash Magic terminal
4. ADC / LM35 — read analog temperature and display on LCD
5. ESP01 — test AT commands via Flash Magic terminal, then send a constant value to ThingSpeak
6. ThingSpeak read — fetch a field value from cloud and display on LCD
7. EEPROM — write and read back N bytes, display on LCD
8. External interrupt — write a simple ISR and verify it fires on switch press
9. Integrate everything into the main application

---

## Pin Reference (Key Connections)

| Signal | LPC2148 Pin |
|---|---|
| LM35 output | AD0.1 (P0.28) |
| LCD (4-bit mode) | P1 (configured in `lcd_defines.h`) |
| Keypad rows/cols | P1 (configured in `kpm_defines.h`) |
| ESP01 TX/RX | UART1 (P0.8 / P0.9) |
| EEPROM SDA/SCL | I2C0 (P0.2 / P0.3) |
| Buzzer/LED | P0.16 |
| Interrupt switch | EINT (configured in `EXT_Interrupt_defines.h`) |

> Confirm exact pin assignments against your board's schematic and the respective `_defines.h` files.
