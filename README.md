# About

<img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/nature_people_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/water_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/antenna_FILL0_wght400_GRAD0_opsz48.svg" align="middle">

[Ler em Português](https://dirceu-jr.github.io/igapo/README.pt-BR)

I used to live in front of a [beautiful but polluted lake](https://pt.wikipedia.org/wiki/Ficheiro:Lago_Igap%C3%B3_Londrina.jpg) in _Londrina city_. Now I live in [Curitiba city](https://en.wikipedia.org/wiki/Curitiba), some say _the most ecological Brazilian city_.

Urban socio-environmental problems identified in Curitiba includes air pollution, water pollution and environmental degradation ([references](#references)).

This project is developed with the objective of creating low-cost water monitoring stations, enabling the creation of a dense monitoring network with the capacity to locate occurrences of water pollution and contamination.

With community and educational purposes in mind, information about suppliers, configurations, and software are all open-source.

The current state of the project is hardware and software prototyping. A prototype was tested on the _Atuba River_, near a place known as [_Ecobarreira do Atuba_](https://www.instagram.com/ecobarreiradiegosaldanha/). It was "on" for 36 hours, but the battery died at the end of the night and it didn't turned back "on" when the sun recharged the battery.

The software has been improved to use the microcontroller's "deep sleep" mode and on the desk the battery lasted over 100 hours sending data every 6 minutes. Unfortunately it has a bad performance in the rain. Probably the Micro USB connection do not work well with water.

This is the prototype deployed:

![IMG_20221220_165045](https://user-images.githubusercontent.com/20571/212798906-fd5728bf-b791-455d-8456-79cf07689e0c.jpg)

This is the prototype in greater detail:

<img src="https://user-images.githubusercontent.com/20571/212799501-3fa20d3c-de6e-48f0-9699-e0ce9b30915b.jpg" width="340">

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with _ESP8266_). It has pH, ORP (Oxidation Reduction Potential) and Temperature probes and comes with Wi-Fi connectivity.

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img alt="Atlas Scientific Wi-Fi Pool Kit" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html). Battery holder and solar panel charging circuit. It can provide power to _Wi-Fi Pool Kit_.

<a target="_blank" href="https://pt.aliexpress.com/item/4001156737871.html"><img alt="LILYGO® TTGO T-BAT Battery Holder" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/lilygo-ttgo-t-bat.webp"></a>

- [iSNK Solar Panel](https://pt.aliexpress.com/store/3877081)

## Future Work

Some locations where it would be good to have monitoring stations don't have Wi-Fi access point. So cellular or even satellite connectivity are necessary.

- [LILYGO® TTGO T-SIM7000G](https://pt.aliexpress.com/item/4000542688096.html). For cellular connectivity this low-power, low-cost board comes with Espressif's _ESP32_ microcontroller, SIMCom's 7000G cellular modem, battery holder and solar power circuit at around 170 Brazilian Reais. _ESP32_ is more capable than _Arduino_ and less expensive than _Raspberry Pi_.

<a target="_blank" href="https://pt.aliexpress.com/item/4000542688096.html"><img alt="LILYGO® TTGO T-SIM7000G" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/lilygo-t-sim7000g.webp"></a>

As polluted or contaminated "water" can deteriorate the probes, requiring more robust (more expensive) hardware and greater maintenance labor, gas sensors can be used over the water course:

- [DFRobot gas sensors](https://www.dfrobot.com/search-gas%20sensor.html)
- [DS-HCHO-20 (formaldehyde)](https://aliexpress.com/item/10000027551761.html)
- [MQ 135 (toxic gases)](https://aliexpress.com/w/wholesale-MQ-135.html)

## References

- Danos Socioambientais Urbanos Em Curitiba: Uma Abordagem Geográfica ([PDF](https://github.com/dirceu-jr/igapo/blob/master/references/danos-socioambientais-urbanos-em-curitiba-uma-abordagem-geografica.pdf))

## Software

- [Embedded Software](https://github.com/dirceu-jr/igapo/blob/main/firmware/legacy_pool_kit/legacy_pool_kit.ino)
- [ThingSpeak Channel](https://thingspeak.com/channels/1956479/)
- [Dashboard Prototype](https://dirceu-jr.github.io/igapo/dashboard/)

## Suppliers

- [Atlas Scientific](https://atlas-scientific.com/)
- [Espressif](https://www.espressif.com/)
- [LILYGO](https://pt.aliexpress.com/store/2090076)

## Real-Time Data

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=pH&type=line&width=380"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=ORP&type=line&width=380"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temp&type=line&width=380"></iframe>
