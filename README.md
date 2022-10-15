# Ambient Water Quality

<img src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/water_FILL0_wght400_GRAD0_opsz48"> Water Pollution Detection and Localization.

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with ESP8266). It has pH, ORP and Temperature probes but only provides Wi-Fi connectivity.

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img alt="Atlas Scientific Wi-Fi Pool Kit" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html). Battery holder and solar panel charging circuit. It can provide power to Wi-Fi Pool Kit.

<a target="_blank" href="https://pt.aliexpress.com/item/4001156737871.html"><img alt="LILYGO® TTGO T-BAT Battery Holder" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/lilygo-ttgo-t-bat.webp"></a>

- [LILYGO® TTGO T-SIM7000G](https://pt.aliexpress.com/item/4000542688096.html). This low-power, low-cost board comes with ESP32 microcontroller, SIMCom 7000G IoT modem, battery holder and solar power circuit at around 200 Brazilian reais. ESP32 is more capable than Arduino and less expensive than Raspberry Pi.

<a target="_blank" href="https://pt.aliexpress.com/item/4000542688096.html"><img alt="LILYGO® TTGO T-SIM7000G" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/lilygo-t-sim7000g.webp"></a>

## References
- Danos Socioambientais Urbanos Em Curitiba: Uma Abordagem Geográfica ([PDF](https://github.com/dirceu-jr/ambient-water-quality/blob/master/references/danos-socioambientais-urbanos-em-curitiba-uma-abordagem-geografica.pdf))

## Software

- [Dashboard Prototype](https://dirceu-jr.github.io/ambient-water-quality/dashboard/)
- [Firmware](https://github.com/dirceu-jr/ambient-water-quality/blob/master/firmware/legacy_pool_kit.ino)
- [Thingspeak Channel](https://thingspeak.com/channels/1643222/)

## Real-time Data

<iframe width="450" height="260" src="https://thingspeak.com/channels/1643222/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=pH&type=line"></iframe>

<iframe width="450" height="260" src="https://thingspeak.com/channels/1643222/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=ORP&type=line"></iframe>

<iframe width="450" height="260" src="https://thingspeak.com/channels/1643222/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temp&type=line"></iframe>
