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
      { code: 'PR02', name: '', available_data: [] }
    ];

    var data_to_units = {
      'PTS': 'µg/m3',

    };

    // geodesic center of paraná
    // center: [-24.7574861, -51.7596274],
    var map = L.map('map', {
      center: [-24.7574861, -51.7596274],
      zoom: 7,
      attributionControl: false
    });

    var tile_layer = this.defaultTileLayer().addTo(map);

    L.control.attribution({ prefix: '<a href="https://leafletjs.com/">Leaflet</a>' }).addTo(map);

    var stations = [
      { lat: -25.38699, lng: -49.26674, name: 'Rio Belém - Estação São Lourenço', color: 'yellow', risk: 'Baixo', co2: 0.5 },
      { lat: -25.39875, lng: -49.27065, name: 'Rio Belém - Estação Nelson de Souza', color: 'yellow', risk: 'Baixo', co2: 0.2 },
      { lat: -25.40165, lng: -49.26997, name: 'Rio Belém - Estação OAB', color: 'yellow', risk: 'Baixo', co2: 0.8 },
      { lat: -25.40636, lng: -49.27002, name: 'Rio Belém - Estação Celeste Santi', color: 'green', risk: 'Baixo', co2: 0.3 },
      { lat: -25.41862, lng: -49.27064, name: 'Rio Belém - Estação Cândido de Abreu', color: 'yellow', risk: 'Baixo', co2: 0.6 },

      { lat: -25.4853, lng: -49.17603, name: 'Rio Pequeno - Estação 1', color: 'green', risk: 'Médio', co2: 0.8 },
      { lat: -25.49754, lng: -49.15766, name: 'Rio Pequeno - Estação 2', color: 'yellow', risk: 'Médio', co2: 0.3 },
      { lat: -25.51982, lng: -49.14433, name: 'Rio Pequeno - Estação 3', color: 'red', risk: 'Médio', co2: 0.1 },
      { lat: -25.54166, lng: -49.12717, name: 'Rio Pequeno - Estação 4', color: 'red', risk: 'Baixo', co2: 0.8 },

      { lat: -25.43261, lng: -49.1708, name: 'Rio Palmital - Estação 1', color: 'green', risk: 'Alto', co2: 0.5 },
      { lat: -25.39762, lng: -49.17424, name: 'Rio Palmital - Estação 2', color: 'green', risk: 'Alto', co2: 0.4 },
      { lat: -25.36878, lng: -49.17189, name: 'Rio Palmital - Estação 3', color: 'red', risk: 'Alto', co2: 0.3 },
      { lat: -25.34672, lng: -49.16877, name: 'Rio Palmital - Estação 4', color: 'yellow', risk: 'Médio', co2: 0.1 }
    ];

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
          '</b></div><div>CO2e: ', stations[station].co2,' ppm</div>'
        ].join(''),
        { sticky: true }
      );
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
  }
}
