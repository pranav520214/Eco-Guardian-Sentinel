# 🛠️ Eco Guardian: Hardware Fabrication & Mechanical Engineering

> ### या ओषधीः पूर्वा जाता देवेभ्यस्त्रियुगं पुरा ।<br/>मनै नु बभ्रूणामहं शतं धामानि सप्त च ॥
> *yā oṣadhīḥ pūrvā jātā devebhyastriyugaṁ purā |<br/>manai nu babhrūṇāmahaṁ śataṁ dhāmāni sapta ca ||*
> 
> — **ऋग्वेद (Rigveda 10.97.1, Oshadhi Sukta)**
> 
> *"The sacred plants and herbs that were born long before the gods, through three ancient ages—I contemplate their hundred and seven divine healing powers to protect and restore wholeness."*

---

## 1. Sustainable Materials: Indigenous Golden Jute Composite

Traditional industrial street equipment relies on non-biodegradable petroleum-derived plastics (ABS, PVC) or heavy steel enclosures prone to rust and high thermal absorption in direct sunlight. 

Eco Guardian utilizes **natural Indian golden jute composite**—leveraging India's position as the world's leading jute producer to create an indigenous, circular-economy enclosure:

```
[Raw Woven Jute Fabric] ──> [Alkali Treatment] ──> [Bio-Epoxy Resin Infusion] ──> [Bio-Wax Sealing] ──> [IP65 Weatherproof Chassis]
```

### 1.1 Chemical Treatment & Weatherproofing Process
1. **Fiber Preparation & Alkali Washing**: Raw woven jute fabrics are washed in a 2% Sodium Hydroxide ($\text{NaOH}$) solution for 30 minutes to strip natural hemicellulose and lignin, increasing fiber surface roughness and improving mechanical bonding with the polymer matrix.
2. **Matrix Infusion**: The treated jute layers (4-ply bidirectional weave) are laminated using a plant-based bio-epoxy resin derived from cashew nutshell liquid (CNSL) at a 60:40 fiber-to-resin ratio.
3. **Hydrophobic Wax Sealing**: The cured composite is coated with a hot-melt hydrophobic bio-wax (natural carnauba and beeswax blend). This establishes a high water contact angle ($\theta > 115^\circ$), ensuring rain droplets roll off immediately without fiber swelling.
4. **Thermal & Fire Retardancy**: Treated with ammonium polyphosphate (APP) mineral additives to prevent flammability and withstand direct summer sunlight up to $55^\circ\text{C}$.

---

## 2. Mechanical Enclosure & Dual-Chamber Isolation

```
+-------------------------------------------------------------------------+
|                  ECO GUARDIAN MECHANICAL CROSS-SECTION                  |
+-------------------------------------------------------------------------+
|                                                                         |
|            [ 10W Monocrystalline Solar Panel - 28° Tilt ]               |
|                                  |                                      |
|    +-----------------------------+-----------------------------+        |
|    |                                                           |        |
|    |   [Tower 1: Misting]                 [Tower 2: Filtration]|        |
|    |   • High-frequency transducer        • Dual Brushless Fan |        |
|    |   • Downward 45° angle               • Cyclonic Intake    |        |
|    |                                                           |        |
|    +-----------------------------------------------------------+        |
|                                  |                                      |
|    +-----------------------------+-----------------------------+        |
|    |  UPPER CHAMBER: Wet Cleansing & Mist Generation (Isolated)|        |
|    +-----------------------------------------------------------+        |
|    ==================== SILICONE GASKET SEAL ===================        |
|    +-----------------------------------------------------------+        |
|    |  LOWER CHAMBER: Dry Electronics & Power Storage           |        |
|    |  • Microprocessor Brain in IP65 Enclosure                 |        |
|    |  • 12.8V 6000mAh LiFePO4 Battery Buffer                   |        |
|    |  • MPPT Solar Charge Regulator                            |        |
|    |  • Front: SSD1306 OLED Telemetry Display                  |        |
|    |  • Front: Illuminated 24/7 Citizen SOS Panic Button       |        |
|    +-----------------------------------------------------------+        |
|                                                                         |
+-------------------------------------------------------------------------+
```

### Physical Specifications
- **Form Factor**: Cylindrical sentinel pole-mounting tower.
- **Dimensions**: Height $85\text{ cm} \times \text{Width } 28\text{ cm} \times \text{Depth } 22\text{ cm}$.
- **Weight**: $4.8\text{ kg}$ (including 12.8V battery and solar mounting brackets).
- **Mounting Mechanism**: Universal dual stainless-steel band clamps compatible with standard municipal street light poles ($60\text{ mm}$ to $120\text{ mm}$ outer diameter).
- **Dual-Chamber Isolation**: The upper misting and water-intake chamber is physically separated from the lower electronics chamber by an airtight silicone-gasket barrier to prevent internal condensation.

---

## 3. Bill of Materials (BOM) & Unit Economics

Below is the certified Bill of Materials for the bench-tested prototype alongside projected volume costs for a 30-node municipal pilot batch:

| Subsystem / Component | Manufacturer / Model | Qty | Prototype Cost (₹) | Batch Cost (30+ Units) (₹) |
| :--- | :--- | :---: | :---: | :---: |
| **Microprocessor Brain** | Dual-Core 240MHz Processor (8MB Flash) | 1 | ₹650 | ₹420 |
| **Optical Dust Sensor** | Sharp Optical Particle Sensor + Harness | 1 | ₹580 | ₹420 |
| **Hazardous Gas Array** | Multi-Gas VOC & Ammonia Detection Array | 1 | ₹350 | ₹240 |
| **Local Display** | 0.96" I2C SSD1306 OLED (128x64) | 1 | ₹280 | ₹190 |
| **Cellular / GPS Telemetry** | 4G LTE VoLTE / GPS Communication Board | 1 | ₹2,800 | ₹1,950 |
| **Ultrasonic Transducer** | High-Frequency Piezoelectric Misting Plate | 2 | ₹420 | ₹280 |
| **Airflow Blowers** | Dual 12V Brushless High-Flow Blower Fans | 2 | ₹480 | ₹340 |
| **Power Storage** | 12.8V 6000mAh LiFePO4 Battery Pack + BMS | 1 | ₹3,400 | ₹2,600 |
| **Solar Generation** | 10W 18V Monocrystalline PV Panel | 1 | ₹1,100 | ₹850 |
| **Charge Controller** | MPPT Solar Charge Board | 1 | ₹380 | ₹260 |
| **Citizen SOS Button** | IP67 Stainless Steel Illuminated 19mm Button | 1 | ₹320 | ₹220 |
| **Audio-Visual Strobe** | 100-Lumen LED Strobe Ring + 85dB Buzzer | 1 | ₹290 | ₹190 |
| **Jute Composite Enclosure** | Natural Indian Jute + Bio-Epoxy + Bio-Wax | 1 | ₹1,850 | ₹1,100 |
| **Wiring, Fasteners & Seals**| Silicone gaskets, SS304 screws, connectors | — | ₹950 | ₹540 |
| **Camera Module** | High-Definition Optical Edge Surface Sensor | 1 | ₹650 | ₹460 |
| **Assembly & Quality Testing**| Bench assembly, wiring loom, lab leak testing | — | ₹790 | ₹500 |
| **TOTAL UNIT BOM COST** | — | — | **₹15,000** | **₹10,560** |

---

## 4. Maintenance & Service Lifecycle

Eco Guardian is engineered for **minimal municipal operating overhead**:

1. **Water Reservoir Capacity**: Integrated 3.5-liter internal water reserve provides up to **14 days of misting operation** during severe pollution episodes. An internal float sensor alerts municipal crews via dashboard when water levels drop below 15%.
2. **Rainwater Harvesting Funnel**: The upper sloped housing incorporates a conical rainwater intake with a 50-micron stainless steel mesh filter, naturally replenishing the water reservoir during monsoon and winter rain events.
3. **Zero Filter Disposables**: Unlike HEPA filters that clog and require frequent ₹3,000 cartridge replacements, Eco Guardian uses a cleanable cyclonic dust trap and mist precipitation, eliminating ongoing consumable costs.
