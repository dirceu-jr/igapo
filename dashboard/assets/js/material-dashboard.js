/*!

 =========================================================
 * Material Dashboard - v2.1.2
 =========================================================

 * Product Page: https://www.creative-tim.com/product/material-dashboard
 * Copyright 2020 Creative Tim (http://www.creative-tim.com)

 * Designed by www.invisionapp.com Coded by www.creative-tim.com

 =========================================================

 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 */

(function() {
  var isWindows = navigator.platform.indexOf('Win') > -1 ? true : false;

  if (isWindows) {
    // if we are on windows OS we activate the perfectScrollbar function
    $('.sidebar .sidebar-wrapper, .main-panel, .main').perfectScrollbar();

    $('html').addClass('perfect-scrollbar-on');
  } else {
    $('html').addClass('perfect-scrollbar-off');
  }
})();


var breakCards = true;

var searchVisible = 0;
var transparent = true;

var transparentDemo = true;
var fixedTop = false;

var
  mobile_menu_visible = 0,
  mobile_menu_initialized = false,
  toggle_initialized = false,
  bootstrap_nav_initialized = false
;

var
  seq = 0,
  delays = 80,
  durations = 500
;

var
  seq2 = 0,
  delays2 = 80,
  durations2 = 500
;

$(document).ready(function() {

  $('body').bootstrapMaterialDesign();

  $sidebar = $('.sidebar');

  md.initSidebarsCheck();

  var window_width = $(window).width();

  // check if there is an image set for the sidebar's background
  md.checkSidebarImage();

  //    Activate bootstrap-select
  if ($(".selectpicker").length != 0) {
    $(".selectpicker").selectpicker();
  }

  //  Activate the tooltips
  $('[rel="tooltip"]').tooltip();

  $('.form-control').on("focus", function() {
    $(this).parent('.input-group').addClass("input-group-focus");
  }).on("blur", function() {
    $(this).parent(".input-group").removeClass("input-group-focus");
  });

  // remove class has-error for checkbox validation
  $('input[type="checkbox"][required="true"], input[type="radio"][required="true"]').on('click', function() {
    if ($(this).hasClass('error')) {
      $(this).closest('div').removeClass('has-error');
    }
  });

});

$(document).on('click', '.navbar-toggler', function() {
  var $toggle = $(this);

  if (mobile_menu_visible == 1) {
    $('html').removeClass('nav-open');

    $('.close-layer').remove();
    setTimeout(function() {
      $toggle.removeClass('toggled');
    }, 400);

    mobile_menu_visible = 0;
  } else {
    setTimeout(function() {
      $toggle.addClass('toggled');
    }, 430);

    var $layer = $('<div class="close-layer"></div>');

    if ($('body').find('.main-panel').length != 0) {
      $layer.appendTo(".main-panel");
    } else if (($('body').hasClass('off-canvas-sidebar'))) {
      $layer.appendTo(".wrapper-full-page");
    }

    setTimeout(function() {
      $layer.addClass('visible');
    }, 100);

    $layer.click(function() {
      $('html').removeClass('nav-open');
      mobile_menu_visible = 0;

      $layer.removeClass('visible');

      setTimeout(function() {
        $layer.remove();
        $toggle.removeClass('toggled');

      }, 400);
    });

    $('html').addClass('nav-open');
    mobile_menu_visible = 1;

  }

});

// activate collapse right menu when the windows is resized
$(window).resize(function() {
  md.initSidebarsCheck();

  // reset the seq for charts drawing animations
  seq = seq2 = 0;

  setTimeout(function() {
    md.initDashboardPageCharts();
  }, 500);
});

var md = {
  misc: {
    navbar_menu_visible: 0,
    active_collapse: true,
    disabled_collapse_init: 0,
  },

  checkSidebarImage: function() {
    var $sidebar = $('.sidebar');
    var image_src = $sidebar.data('image');

    if (image_src !== undefined) {
      sidebar_container = '<div class="sidebar-background" style="background-image: url(' + image_src + ') "/>';
      $sidebar.append(sidebar_container);
    }
  },

  initSidebarsCheck: function() {
    if ($(window).width() <= 991) {
      if ($sidebar.length != 0) {
        // OBS: what initRightMenu does?
        // md.initRightMenu();
      }
    }
  },

  checkFullPageBackgroundImage: function() {
    var $page = $('.full-page');
    var image_src = $page.data('image');

    if (image_src !== undefined) {
      image_container = '<div class="full-page-background" style="background-image: url(' + image_src + ') "/>'
      $page.append(image_container);
    }
  },

  initDashboardPageCharts: function() {

    if ($('#dailySalesChart').length != 0 || $('#completedTasksChart').length != 0 || $('#websiteViewsChart').length != 0) {

      // Risco em Curitiba -------------
      var dataDailySalesChart = {
        labels: ['D', 'S', 'T', 'Q', 'Q', 'S', 'S'],
        series: [
          [1, 2, 1, 2, 2, 2, 4]
        ]
      };

      var optionsDailySalesChart = {
        low: 0,
        high: 5,
        chartPadding: -14,
        plugins: [
          Chartist.plugins.tooltip({
              appendToBody: true
          })
        ]
      }

      var dailySalesChart = new Chartist.Line(
        '#dailySalesChart',
        dataDailySalesChart,
        optionsDailySalesChart
      );

      md.startAnimationForLineChart(dailySalesChart);

      // Precipitação -------------
      var dataWebsiteViewsChart = {
        labels: ['D', 'S', 'T', 'Q', 'Q', 'S', 'S'],
        series: [
          [7, 0, 4, 28, 0, 5, 21]
        ]
      }

      var optionsWebsiteViewsChart = {
        axisX: {
          showGrid: false
        },
        low: 0,
        high: 60,
        chartPadding: -14,
        plugins: [
          Chartist.plugins.tooltip({
              appendToBody: true,
              transformTooltipTextFnc: function(value) {
                return value + ' mm';
              }
          })
        ]
      }

      var responsiveOptions = [
        ['screen and (max-width: 640px)', {
          seriesBarDistance: 5,
          axisX: {
            labelInterpolationFnc: function(value) {
              return value[0];
            }
          }
        }]
      ]

      var websiteViewsChart = Chartist.Bar(
        '#websiteViewsChart',
        dataWebsiteViewsChart,
        optionsWebsiteViewsChart,
        responsiveOptions
      );

      //start animation for the Emails Subscription Chart
      md.startAnimationForBarChart(websiteViewsChart);

      // CO -------------
      var dataCompletedTasksChart = {
        labels: ['D', 'S', 'T', 'Q', 'Q', 'S', 'S'],
        series: [
          [9.15, 9.11, 6.02, 5.74, 5.65, 4.74, 4.72]
        ]
      };

      var optionsCompletedTasksChart = {
        low: 0,
        high: 11,
        chartPadding: -14,
        plugins: [
          Chartist.plugins.tooltip({
              appendToBody: true,
              transformTooltipTextFnc: function(value) {
                return value + ' ppm';
              }
          })
        ]
      }

      var completedTasksChart = new Chartist.Line(
        '#completedTasksChart',
        dataCompletedTasksChart,
        optionsCompletedTasksChart
      );

      // start animation for the Completed Tasks Chart - Line Chart
      md.startAnimationForLineChart(completedTasksChart);
    }
  },

  checkScrollForTransparentNavbar: debounce(function() {
    if ($(document).scrollTop() > 260) {
      if (transparent) {
        transparent = false;
        $('.navbar-color-on-scroll').removeClass('navbar-transparent');
      }
    } else {
      if (!transparent) {
        transparent = true;
        $('.navbar-color-on-scroll').addClass('navbar-transparent');
      }
    }
  }, 17),

  // unused
  initRightMenu: debounce(function() {
    $sidebar_wrapper = $('.sidebar-wrapper');

    if (!mobile_menu_initialized) {
      $navbar = $('nav').find('.navbar-collapse').children('.navbar-nav');

      mobile_menu_content = '';

      nav_content = $navbar.html();

      nav_content = '<ul class="nav navbar-nav nav-mobile-menu">' + nav_content + '</ul>';

      console.log($('nav').find('.navbar-form'));
      navbar_form = $('nav').find('.navbar-form').get(0).outerHTML;

      $sidebar_nav = $sidebar_wrapper.find(' > .nav');

      // insert the navbar form before the sidebar list
      $nav_content = $(nav_content);
      $navbar_form = $(navbar_form);
      $nav_content.insertBefore($sidebar_nav);
      $navbar_form.insertBefore($nav_content);

      $(".sidebar-wrapper .dropdown .dropdown-menu > li > a").click(function(event) {
        event.stopPropagation();

      });

      // simulate resize so all the charts/maps will be redrawn
      window.dispatchEvent(new Event('resize'));

      mobile_menu_initialized = true;
    } else {
      if ($(window).width() > 991) {
        // reset all the additions that we made for the sidebar wrapper only if the screen is bigger than 991px
        $sidebar_wrapper.find('.navbar-form').remove();
        $sidebar_wrapper.find('.nav-mobile-menu').remove();

        mobile_menu_initialized = false;
      }
    }
  }, 200),

  startAnimationForLineChart: function(chart) {

    chart.on('draw', function(data) {
      if (data.type === 'line' || data.type === 'area') {
        data.element.animate({
          d: {
            begin: 600,
            dur: 700,
            from: data.path.clone().scale(1, 0).translate(0, data.chartRect.height()).stringify(),
            to: data.path.clone().stringify(),
            easing: Chartist.Svg.Easing.easeOutQuint
          }
        });
      } else if (data.type === 'point') {
        seq++;
        data.element.animate({
          opacity: {
            begin: seq * delays,
            dur: durations,
            from: 0,
            to: 1,
            easing: 'ease'
          }
        });
      }
    });

    seq = 0;
  },

  startAnimationForBarChart: function(chart) {

    chart.on('draw', function(data) {
      if (data.type === 'bar') {
        seq2++;
        data.element.animate({
          opacity: {
            begin: seq2 * delays2,
            dur: durations2,
            from: 0,
            to: 1,
            easing: 'ease'
          }
        });
      }
    });

    seq2 = 0;
  }
}

// Returns a function, that, as long as it continues to be invoked, will not
// be triggered. The function will be called after it stops being called for
// N milliseconds. If `immediate` is passed, trigger the function on the
// leading edge, instead of the trailing.

function debounce(func, wait, immediate) {
  var timeout;
  return function() {
    var context = this,
      args = arguments;
    clearTimeout(timeout);
    timeout = setTimeout(function() {
      timeout = null;
      if (!immediate) func.apply(context, args);
    }, wait);
    if (immediate && !timeout) func.apply(context, args);
  };
};
