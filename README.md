# About

<img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/nature_people_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/water_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/antenna_FILL0_wght400_GRAD0_opsz48.svg" align="middle">

[Ler em Português](https://dirceu-jr.github.io/igapo/README.pt-BR)

I used to live in front of a [beautiful but polluted lake](https://pt.wikipedia.org/wiki/Ficheiro:Lago_Igap%C3%B3_Londrina.jpg) in _Londrina city_. Now I live in [Curitiba city](https://en.wikipedia.org/wiki/Curitiba), some say, _the most ecological Brazilian city_.

Urban socio-environmental problems identified in Curitiba includes air pollution, water pollution and environmental degradation ([references](#references)).

This project is developed with the objective of creating low-cost water monitoring stations, enabling the creation of a dense monitoring network with the capacity to locate occurrences of water pollution and contamination.

With community and educational purposes in mind, information about suppliers, configurations, and software are all open-source.

## Status

The current state of the project is hardware and software prototyping and testing. The first prototype (Igapó #1) was initially tested on the _Atuba River_, in a place known as [_Ecobarreira do Atuba_](https://www.instagram.com/ecobarreiradiegosaldanha/) and it is currently deployed at Igapó Lake 2 in Londrina city.

This is the prototype deployed at Igapó Lake 2:

<img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/igapo-2.jpg" width="340">

This is the prototype when deployed at Ecobarreira:

![IMG_20221220_165045](https://user-images.githubusercontent.com/20571/212798906-fd5728bf-b791-455d-8456-79cf07689e0c.jpg)

The prototype in greater detail:

<img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/1760993504025.jpg" width="340">

Inside the box:

<img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/1757982036064.jpg" width="340">

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with _ESP8266_). It has pH, ORP (Oxidation Reduction Potential) and Temperature probes and comes with Wi-Fi connectivity.

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img alt="Atlas Scientific Wi-Fi Pool Kit" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® T-SIM7000G](https://lilygo.cc/products/t-sim7000g). For cellular connectivity this low-power, low-cost board comes with Espressif's _ESP32_ microcontroller, SIMCom's 7000G cellular modem, battery holder and solar power circuit at around 300 Brazilian Reais.

<a target="_blank" href="https://lilygo.cc/products/t-sim7000g"><img alt="LILYGO® TTGO T-SIM7000G" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/lilygo-t-sim7000g.webp"></a>

- [LILYGO® T-A7670SA R2](https://lilygo.cc/products/t-sim-a7670e). Similar to T-SIM7000G but this one have Cat 1 protocol support, enabling future connection to Starlink's "Direct to Cell".

<a target="_blank" href="https://lilygo.cc/products/t-sim-a7670e"><img alt="LILYGO® T-A7670SA R2" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/LILYGO-T-SIMA7670E_18.jpg"></a>

## Future Work

Atlas Scientific has a broad range of probes, such as Conductivity and Dissolved Oxygen. Also, several other locations need to be monitored.

## References

- Danos Socioambientais Urbanos Em Curitiba: Uma Abordagem Geográfica ([PDF](https://github.com/dirceu-jr/igapo/blob/master/references/danos-socioambientais-urbanos-em-curitiba-uma-abordagem-geografica.pdf))

## Software

- [Embedded Software](https://github.com/dirceu-jr/igapo/tree/main/firmware)
- [ThingSpeak Channel](https://thingspeak.com/channels/1956479/)

## Suppliers

- [Atlas Scientific](https://atlas-scientific.com/)
- [Espressif](https://www.espressif.com/)
- [LILYGO](https://lilygo.cc/)

## Real-Time Data

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/1?title=pH&width=1&height=1"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/2?title=ORP+(mV)&width=1&height=1"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/3?title=Temperatura+(C)&width=1&height=1"></iframe>
