# CElay - Audio Delay Plugin

A custom C++ / JUCE audio effect plugin implementing a digital delay with custom parameter control.

> **Status:** Practice Project - Work in Progress


<img width="494" height="296" alt="Bildschirmfoto 2026-10-11 um 15 41 48" src="https://github.com/user-attachments/assets/732863b4-6cd9-497b-8b28-4c9b6acfe925" />


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

## Project Structure

```text
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
   ```bash
   git clone [https://github.com/lucahinrichs/CElay.git](https://github.com/lucahinrichs/CElay.git)
   ```
2. Open `CElay.jucer` in **Projucer** and export to your preferred IDE (Xcode / Visual Studio).
3. Build the target as a **VST3** or **Standalone** application.

---

## Roadmap / Planned Features

- [x] Basic delay line with circular buffer logic
- [x] Dry/Wet parameter control with GUI attachment
- [x] Pre-FX Drive stage (`std::tanh` soft-clipping)
- [ ] Tempo / Beat Sync (BPM-based delay divisions)
- [ ] Parameter smoothing (`juce::SmoothedValue`) to eliminate modulation artifacts
- [ ] High-pass / Low-pass filters in the feedback loop
- [ ] Custom LookAndFeel UI redesign
