# About

<img src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/nature_people_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/water_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/antenna_FILL0_wght400_GRAD0_opsz48.svg" align="middle">

[Ler em Português](https://dirceu-jr.github.io/ambient-water-quality/README.pt-BR)

I used to live in front of a [beautiful but polluted lake](https://pt.wikipedia.org/wiki/Ficheiro:Lago_Igap%C3%B3_Londrina.jpg) in _Londrina city_. Now I live in [Curitiba city](https://en.wikipedia.org/wiki/Curitiba), some say _the most ecological Brazilian city_.

Urban socio-environmental problems identified in Curitiba include air pollution, water pollution and environmental degradation.

I'm developing this project with the aim of creating a low cost water monitoring station, enabling the creation of a dense monitoring network with the capacity to locate occurrences of pollution.

With societal and educational purposes I'm being open about suppliers, configuration and software.

The current state of the project is the beginning of hardware and software prototyping. I am preparing a station and requesting authorization to start collecting data on the _Atuba River_.

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with _ESP8266_). It has pH, ORP (Oxidation Reduction Potential) and Temperature probes and comes with Wi-Fi connectivity.

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img alt="Atlas Scientific Wi-Fi Pool Kit" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html). Battery holder and solar panel charging circuit. It can provide power to _Wi-Fi Pool Kit_.

<a target="_blank" href="https://pt.aliexpress.com/item/4001156737871.html"><img alt="LILYGO® TTGO T-BAT Battery Holder" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/lilygo-ttgo-t-bat.webp"></a>

## Future Work

Some locations where it would be good to have monitoring stations don't have Wi-Fi access point. So cellular or even satellite connectivity are necessary.

- [LILYGO® TTGO T-SIM7000G](https://pt.aliexpress.com/item/4000542688096.html). For cellular connectivity this low-power, low-cost board comes with Espressif's _ESP32_ microcontroller, SIMCom's 7000G cellular modem, battery holder and solar power circuit at around 200 Brazilian Reais. _ESP32_ is more capable than _Arduino_ and less expensive than _Raspberry Pi_.

<a target="_blank" href="https://pt.aliexpress.com/item/4000542688096.html"><img alt="LILYGO® TTGO T-SIM7000G" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/lilygo-t-sim7000g.webp"></a>

As some locations have "water" so polluted that deteriorate any sensor, gas sensors may be used.

## References

- Danos Socioambientais Urbanos Em Curitiba: Uma Abordagem Geográfica ([PDF](https://github.com/dirceu-jr/ambient-water-quality/blob/master/references/danos-socioambientais-urbanos-em-curitiba-uma-abordagem-geografica.pdf))

## Software

- [Embedded Software](https://github.com/dirceu-jr/ambient-water-quality/blob/master/firmware/legacy_pool_kit.ino)
- [ThingSpeak Channel](https://thingspeak.com/channels/1956479/)
- [Dashboard Prototype](https://dirceu-jr.github.io/ambient-water-quality/dashboard/)

## Suppliers

- [Atlas Scientific](https://atlas-scientific.com/)
- [Espressif](https://www.espressif.com/)
- [LILYGO](https://pt.aliexpress.com/store/2090076)
- [Swarm](https://swarm.space/)

## Real-Time Data

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=pH&type=line&width=380"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=ORP&type=line&width=380"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temp&type=line&width=380"></iframe>
