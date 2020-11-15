String.prototype.capitalize = function() {
  return this.replace(/(^\w|\s\w)/g, m => m.toUpperCase());
}

var demo = {
  initDashboardPageCharts: function() {

    if ($('#dailySalesChart').length != 0 || $('#completedTasksChart').length != 0 || $('#websiteViewsChart').length != 0) {
      /* ----------==========     Daily Sales Chart initialization    ==========---------- */

      dataDailySalesChart = {
        labels: ['M', 'T', 'W', 'T', 'F', 'S', 'S'],
        series: [
          [12, 17, 7, 17, 23, 18, 38]
        ]
      };

      optionsDailySalesChart = {
        lineSmooth: Chartist.Interpolation.cardinal({
          tension: 0
        }),
        low: 0,
        high: 50, // creative tim: we recommend you to set the high sa the biggest value + something for a better look
        chartPadding: {
          top: 0,
          right: 0,
          bottom: 0,
          left: 0
        },
      }

      var dailySalesChart = new Chartist.Line('#dailySalesChart', dataDailySalesChart, optionsDailySalesChart);

      md.startAnimationForLineChart(dailySalesChart);



      /* ----------==========     Completed Tasks Chart initialization    ==========---------- */

      dataCompletedTasksChart = {
        labels: ['12p', '3p', '6p', '9p', '12p', '3a', '6a', '9a'],
        series: [
          [230, 750, 450, 300, 280, 240, 200, 190]
        ]
      };

      optionsCompletedTasksChart = {
        lineSmooth: Chartist.Interpolation.cardinal({
          tension: 0
        }),
        low: 0,
        high: 1000, // creative tim: we recommend you to set the high sa the biggest value + something for a better look
        chartPadding: {
          top: 0,
          right: 0,
          bottom: 0,
          left: 0
        }
      }

      var completedTasksChart = new Chartist.Line('#completedTasksChart', dataCompletedTasksChart, optionsCompletedTasksChart);

      // start animation for the Completed Tasks Chart - Line Chart
      md.startAnimationForLineChart(completedTasksChart);


      /* ----------==========     Emails Subscription Chart initialization    ==========---------- */

      var dataWebsiteViewsChart = {
        labels: ['J', 'F', 'M', 'A', 'M', 'J', 'J', 'A', 'S', 'O', 'N', 'D'],
        series: [
          [542, 443, 320, 780, 553, 453, 326, 434, 568, 610, 756, 895]

        ]
      };
      var optionsWebsiteViewsChart = {
        axisX: {
          showGrid: false
        },
        low: 0,
        high: 1000,
        chartPadding: {
          top: 0,
          right: 5,
          bottom: 0,
          left: 0
        }
      };
      var responsiveOptions = [
        ['screen and (max-width: 640px)', {
          seriesBarDistance: 5,
          axisX: {
            labelInterpolationFnc: function(value) {
              return value[0];
            }
          }
        }]
      ];
      var websiteViewsChart = Chartist.Bar('#websiteViewsChart', dataWebsiteViewsChart, optionsWebsiteViewsChart, responsiveOptions);

      //start animation for the Emails Subscription Chart
      md.startAnimationForBarChart(websiteViewsChart);
    }
  },

  initMaps: function() {
    
    var map = L.map(
      "map",
      {
          center: [-24.7574861, -51.7596274], 
          zoom: 7
      }
    );

    var tile_layer = L.tileLayer(
      "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
        {
            attribution: "Dados por \u0026copy; \<a href=\"http://openstreetmap.org\"\> OpenStreetMap",
            detectRetina: true,
            maxNativeZoom: 18,
            maxZoom: 21,
            minZoom: 0,
            subdomains: "abc"
        }
    ).addTo(map);

    var circle_1 = L.circle(
      [-25.413852, -49.270339],
      {
          color: "#00FF69",
          radius: 20
      }
    ).addTo(map);

    circle_1.bindTooltip(
      "<div>Nível: 50cm - Chuva: 10mm</div>",
      { sticky: true }
    );

    $.ajax({
      url: "./data/sub_bacias_altoiguacupoligono.json"
    }).done(function(data) {
      L.geoJSON(data, {
          style: {
              fillOpacity: 0.1,
              color: "#417fc2",
              weight: 3,
              opacity: 0.5
          },
          onEachFeature: function (feature, layer) {
              layer.on('mouseover', function () {
                  // bacia hidrogrfica
                  layer.bindPopup(feature.properties.SUBNOME.toLowerCase().capitalize());
                  this.setStyle({
                      'fillColor': '#0000ff'
                  });
              });
              layer.on('mouseout', function () {
                  this.setStyle({
                      'fillColor': '#417fc2'
                  });
              });
              // layer.on('click', function () {
              //     // Let's say you've got a property called url in your geojsonfeature:
              //     window.location = feature.properties.url;
              // });
          }
      }).addTo(map);
    });
  }
}
