# About

<img src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/water_FILL0_wght400_GRAD0_opsz48.svg" align="middle">

[Ler em Português](https://dirceu-jr.github.io/ambient-water-quality/README.pt-BR)

I used to live in front a [beauty but polluted lake](https://pt.wikipedia.org/wiki/Ficheiro:Lago_Igap%C3%B3_Londrina.jpg). Now I live in [Curitiba city](https://en.wikipedia.org/wiki/Curitiba), some say _the most ecological Brazilian city_.

I develop this project with the aim of implementing a monitoring network. It has also educational purposes.

The current state is the beginning of hardware and software prototyping.

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with _ESP8266_). It has pH, ORP (Oxidation Reduction Potential) and Temperature probes but only provides Wi-Fi connectivity.

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img alt="Atlas Scientific Wi-Fi Pool Kit" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html). Battery holder and solar panel charging circuit. It can provide power to _Wi-Fi Pool Kit_.

<a target="_blank" href="https://pt.aliexpress.com/item/4001156737871.html"><img alt="LILYGO® TTGO T-BAT Battery Holder" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/lilygo-ttgo-t-bat.webp"></a>

## WIP

Some locations where it would be good to have monitoring stations don't have Wi-Fi access point. So cellular or even satellite connectivity are necessary options.

- [LILYGO® TTGO T-SIM7000G](https://pt.aliexpress.com/item/4000542688096.html). This low-power, low-cost board comes with Espressif's _ESP32_ microcontroller, SIMCom's 7000G cellular modem, battery holder and solar power circuit at around 200 Brazilian reais. _ESP32_ is more capable than _Arduino_ and less expensive than _Raspberry Pi_. It could provide cellular connectivity to Atlas Scientific probes.

<a target="_blank" href="https://pt.aliexpress.com/item/4000542688096.html"><img alt="LILYGO® TTGO T-SIM7000G" width="260" src="https://raw.githubusercontent.com/dirceu-jr/ambient-water-quality/master/readme_files/lilygo-t-sim7000g.webp"></a>

## References

- Danos Socioambientais Urbanos Em Curitiba: Uma Abordagem Geográfica ([PDF](https://github.com/dirceu-jr/ambient-water-quality/blob/master/references/danos-socioambientais-urbanos-em-curitiba-uma-abordagem-geografica.pdf))

## Software

- [Embedded software](https://github.com/dirceu-jr/ambient-water-quality/blob/master/firmware/legacy_pool_kit.ino)
- [ThingSpeak Channel](https://thingspeak.com/channels/1956479/)
- [Dashboard Prototype](https://dirceu-jr.github.io/ambient-water-quality/dashboard/)

## Suppliers

For educational purposes...

- [Atlas Scientific](https://atlas-scientific.com/)
- [Espressif](https://www.espressif.com/)
- [LILYGO](https://pt.aliexpress.com/store/2090076)
- [Swarm](https://swarm.space/)

## Real-time Data

<iframe width="450" height="260" src="https://thingspeak.com/channels/1956479/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=pH&type=line"></iframe>

<iframe width="450" height="260" src="https://thingspeak.com/channels/1956479/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=ORP&type=line"></iframe>

<iframe width="450" height="260" src="https://thingspeak.com/channels/1956479/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temp&type=line"></iframe>
