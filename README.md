# CElay - Audio Delay Plugin

A custom C++ / JUCE audio effect plugin implementing a digital delay with custom parameter control.

> **Status:** Practice Project - Work in Progress

---

## Key Features

* **Core DSP Delay Buffer:** Efficient circular buffer implementation for dynamic delay processing.
* **Pre-FX Drive Stage:** Integrated soft-clipping overdrive (`std::tanh`) feeding directly into the delay buffer.
* **Custom GUI:** Clean interface with parameter attachments for Time, Feedback, Mix, Drive, and Drive Toggle.

---

## Tech Stack & Architecture

* **Language:** C++17 / C++20
* **Framework:** JUCE
* **Build Systems:** Projucer (`.jucer`), CMake
* **Target Platforms:** macOS (VST3 / Standalone / AU)

---

## Author

* **Luca Hinrichs** - [GitHub Profile](https://github.com/lucahinrichs)
