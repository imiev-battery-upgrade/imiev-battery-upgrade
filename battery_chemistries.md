# Battery Chemistry Options for i-MiEV Upgrade

## NMC (Nickel Manganese Cobalt) Cells - Currently Preferred Option

- Most viable direct replacement option
- Used successfully by several forum members (e.g. piev)
- Examples: CATL 93Ah cells
- Matches original voltage range (charges to 4.1V)
- Requires CAN bridge to utilize full capacity
- Higher energy density than LFP
- More temperature sensitive than LFP, especially when charging in cold weather
- Main downside is they are more volatile/less stable than LFP

### CATL 93Ah Cells

- Dimensions: 172mm x 42mm x 90mm (very close to original LEV50)
- Approximately 87Ah capacity within i-MiEV voltage range (4.1V-3.3V)
- Successfully used in several i-MiEV upgrades

### SVOLT NMC-90F Cells

- Emerging alternative to CATL cells
- Dimensions: 148mm x 39mm x 102mm (shorter but taller than LEV50)
- Tested capacity: 68.5-71Ah at 30A load within i-MiEV voltage range (4.1V-3.3V)
- Requires custom mounting solution due to height difference
- Maximum continuous charge rate: 0.3C (27A) - may require CHAdeMO current limiting
- Maximum pulse charge rate: 1C (90A) - suitable for regenerative braking
- Custom tab welding and compression mounting recommended
- Forum members working on 4S block designs and custom mounting solutions
- Approximate cost: $25 per cell (as of early 2025)

### ⚠️ Cold Weather Operation Warning

NMC cells will be permanently damaged if charged (including regenerative braking) below 0°C (32°F).

**Mitigation Strategies:**

1. **For Regenerative Braking:**
   - A temporary solution is to set SoC to 100% while lowest reported cell temperature is below 5°C, as regen is disabled at high SoC
   - Drive for a few minutes to warm up cells before enabling normal SoC reporting

2. **For Charging:**
   - Drive the vehicle for several minutes before plugging in to charge (using heater/AC/blower can help warm the battery)
   - For home charging, consider modifying your EVSE to only activate the pilot signal above freezing temperatures
   - Install battery heating system (if feasible)

## LFP (Lithium Iron Phosphate) Cells - Challenging to Implement

- More stable/safer chemistry
- Much longer cycle life
- Major challenges:
  - Different voltage range (3.65V max vs 4.1V for stock)
  - Would require BMU reprogramming or extensive CAN modifications
  - Lower energy density means less range
  - Yuasa LEV60F cells are physically too thick (55mm vs 44mm needed)
- Currently not practical without major system modifications

## Original LEV50/LEV61 (LMO - Lithium Manganese Oxide) Cells

- Direct plug-and-play replacement
- LEV61 offers 20% more capacity than LEV50
- Matches original voltage range and dimensions
- No CAN bridge needed
- Limited availability and likely expensive
- Lower energy density than NMC

## 18650 Cell Pack Conversion

Not recommended due to:

- Complex assembly required
- Charging/regen current limitations
- Thermal management issues
- Reliability concerns
- Safety risks from DIY pack assembly

## Current Recommendation

Based on proven success and reasonable compromises, NMC cells (like the CATL 93Ah) appear to be the most practical upgrade path when combined with a CAN bridge. SVOLT NMC-90F cells are an emerging alternative that may offer a viable option with custom mounting solutions. While LFP would offer some advantages, the voltage and physical compatibility issues make it impractical without major system modifications.
