# CElay - Audio Delay Plugin

A custom C++ / JUCE audio effect plugin implementing a digital delay with custom parameter control.

> **Status:** Practice Project - Work in Progress


<img width="494" height="290" alt="Bildschirmfoto 2026-10-11 um 17 23 38" src="https://github.com/user-attachments/assets/b910bbb0-7a94-4112-a8fc-af00c07c051b" />


---

## Key Features

* **Core DSP Delay Buffer:** Efficient circular buffer implementation for dynamic delay processing.
* **DAW Tempo Synchronization:** Integrated `getPlayHead()` processing to dynamically lock delay times to host BPM with selectable subdivisions (`1/16`, `1/8`, `1/4`, `1/2`, `1/1`).
* **Pre-FX Drive Stage:** Integrated soft-clipping overdrive (`std::tanh`) feeding directly into the delay buffer.
* **Context-Aware GUI:** Responsive controls that automatically enable/disable depending on Sync state, aligned layout, and a custom cyan-to-dark-teal background gradient.

---

## Tech Stack & Architecture

* **Language:** C++
* **Framework:** JUCE
* **Build Systems:** Projucer (`.jucer`), CMake
* **Target Platforms:** macOS (VST3 / Standalone / AU)

---

## Project Structure

```text
CElay/
├── Source/
│   ├── PluginProcessor.h / .cpp   # Audio processing logic, APVTS & buffer management
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
- [x] Tempo / Beat Sync (BPM-based delay divisions)
- [ ] Parameter smoothing (`juce::SmoothedValue`) to eliminate modulation artifacts
- [ ] High-pass / Low-pass filters in the feedback loop
- [ ] Custom LookAndFeel UI redesign
