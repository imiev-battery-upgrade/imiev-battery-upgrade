# Mitsubishi i-MiEV Battery Upgrade

> [!NOTE]
> This is an unofficial guide created by community members. We are not affiliated with, endorsed by, or connected to Mitsubishi Motors Corporation in any way. "Mitsubishi" and "i-MiEV" are registered trademarks of Mitsubishi Motors Corporation. All trademarks are the property of their respective owners.

![i-MiEV](./miev.svg)

## Prerequisites

- [High-voltage safety requirements](https://web.archive.org/web/20241222211352/http://mmc-manuals.ru/manuals/i-miev/online/Service_Manual/2017/54/html/M154940710001501ENG.HTM):
  - Required protective equipment (must comply with national legal requirements):
    - Electric insulation helmet with shield/visor
    - Electric insulation jacket
    - Electric insulation trousers
    - Electric insulation gloves (properly sized)
    - Electric insulation boots
  - Safety procedures knowledge:
    - Understanding of high-voltage components (330V system):
      - Traction battery
    - Service plug safety:
      - Proper removal/installation procedure
      - 5-minute wait period after auxiliary battery disconnect
      - Proper use of insulation gloves
      - Verification of voltage discharge
    - High-voltage shutdown verification:
      - Use of high-voltage multimeter
      - Verification points and procedures
      - Expected voltage readings
    - Emergency procedures:
      - Actions when high voltage cannot be shut off
    - Connector handling:
      - Proper lock mechanism operation
      - Damage inspection procedures
      - Safe disconnection methods
- Required skills and experience:
  - Mechanical skills:
    - Ability to safely lift and support vehicles
    - Experience with automotive disassembly/reassembly
    - Competence with hand tools and power tools
    - Basic fabrication skills (if making custom bus bars)
  - Electrical skills:
    - Understanding of DC electrical systems and battery fundamentals
    - Experience with high voltage safety procedures
    - Ability to make proper electrical connections
    - Competence with multimeter usage and electrical measurements
    - Basic understanding of CAN bus systems
    - Ability to identify and prevent short circuits
- CAN bridge hardware options:
  - [Arduino Due](https://docs.arduino.cc/hardware/due/) or [CANFDuino](https://github.com/togglebit/CANFDuino) for CAN spoofing [US reseller](<https://copperhilltech.com/arduino/>)
  - STM32-based "MB CAN filter" board (~$8-10 on AliExpress) - see [Alternative CAN Bridge](#alternative-can-bridge-stm32) section
- proper tools:
  - Basic tools:
    - Socket set with ratchets and extensions
    - Wrenches (including ratcheting box wrench for pack removal)
    - Screwdrivers
    - Multimeter for voltage measurements
    - Paint pen or nail polish for marking polarity
  - Specialty tools:
    - Putty knife (for separating adhesive parts)
    - Dremel or rotary tool with deburring bit
    - Hacksaw (if fabricating bus bars)
    - Metal file or sandpaper for deburring
    - M3 x 0.5 tap (for jumper fabrication)
  - Safety equipment:
    - High voltage insulated gloves (properly sized)
    - Safety glasses
    - Insulated tools rated for high voltage work
  - Vehicle support:
    - Floor jack
    - Jack stands rated for vehicle weight
    - Dollies for battery pack (recommended: two 30" x 18" dollies with 1000lb+ capacity)
- workspace requirements:
  - Clean, dry, covered area with good lighting
  - Flat, level concrete floor for safe vehicle lifting
  - Sufficient space around vehicle (minimum 3ft on all sides) for pack removal
  - Workbench or table for module rebuilding
  - ESD-safe work surface for electronics
  - Good ventilation
  - Temperature controlled environment (important for NMC battery work)

## Materials

### Battery Cells

> [!WARNING]
> NMC cells will be permanently damaged if charged (including regenerative braking) below 0°C (32°F). See [battery_chemistries.md](battery_chemistries.md) for more details and mitigation strategies.

> [!TIP]
> When sourcing cells, carefully review the [battery terminal specifications](battery_terminals.md) to ensure compatibility and avoid common manufacturing issues.

- 88x (or 80x for post-2012 iOn/C-Zero) CATL NMC 93Ah cells
- Alibaba sources: [1](https://www.alibaba.com/product-detail/XIHO-CATL-3-7V-93Ah-SVOLT_1601370520376.html) [2](https://www.alibaba.com/product-detail/Starmax-High-Power-Catl-3-7V_1600752172388.html) [3](https://www.alibaba.com/product-detail/Brand-New-CATL-Ternary-Lithium-Ion_1600494889608.html) [4](https://www.xihobattery.com/products/catl-93ah-37v-nmc-prismatic-rechargeable-lithium-ion-battery) [5](https://www.alibaba.com/product-detail/subject_1600869468591.html)

### Hardware

- cork/felt/corrogated plastic spacers for cell height adjustment ([details](module_rebuild.md))
- bus bars and jumper materials, either machined or diy
  - machined
    - There seem to be too much variation in cells, so it's not recommended to use the machined bus bars.
  - diy (follow 5by8.net guide)
    - [https://www.amazon.com/gp/product/B0BBDTQVYP/](https://www.amazon.com/gp/product/B0BBDTQVYP/?tag=forumyield-20)
- CAN bridge hardware (choose one):
  - Arduino Due or CANFDuino with CAN shields
  - STM32F105-based "MB CAN filter" board from AliExpress (~$8-10)
- wiring and connectors for CAN bridge

### Step-by-step process​

## Battery Pack Removal  

Follow the detailed guide at [pack_removal.md](./pack_removal.md) .

## Module rebuilding

- Follow the detailed guide at [module_rebuild.md](./module_rebuild.md) .
- Key steps include:
  - disassembling modules
  - modifying plastic cell holders
  - installing new cells with proper spacing
  - making/installing bus bars and jumpers
  - reconnecting CMU boards

## CAN bridge setup  

### Arduino Due Method (Original)

- Install Arduino Due or CANFDuino
- Download latest code from [can_bridge.ino](can_bridge.ino)
- Connect to vehicle:
  - CAN0 to BMU pins 6 & 7
  - CAN1 to ECU
  - power from switched 12V

### Alternative CAN Bridge (STM32)

A more affordable alternative using STM32-based boards has been successfully tested by community members:

**Hardware:**
- STM32F105-based board marketed as "MB CAN filter" or similar on AliExpress (~$8-10)
  - Search terms: "filter CAN universal mercedes STM32F105"
  - Features dual CAN transceivers and STM32F105 microcontroller
  - More robust for automotive environment than Arduino
  - Lower power consumption and integrated transceivers

**Software:**
- Based on Dala's Nissan LEAF Battery Upgrade project: https://github.com/dalathegreat/Nissan-LEAF-Battery-Upgrade
- Community member iso14000 has successfully ported piev's Arduino code to STM32
- Sample code structure available at [can_bridge_stm32_sample.c](can_bridge_stm32_sample.c) - **WARNING: This is incomplete sample code only!**
- Requires modification to bypass UUID lock in original code (comment out NVIC_SystemReset)
- Compiled using Keil µVision or STM32CubeIDE

**Installation:**
- Power from EV-ECU control power source (C-107 pin 2) for key-switched operation
- Same CAN connections as Arduino method
- More compact installation due to smaller board size

**Advantages over Arduino Due:**
- Significantly lower cost (~$10 vs ~$50)
- More automotive-grade with better power regulation
- Smaller form factor
- Integrated CAN transceivers
- Lower power consumption

**Status:** Successfully tested and validated by forum member iso14000 (May 2025)

## Testing & validation  

- Check all connections and voltages.
- Verify CAN communication.
- Test drive and monitor performance.

## Important Notes

- Always follow proper [high voltage safety procedures](https://web.archive.org/web/20241222211352/http://mmc-manuals.ru/manuals/i-miev/online/Service_Manual/2017/54/html/M154940710001501ENG.HTM).
- Take time to properly balance cells before installation if there are any that have varying voltages connect in parallel for a few days. (TODO: add details)
- **WARNING**: NMC cells will be permanently damaged if charged (including regenerative braking) below 0°C (32°F). See [battery_chemistries.md](battery_chemistries.md) for more details and mitigation strategies.
- Always follow proper high voltage safety procedures.
- Take time to properly balance cells before installation if there are any that have varying voltages connect in parallel for a few days.
- Document original wiring and connections.
- The CAN bridge code is still being refined and improved.

## See also

- <https://openinverter.org/wiki/CAN_bus_with_Arduino_Due> : Arduino CAN basics
- <https://savvycan.com/> : FOSS CAN sniffing software
- <https://github.com/collin80/can_common> : FOSS can library
- <https://github.com/collin80/due_can> : FOSS C++ canbus library for Arduino Due compatible boards
- <https://myimiev.com/threads/main-traction-battery-upgrade-i-miev.5458/> : i-MiEV battery upgrade thread where this guide was created

## Special Thanks

- [jiminy](https://myimiev.com/members/jiminy.1606/) for bus bar design
- [piev](https://myimiev.com/members/piev.2638/) for code and starting the main thread this is based on
- [mradtke](https://myimiev.com/members/mradtke.1615/) and son Nicholas for creating the detailed pack removal and module rebuild instructions
- [toecheese](https://myimiev.com/members/toecheese.4279/) for context contributions to the repo
