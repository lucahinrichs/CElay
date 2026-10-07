# CElay - Audio Delay Plugin

A custom C++ / JUCE audio effect plugin implementing a digital delay with custom parameter control.

> **Status:** Practice Project - Work in Progress


<img width="390" height="308" alt="Bildschirmfoto 2026-10-07 um 21 07 32" src="https://github.com/user-attachments/assets/40a20f56-66ca-446e-9f39-cccf8472ca7b" />


---

## Key Features

* **Core DSP Delay Buffer:** Efficient circular buffer implementation for dynamic delay processing.
* **Custom GUI:** User interface featuring a Dry/Wet mix slider connected to the DSP backend.

---

## Tech Stack & Architecture

* **Language:** C++17 / C++20
* **Framework:** JUCE
* **Build Systems:** Projucer (`.jucer`), CMake
* **Target Platforms:** macOS (VST3 / Standalone / AU)

---

## Project Structure

```text
CElay/
├── Source/
│   ├── PluginProcessor.h / .cpp   # Audio processing logic & buffer management
│   └── PluginEditor.h / .cpp      # GUI layout & control attachments
├── Builds/                        # IDE / Build system exported projects
├── CElay.jucer                    # Projucer configuration file
└── CMakeLists.txt                 # CMake build script
