String.prototype.capitalize = function() {
  return this.replace(/(^\w|\s\w)/g, m => m.toUpperCase());
}

var prototype = {
  defaultTileLayer: function() {
    return L.tileLayer(
      'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
      {
        attribution: 'Mapa por \u0026copy; \<a href=\"http://openstreetmap.org\"\> OpenStreetMap',
        detectRetina: true,
        maxNativeZoom: 18,
        maxZoom: 21,
        minZoom: 0,
        subdomains: 'abc'
      }
    )
  },
  initMapWater: function() {
    // geodesic center of paraná
    // center: [-24.7574861, -51.7596274],
    var map = L.map('map', {
      center: [-25.496, -49.286],
      zoom: 10,
      attributionControl: false
    });

    var tile_layer = this.defaultTileLayer().addTo(map);

    L.control.attribution({ prefix: '<a href="https://leafletjs.com/">Leaflet</a>' }).addTo(map);

    var red_objects_ids = [8, 20, 30];
    var yellow_objects_ids = [10, 19, 21];

    var stations = [
      { lat: -25.38699, lng: -49.26674, name: 'Rio Belém - Estação São Lourenço', color: 'green', risk: 'Baixo', co2: 0.5 },
      { lat: -25.39875, lng: -49.27065, name: 'Rio Belém - Estação Nelson de Souza', color: 'green', risk: 'Baixo', co2: 0.2 },
      { lat: -25.40165, lng: -49.26997, name: 'Rio Belém - Estação OAB', color: 'green', risk: 'Baixo', co2: 0.8 },
      { lat: -25.40636, lng: -49.27002, name: 'Rio Belém - Estação Celeste Santi', color: 'green', risk: 'Baixo', co2: 0.3 },
      { lat: -25.41862, lng: -49.27064, name: 'Rio Belém - Estação Cândido de Abreu', color: 'green', risk: 'Baixo', co2: 0.6 },

      { lat: -25.4853, lng: -49.17603, name: 'Rio Pequeno - Estação 1', color: 'yellow', risk: 'Médio', co2: 0.8 },
      { lat: -25.49754, lng: -49.15766, name: 'Rio Pequeno - Estação 2', color: 'yellow', risk: 'Médio', co2: 0.3 },
      { lat: -25.51982, lng: -49.14433, name: 'Rio Pequeno - Estação 3', color: 'yellow', risk: 'Médio', co2: 0.1 },
      { lat: -25.54166, lng: -49.12717, name: 'Rio Pequeno - Estação 4', color: 'green', risk: 'Baixo', co2: 0.8 },

      { lat: -25.43261, lng: -49.1708, name: 'Rio Palmital - Estação 1', color: 'red', risk: 'Alto', co2: 0.5 },
      { lat: -25.39762, lng: -49.17424, name: 'Rio Palmital - Estação 2', color: 'red', risk: 'Alto', co2: 0.4 },
      { lat: -25.36878, lng: -49.17189, name: 'Rio Palmital - Estação 3', color: 'red', risk: 'Alto', co2: 0.3 },
      { lat: -25.34672, lng: -49.16877, name: 'Rio Palmital - Estação 4', color: 'yellow', risk: 'Médio', co2: 0.1 }
    ];

    $.ajax({
      url: "./data/sub_bacias_altoiguacupoligono.json"
    }).done(function(data) {
      L.geoJSON(data, {
        style: {
          fillOpacity: 0.1,
          color: 'green',
          weight: 1,
          opacity: 0.5
        },
        onEachFeature: function(feature, layer) {

          console.log(red_objects_ids.indexOf(feature.properties.OBJECTID));

          if (red_objects_ids.indexOf(feature.properties.OBJECTID) >= 0) {
            layer.setStyle({
              color: 'red',
              fillColor: 'red'
            });
          }

          if (yellow_objects_ids.indexOf(feature.properties.OBJECTID) >= 0) {
            layer.setStyle({
              color: 'yellow',
              fillColor: 'yellow'
            });
          }
        
          layer.on('mouseover', function() {
              this.setStyle({
                opacity: 0.8,
                weight: 3
              });
          });

          layer.on('mouseout', function() {
            this.setStyle({
              opacity: 0.5,
              weight: 1
            });
          });

          layer.bindTooltip('Bacia do ' + feature.properties.SUBNOME.toLowerCase().capitalize(), {
            sticky: true
          });
          
          // layer.on('click', function () {
          //     // Let's say you've got a property called url in your geojsonfeature:
          //     window.location = feature.properties.url;
          // });
        }
      }).addTo(map);

      // after xhr loaded
      for (station in stations) {
        var circle = L.circleMarker(
          [stations[station].lat, stations[station].lng], {
            color: '#000',
            fillColor: stations[station].color,
            weight: 1,
            radius: 5,
            fillOpacity: 1
          }
        ).addTo(map);
    
        circle.bindTooltip(
          [
            '<div><b>',
              stations[station].name,
            '</b></div><div>Risco ',
              stations[station].risk,
            '</div><div>Nível: 50cm<div><div>Chuva: 10mm</div><div>CO2e: ', stations[station].co2,' ppm</div>'
          ].join(''),
          { sticky: true }
        );
      }
    });

  },

  initMapAir: function() {

    var stations = [
      { code: 'PR02', name: 'Cidade Industrial', lat_lgn: [-25.508000, -49.337186], available_data: ['CO', 'NO2'] },
      { code: 'PR03', name: 'CSN', lat_lgn: [-25.5718755, -49.3879971], available_data: ['NO2', 'O3', 'PTS', 'SO2'] },
      { code: 'PR06', name: 'REPAR', lat_lgn: [-25.5658911, -49.3716738], available_data: ['CO', 'MP10', 'NO2', 'O3', 'PTS', 'SO2'] },
      { code: 'PR08', name: 'Assis', lat_lgn: [-24.3998019, -53.5337091], available_data: ['NO2', 'O3', 'PTS', 'SO2'] },
      { code: 'PR09', name: 'PETROSIX', lat_lgn: [-25.861061, -50.9571824], available_data: ['CO', 'NO2', 'O3', 'PTS', 'SO2'] },
      { code: 'PR14', name: 'Ponta Grossa', lat_lgn: [-25.1388653, -50.3493838], available_data: ['CO', 'MP10', 'NO2', 'O3', 'PTS'] },
      { code: 'PR15', name: 'Cascavel', lat_lgn: [-24.9637544, -53.5423919], available_data: ['CO', 'MP10', 'NO2', 'O3', 'PTS', 'SO2'] },
      { code: 'PR16', name: 'Londrina', lat_lgn: [-23.321264, -51.2358033], available_data: ['CO', 'MP10', 'NO2', 'O3', 'PTS', 'SO2'] },
    ];

    // TODO:
    // - cor do marker de acordo com índice de qualidade do conama

    var data_to_units = {
      'CO': 'ppm',
      'NO2': 'ppb',
      'O3': 'ppb',
      'SO2': 'ppb',
      'MP10': 'µg/m3',
      'PTS': 'µg/m3'
    };

    // geodesic center of paraná
    // center: [-24.7574861, -51.7596274],
    var map = L.map('map', {
      center: [-24.7574861, -51.7596274],
      zoom: 8,
      attributionControl: false
    });

    L.control.scale({ position: 'bottomleft' }).addTo(map);
    var tile_layer = this.defaultTileLayer().addTo(map);
    L.control.attribution({ prefix: '<a href="https://leafletjs.com/">Leaflet</a>' }).addTo(map);

    for (station in stations) {
      var marker = L.marker(stations[station].lat_lgn).addTo(map);
      var popup = marker.bindPopup();
      popup.on('popupopen', function() {
        this.setPopupContent("<div class='popup_chart'></div>");

        new Chartist.Line('.popup_chart', {
          labels: ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'],
          series: [
            [12, 9, 7, 8, 5],
            [2, 1, 3.5, 7, 3],
            [1, 3, 4, 5, 6]
          ]
        }, {
          chartPadding: -10
        });

      });
    }

  },

  initMapsLevel: function() {
    // Centro Cívico
    var map1_lat_lgn = [-25.414077, -49.270353];
    var map1 = L.map('map1', {
      center: map1_lat_lgn,
      zoom: 17,
      attributionControl: false
    });

    var tile_layer1 = this.defaultTileLayer().addTo(map1);
    var marker1 = L.marker(map1_lat_lgn).addTo(map1);

    // Itupava
    var map2_lat_lgn = [-25.422449, -49.251960];
    var map2 = L.map('map2', {
      center: map2_lat_lgn,
      zoom: 17,
      attributionControl: false
    });

    var tile_layer2 = this.defaultTileLayer().addTo(map2);
    var marker2 = L.marker(map2_lat_lgn).addTo(map2);

    // PUCPR
    var map3_lat_lgn = [-25.450110, -49.249865];
    var map3 = L.map('map3', {
      center: map3_lat_lgn,
      zoom: 17,
      attributionControl: false
    });

    var tile_layer3 = this.defaultTileLayer().addTo(map3);
    var marker3 = L.marker(map3_lat_lgn).addTo(map3);

    // Parque Náutico
    var map4_lat_lgn = [-25.5250071, -49.2238426];
    var map4 = L.map('map4', {
      center: map4_lat_lgn,
      zoom: 17,
      attributionControl: false
    });

    var tile_layer4 = this.defaultTileLayer().addTo(map4);
    var marker4 = L.marker(map4_lat_lgn).addTo(map4);
  }
}
