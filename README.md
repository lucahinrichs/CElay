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

```
CElay/
├── Source/
│   ├── PluginProcessor.h / .cpp   # Audio processing logic & buffer management
│   └── PluginEditor.h / .cpp      # GUI layout & control attachments
├── Builds/                        # IDE / Build system exported projects
├── CElay.jucer                    # Projucer configuration file
└── CMakeLists.txt                 # CMake build script
```

---

## Building the Plugin

1. Clone the repository:
   git clone [https://github.com/lucahinrichs/CElay.git](https://github.com/lucahinrichs/CElay.git)
2. Open CElay.jucer in Projucer and export to your preferred IDE (Xcode / Visual Studio).
3. Build the target as a VST3 or Standalone application.

---

## Roadmap / Planned Features

- [x] Basic delay line with circular buffer logic
- [x] Dry/Wet parameter control with GUI attachment
- [ ] Parameter smoothing (juce::SmoothedValue) to eliminate modulation artifacts
- [ ] High-pass / Low-pass filters in the feedback loop
- [ ] Custom LookAndFeel UI redesign
