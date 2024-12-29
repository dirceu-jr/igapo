# Sobre

<img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/nature_people_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/water_FILL0_wght400_GRAD0_opsz48.svg" align="middle"> <img src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/antenna_FILL0_wght400_GRAD0_opsz48.svg" align="middle">

[Read in English](https://dirceu-jr.github.io/igapo/)

Eu morava na frente de um [lindo mas poluído lago](https://pt.wikipedia.org/wiki/Ficheiro:Lago_Igap%C3%B3_Londrina.jpg) na cidade de Londrina. Agora eu moro na [cidade de Curitiba](https://pt.wikipedia.org/wiki/Curitiba), alguns dizem _a cidade mais ecológica do Brasil_.

Os problemas socioambientais urbanos identificados em Curitiba incluem poluição do ar, poluição da água e degradação ambiental ([referências](#referências)).

Esse projeto é desenvolvido com o objetivo de criar estações de monitoramento de baixo custo, possibilitando a criação de uma rede densa com a capacidade de localizar ocorrencias de poluição e contaminação na água.

Com fins comunitários e educativos, informações sobre fornecedores, configurações e _software_ são de código aberto.

## Status

O estado atual do projeto é de prototipagem de _hardware_ e _software_. O protótipo foi testado no Rio Atuba, próximo a um lugar conhecido por [Ecobarreira do Atuba](https://www.instagram.com/ecobarreiradiegosaldanha/). Ele ficou ligado por 36 horas, a bateria acabou no final da noite e ele não religou quando o sol recarregou a bateria. 

O _software_ foi melhorado para usar o modo "sono profundo" do microcontrolador e na mesa a bateria durou mais de 100 horas enviando dados a cada 6 minutos. Infelizmente apresentou baixa performance na chuva. Provavelmente a conexão Micro USB não funciona bem com água. Um novo conector foi adquirido e será testado novamente.

Esse é o protótipo instalado:

![IMG_20221220_165045](https://user-images.githubusercontent.com/20571/212798906-fd5728bf-b791-455d-8456-79cf07689e0c.jpg)

Esse é o protótipo em maior detalhe:

<img src="https://user-images.githubusercontent.com/20571/212799501-3fa20d3c-de6e-48f0-9699-e0ce9b30915b.jpg" width="340">

## Hardware atual

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (_Legacy_, com _ESP8266_). Possui sondas de pH, ORP (Potencial de redução) e temperatura, fornece conectividade Wi-Fi.

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img alt="Atlas Scientific Wi-Fi Pool Kit" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html). Suporte de bateria e circuito de carga de painel solar. Pode fornecer energia para o _Wi-Fi Pool Kit_.

<a target="_blank" href="https://pt.aliexpress.com/item/4001156737871.html"><img alt="LILYGO® TTGO T-BAT Suporte de Bateria" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/lilygo-ttgo-t-bat.webp"></a>

- [Painel solar da iSNK](https://pt.aliexpress.com/store/3877081)

## Trabalho futuro

Alguns locais onde seria bom ter estações de monitoramento não possuem ponto de acesso Wi-Fi. Portanto, conectividade celular ou mesmo via satélite são necessárias.

- [LILYGO® TTGO T-SIM7000G](https://pt.aliexpress.com/item/4000542688096.html). Para conectividade celular esta placa de baixo consumo de energia e baixo custo vem com microcontrolador _ESP32_ da Espressif, modem 7000G da SIMCom, suporte de bateria e circuito de energia solar, tudo por volta de 200 Reais. O _ESP32_ é mais capaz que o _Arduino_ e mais barato que o _Raspberry Pi_.

<a target="_blank" href="https://pt.aliexpress.com/item/4000542688096.html"><img alt="LILYGO® TTGO T-SIM7000G" width="260" src="https://raw.githubusercontent.com/dirceu-jr/igapo/master/readme_files/lilygo-t-sim7000g.webp"></a>

## Referências

- Danos Socioambientais Urbanos Em Curitiba: Uma Abordagem Geográfica ([PDF](https://github.com/dirceu-jr/igapo/blob/master/references/danos-socioambientais-urbanos-em-curitiba-uma-abordagem-geografica.pdf))

## Software

- [Software Embarcado](https://github.com/dirceu-jr/igapo/blob/main/firmware/legacy_pool_kit/legacy_pool_kit.ino)
- [Canal no ThingSpeak](https://thingspeak.com/channels/1956479/)
- [Protótipo de Painel](https://dirceu-jr.github.io/igapo/dashboard/)

## Fornecedores

- [Atlas Scientific](https://atlas-scientific.com/)
- [Espressif](https://www.espressif.com/)
- [LILYGO](https://pt.aliexpress.com/store/2090076)

## Dados em tempo real

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=pH&type=line&width=380"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=ORP&type=line&width=380"></iframe>

<iframe width="380" height="260" src="https://thingspeak.com/channels/1956479/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temp&type=line&width=380"></iframe>
