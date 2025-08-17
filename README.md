# 🥤 Cola Machine – Automated Vending System

## 🔹 Project Overview

The **Cola Machine** is an automated vending machine prototype designed to dispense **7 different types of drinks**.
It uses a **20x4 LCD with I2C module** for the user interface, **7 relays** for motor/pump control, and a **stepper motor with A4988 driver** for mechanical dispensing.

Powered by a **12V power supply**, the system integrates **multiple motors and actuators** to control drink selection and dispensing.

---

## 🛠️ Hardware Components

### 📟 User Interface

* **20x4 LCD with I2C Module** – Displays drink menu and status.
* **Push Buttons / Keypad** – Used to select drinks (7 options).

### ⚡ Power & Control

* **12V Power Supply** – Provides main power.
* **Arduino Uno / Mega / ESP32** – Main controller.
* **7 Relays** – Switch and control the drink dispensing motors.
* **7 DC Motors / Pumps** – Each motor corresponds to one drink type.
* **Stepper Motor (NEMA 17)** – Handles mechanical dispensing mechanism.
* **A4988 Stepper Driver Module** – Controls the stepper motor.

### 🧩 Optional

* **Coin Acceptor / RFID module** – For payment system.
* **Buzzer** – Feedback when drink is selected or error occurs.

---

## 💻 Software Requirements

### 🔹 Microcontroller Code (Arduino)

* Controls LCD interface (menu navigation).
* Reads user input (buttons/keypad).
* Activates relays to run selected drink motor.
* Controls stepper motor via A4988 driver for dispensing.
* Manages timing and safety (e.g., prevent multiple motors at once).

Libraries Used:

* `LiquidCrystal_I2C.h` – for 20x4 LCD display.
* `AccelStepper.h` – for stepper motor with A4988 driver.
* `Wire.h` – for I2C communication.

---

## ⚙️ System Workflow

1. **Menu Display**

   * LCD shows 7 available drink options.
   * User selects a drink using buttons/keypad.

2. **Drink Selection**

   * Arduino checks input and confirms selection.
   * Corresponding **relay** activates the motor/pump for the chosen drink.

3. **Dispensing Mechanism**

   * **Stepper motor (via A4988 driver)** controls the mechanical gate/dispenser.
   * Ensures correct amount of liquid is released.

4. **Completion**

   * LCD displays *“Drink Ready”*.
   * System resets and waits for next input.

---

## 🌟 Features

* ✅ **7 different drink options**.
* ✅ **LCD 20x4 with I2C** for easy user interface.
* ✅ **Stepper motor control** for precise dispensing.
* ✅ **Relay-based motor switching** for drink selection.
* ✅ Powered by **12V supply** for reliability.
* ✅ Modular design – can be expanded for more drinks or payment integration.

---

## 🔮 Future Improvements

* Add **coin acceptor / RFID payment system**.
* Integrate with **mobile app** for remote ordering.
* Add **temperature control system** (cooling unit).
* Upgrade to **touchscreen display** instead of LCD + buttons.
* Smart portion control with **flow sensors**.

---

## 📂 Project Structure

```
├── Arduino/
│   └── cola_machine.ino       # Main Arduino code
├── Hardware/
│   └── circuit_diagram.jpg    # Wiring and schematic
├── Images/
│   └── demo_machine.jpg       # Prototype photos
├── README.md                  # Documentation
```

تحب أزودلك **جدول يوضح الـ 7 مشروبات مع كل ريلاي ومواتير مرتبطة بيها** عشان يكون أوضح في الـ README؟
