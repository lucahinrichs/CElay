# CElay - Audio Delay Plugin

A custom C++ / JUCE audio effect plugin implementing a digital delay with custom parameter control.

> **Status:** Practice Project - Work in Progress


<img width="391" height="293" alt="CElay - GUI" src="https://github.com/user-attachments/assets/1c7ea80d-bef4-4a39-8b8e-c6d3606ca750" />


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
