# Contributing to Eco Guardian

We welcome contributions from embedded hardware engineers, data scientists, civic technologists, and open-source contributors! 

Eco Guardian is dedicated to open, reproducible civic sensing and environmental purification technology.

---

## Areas Where You Can Contribute

1. **Embedded Firmware (`/firmware`)**:
   - ESP-IDF and FreeRTOS optimizations.
   - Low-power deep-sleep scheduling and MPPT telemetry.
   - TinyML edge neural network optimization for gas and particulate anomaly detection.
2. **Municipal Web Platform (`/web`)**:
   - Enhancements to the real-time Leaflet / Mapbox GIS dashboard.
   - PWD work-order ticketing integrations (REST, MQTT, WebSockets).
   - DPDT compliance audit tools and telemetry validation scripts.
3. **Hardware & Mechanical Design (`/docs`)**:
   - CAD models (STL, STEP) for 3D printable brackets and misting nozzle ducts.
   - Alternative indigenous natural composite recipes (jute, hemp, coir).
   - Rainwater harvesting and hydrophobic coating optimizations.

---

## Development Workflow

1. **Fork the Repository**: Create a personal fork on GitHub.
2. **Create a Feature Branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Firmware Guidelines**:
   - Target Microcontroller: ESP32-S3 (Xtensa Dual-Core).
   - Use non-blocking timers (`millis()` or FreeRTOS task delays). Never use long blocking `delay()` calls on Core 1.
   - Ensure all analog reads use multi-sample averaging to suppress optical noise.
4. **Submit a Pull Request**:
   - Provide a clear summary of your changes.
   - Include test chamber data or serial monitor logs if modifying sensor physics or actuation routines.

---

## Code of Conduct

Please review our [Code of Conduct](CODE_OF_CONDUCT.md). We are committed to providing a welcoming, inclusive, and harassment-free community.
