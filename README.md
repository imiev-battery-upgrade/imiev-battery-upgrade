# Mitsubishi i-MiEV Battery Upgrade Guide

![i-MiEV](./miev.svg)

## Prerequisites:​

-   High-voltage safety knowledge and equipment
-   Basic mechanical and electrical skills
-   Arduino Due or CANFDuino for CAN spoofing [found here](https://copperhilltech.com/arduino/)
-   Proper tools and workspace ( i'd love to expand on this )

## Materials Needed:​

### Battery Cells:  

-   88x (or 80x for post-2012 iOn/C-Zero) NMC 93Ah cells with M8 terminals recommended
-   Available from vendors on Alibaba like:
    -   [https://www.alibaba.com/product-detail/Starmax-High-Power-Catl-3-7V\_1600752172388.html](https://www.alibaba.com/product-detail/Starmax-High-Power-Catl-3-7V_1600752172388.html)
    -   [https://www.alibaba.com/product-detail/Brand-New-CATL-Ternary-Lithium-Ion\_1600494889608.html](https://www.alibaba.com/product-detail/Brand-New-CATL-Ternary-Lithium-Ion_1600494889608.html)
    -   [https://www.xihobattery.com/products/catl-93ah-37v-nmc-prismatic-rechargeable-lithium-ion-battery](https://www.xihobattery.com/products/catl-93ah-37v-nmc-prismatic-rechargeable-lithium-ion-battery)
    -   [https://www.alibaba.com/product-detail/subject\_1600869468591.html](https://www.alibaba.com/product-detail/subject_1600869468591.html)

###Hardware:  

-   Cork/felt/corrogated plastic spacers for cell height adjustment (check [this](https://5by9.net/prune_batteries/module_rebuild.html) for details)
-   Bus bars and jumper materials
    -   machined (3.2mm thick 6061 aluminum without tapped holes from SendCutSend)
        -   76 x [https://www.printables.com/model/1036239-l-shape-bus-bar-for-1233mm-ctc-battery-cell](https://www.printables.com/model/1036239-l-shape-bus-bar-for-1233mm-ctc-battery-cell)
        -   24 x [https://www.printables.com/model/1036252-i-shape-bus-bar-for-1233mm-ctc-battery-cell-for-mi](https://www.printables.com/model/1036252-i-shape-bus-bar-for-1233mm-ctc-battery-cell-for-mi)
    -   diy (follow 5by8.net guide)
        -   [https://www.amazon.com/gp/product/B0BBDTQVYP/](https://www.amazon.com/gp/product/B0BBDTQVYP/?tag=forumyield-20)
-   Arduino Due or CANFDuino with CAN shields
-   Wiring and connectors for CAN bridge

### Step-by-Step Process:​

## Battery Pack Removal  

-   Follow detailed guide at: [https://5by9.net/prune\_batteries/pack\_removal.html](https://5by9.net/prune_batteries/pack_removal.html)

## Module Rebuilding  

-   Follow detailed guide at: [https://5by9.net/prune\_batteries/module\_rebuild.html](https://5by9.net/prune_batteries/module_rebuild.html)
-   Key steps include:
    -   Disassembling modules
    -   Modifying plastic cell holders
    -   Installing new cells with proper spacing
    -   Making/installing bus bars and jumpers
    -   Reconnecting CMU boards

## CAN Bridge Setup  

-   Install Arduino Due or CANFDuino
-   Download latest code from (github?)
-   Connect to vehicle:
    -   CAN0 to BMU pins 6 & 7
    -   CAN1 to ECU
    -   Power from switched 12V

## Testing & Validation  

-   Check all connections and voltages
-   Verify CAN communication
-   Test drive and monitor performance

## Important Notes

-   Always follow proper high voltage safety procedures
-   Take time to properly balance cells before installation if there are any that have varying voltages connect in parallel for a few days.
-   Document original wiring and connections
-   The CAN bridge code is still being refined and improved
-   Consider weather conditions as NMC cells are sensitive to charging/driving in freezing temperatures
