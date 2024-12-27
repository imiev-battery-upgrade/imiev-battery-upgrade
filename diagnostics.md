# i-MiEV Diagnostics

## Software

### ObDZero

- iMiev CAN diagnostics app (Android)
- [source](https://github.com/DavidCecil50/OBDZero)
- CATL 93 Ah cell upgraded battery packs supported (!)
- [manual](http://obdzero.dk/wp-content/uploads/2024/02/OBDZero-User-Manual-1.pdf)
- [Google play](https://play.google.com/store/apps/details?id=dc.local.electriccar)

### Car Scanner

- <https://www.carscanner.info/>
- [Google play](https://play.google.com/store/apps/details?id=com.ovz.carscanner)
- basic version: free
- pro version: paid
- DTC: read, delete

### Canion

- closed source
- unmaintained
- <https://canion.en.softonic.com/android?ex=RAMP-2639.2>
- <https://www.facebook.com/emobility.at>

### EVBatMon

### HobDrive

## Hardware

### Use Case Categories

1. **Basic Car Repair & Programming**
   - [Tactrix OpenPort 2.0](https://www.tactrix.com/index.php?option=com_virtuemart&page=shop.product_details&flypage=flypage.tpl&product_id=17&Itemid=53&redirected=1&Itemid=53)
     - [Clone](https://www.aliexpress.us/item/3256807605812486.html): <$20 (most cost-effective option)
       - Works with MUT3 SE software (requires registry hack for CAN)
       - Compatible with EvUtil for error codes and battery voltages
       - Works with kolyandex's software for BMU modifications
       - Linux driver available on GitHub
     - [Original](https://www.tactrix.com/index.php?option=com_virtuemart&page=shop.product_details&flypage=flypage.tpl&product_id=17&Itemid=53&redirected=1&Itemid=53): ~$200 (premium option)
   - Alternative: ACTIA PSA XS EVOLUTION
     - Clone: ~$80 (has restrictions, paid telecoding)
     - Original: $200-700 (used)

2. **Real-time Phone Monitoring**
   - [OBDlink LX adapter](https://www.obdlink.com/products/obdlink-lx/)
     - Optimized for Android apps
     - Special STN chipset functionality
     - Current standard for Bluetooth support

3. **Smart Systems Integration**
   - [OVMS v3](https://docs.openvehicles.com/en/latest/introduction.html)
     - Built-in vehicle installation
     - LTE+GPS tracking
     - Remote control capabilities
   - [MeatPI WiCAN](https://www.meatpi.com/products/wican)
     - Home Assistant integration
     - Solar system charging integration
     - Open source

4. **Open Source Development**
   - [MeatPI WiCAN Pro](https://www.crowdsupply.com/meatpi-electronics/wican-pro) (upcoming)
     - Dedicated car communication chipset
     - STM functionality emulation
     - OpenPort 2.0 PassThru compatibility
     - LTE+GPS support for OVMS
     - Built-in Bluetooth LE
   - [OBDLink SX](https://www.obdlink.com/products/obdlink-sx/)
     - Original product
     - Linux CAN logging support

## See also

- [forum thread about software](https://myimiev.com/threads/smartphone-tablet-apps-for-i-miev-c-zero-and-ion.4936/)
- [forum thread about hardware](https://myimiev.com/threads/overview-of-the-current-obd2-adapters-their-functionality-and-the-future.5719/)
