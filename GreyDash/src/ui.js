require('../node_modules/justgage/justgage.js');
const smoothie = require('smoothie');
const fs = require('fs');

const config = JSON.parse(fs.readFileSync(`${__dirname}/configlisteners.json`, 'utf-8'));

// Set Defaults
for (let i = 0; i < config.charts.length; i += 1) {
  if (config.charts[i].settings.tooltip === undefined) {
    config.charts[i].settings.tooltip = false;
  }
  if (config.charts[i].settings.minValue === undefined) {
    config.charts[i].settings.minValue = 0;
  }
  if (config.charts[i].settings.maxValue === undefined) {
    config.charts[i].settings.maxValue = 50;
  }
  if (config.charts[i].settings.debug === undefined) {
    config.charts[i].settings.debug = false;
  }
}
for (let i = 0; i < config.indicators.length; i += 1) {
  if (config.indicators[i].settings.fixedDecimals === undefined) {
    config.indicators[i].settings.fixedDecimals = true;
  }
  if (config.indicators[i].settings.debug === undefined) {
    config.indicators[i].settings.debug = false;
  }
}

// Reload on capital R
window.addEventListener('keypress', (ev) => {
  if (ev.key === 'R') {
    location.reload(true);
  }
});

/**
 * Define UI Elements
 */
const ui = {
  misc: {
    timer: document.getElementById('timer'),
    robotState: document.getElementById('robotState').firstChild,
    autoSelect: document.getElementById('autoSelect'),
  },
  charts: document.getElementById('charts'),
  debugCharts: document.getElementById('debugCharts'),
  indicators: document.getElementById('indicators'),
  debugIndicators: document.getElementById('debugIndicators'),
  custom: {
    drive: {
      gyro: {
        container: document.getElementById('gyro'),
        val: 0,
        offset: 0,
        visualVal: 0,
        gyroDial: document.getElementById('gyroDial'),
        gyroNumber: document.getElementById('gyroNumber'),
      },
      debugGyro: {
        container: document.getElementById('debugGyro'),
        val: 0,
        offset: 0,
        visualVal: 0,
        debugGyroDial: document.getElementById('debugGyroDial'),
        debugGyroNumber: document.getElementById('debugGyroNumber'),
      },
    },
  },
};

/**
 * Chart Listeners
 */
for (let i = 0; i < config.charts.length; i += 1) {
  config.charts[i].div = document.createElement('div');
  config.charts[i].div.setAttribute('id', `chart${i}`);
  config.charts[i].div.setAttribute('class', 'chartContainer');

  config.charts[i].displayTitle = document.createElement('span');
  config.charts[i].displayTitle.innerText = `${config.charts[i].title}`;

  config.charts[i].displayChart = document.createElement('canvas');
  config.charts[i].displayChart.setAttribute('class', 'responsiveCharts');

  config.charts[i].chart = new smoothie.SmoothieChart({
    interpolation: 'step',
    responsive: 'true',
    tooltip: config.charts[i].settings.tooltip,
    minValue: config.charts[i].settings.minValue,
    maxValue: config.charts[i].settings.maxValue,
  });
  config.charts[i].chart.streamTo(config.charts[i].displayChart, 0);

  config.charts[i].lines = {};
  for (let line = 0; line < config.charts[i].keys.length; line += 1) {
    const colors = ['red', 'blue', 'yellow', 'violet', 'orange', 'indigo'];
    config.charts[i].lines[line] = new smoothie.TimeSeries();
    config.charts[i].chart.addTimeSeries(config.charts[i].lines[line], {
      strokeStyle: colors[line],
      lineWidth: 3,
    });
    NetworkTables.addKeyListener(config.charts[i].keys[line], (function bindIndicator(idx) {
      return ((key, value) => {
        config.charts[idx].lines[line].append(new Date().getTime(), value);
      });
    }(i)));
  }
  config.charts[i].div.appendChild(config.charts[i].displayTitle);
  config.charts[i].div.appendChild(document.createElement('br'));
  config.charts[i].div.appendChild(config.charts[i].displayChart);
  if (config.charts[i].settings.debug) {
    ui.debugCharts.appendChild(config.charts[i].div);
  } else {
    ui.charts.appendChild(config.charts[i].div);
  }
}

/**
 * Regular Listeners
 */
for (let i = 0; i < config.indicators.length; i += 1) {
  let unitvalue;
  config.indicators[i].div = document.createElement('div');
  config.indicators[i].div.setAttribute('id', `indicator${i}`);

  config.indicators[i].displayTitle = document.createElement('span');
  config.indicators[i].displayTitle.innerText = `${config.indicators[i].title}: `;

  config.indicators[i].displayValue = document.createElement('span');

  NetworkTables.addKeyListener(config.indicators[i].key, (function bindIndicator(idx) {
    return ((key, value) => {
      if (config.indicators[idx].settings.fixedDecimals === true) {
        unitvalue = `${value.toFixed(2)} ${config.indicators[idx].unit}`;
      } else {
        unitvalue = `${value} ${config.indicators[idx].unit}`;
      }
      config.indicators[idx].displayValue.innerText = unitvalue;
    });
  }(i)));

  config.indicators[i].displayTitle.appendChild(config.indicators[i].displayValue);
  config.indicators[i].div.appendChild(config.indicators[i].displayTitle);
  ui.indicators.appendChild(config.indicators[i].div);
  if (config.indicators[i].settings.debug) {
    ui.debugIndicators.appendChild(config.indicators[i].div);
  } else if (config.indicators[i].settings.bothTabs) {
    ui.indicators.appendChild(config.indicators[i].div);
    ui.debugIndicators.appendChild(config.indicators[i].div);
  } else {
    ui.indicators.appendChild(config.indicators[i].div);
  }
}

/**
 * Custom Listeners
 */

// Gyro rotation
const updateGyro = (key, value) => {
  ui.custom.drive.gyro.val = value;
  ui.custom.drive.gyro.visualVal = Math.floor(ui.custom.drive.gyro.val
                                              - ui.custom.drive.gyro.offset);
  ui.custom.drive.gyro.visualVal %= 360;
  if (ui.custom.drive.gyro.visualVal < 0) {
    ui.custom.drive.gyro.visualVal += 360;
  }
  ui.custom.drive.gyro.gyroDial.style.transform = `rotate(-${ui.custom.drive.gyro.visualVal}deg)`;
  ui.custom.drive.gyro.gyroNumber.innerHTML = `${ui.custom.drive.gyro.visualVal}º`;
};
const updateDebugGyro = (key, value) => {
  ui.custom.drive.debugGyro.val = value;
  ui.custom.drive.debugGyro.visualVal = Math.floor(ui.custom.drive.debugGyro.val
                                              - ui.custom.drive.debugGyro.offset);
  ui.custom.drive.debugGyro.visualVal %= 360;
  if (ui.custom.drive.debugGyro.visualVal < 0) {
    ui.custom.drive.debugGyro.visualVal += 360;
  }
  ui.custom.drive.debugGyro.debugGyroDial.style.transform = `rotate(-${ui.custom.drive.debugGyro.visualVal}deg)`;
  ui.custom.drive.debugGyro.debugGyroNumber.innerHTML = `${ui.custom.drive.debugGyro.visualVal}º`;
};
NetworkTables.addKeyListener('/SmartDashboard/drive/gyro/angle', updateGyro);
NetworkTables.addKeyListener('/SmartDashboard/drive/gyro/angle', updateDebugGyro);

NetworkTables.addKeyListener('/robot/time', (key, value) => {
  // This is an example of how a dashboard could display the remaining time in a match.
  // We assume here that value is an integer representing the number of seconds left.
  ui.misc.timer.innerHTML = value < 0 ? '0:00' : `${Math.floor(value / 60)}:${value % 60 < 10 ? '0' : ''}${value % 60}`;
});

// Reset gyro value to 0 on click
ui.custom.drive.gyro.container.addEventListener('click', () => {
  // Store previous gyro val, will now be subtracted from val for callibration
  ui.custom.drive.gyro.offset = ui.custom.drive.gyro.val;
  // Trigger the gyro to recalculate value.
  updateGyro('/SmartDashboard/drive/gyro/angle', ui.custom.drive.gyro.val);
});
ui.custom.drive.debugGyro.container.addEventListener('click', () => {
  // Store previous gyro val, will now be subtracted from val for callibration
  ui.custom.drive.debugGyro.offset = ui.custom.drive.debugGyro.val;
  // Trigger the gyro to recalculate value.
  updateDebugGyro('/SmartDashboard/drive/gyro/angle', ui.custom.drive.gyro.val);
});

// Compressor
const airGuage = new JustGage({
  id: 'airPressure',
  min: 0,
  max: 60,
  title: 'Air Pressure',
});
const debugAirGuage = new JustGage({
  id: 'debugAirPressure',
  min: 0,
  max: 60,
  title: 'Air Pressure',
});

NetworkTables.addKeyListener('/SmartDashboard/misc/compressor/pressure', (key, value) => {
  airGuage.value = value;
  debugAirGuage.value = value;
});

window.addEventListener('error', (ev) => {
  ipc.send('windowError', { mesg: ev.message, file: ev.filename, lineNumber: ev.lineno });
});
