const winston = require('winston');

// Set up logger
const customColors = {
  trace: 'white',
  debug: 'green',
  info: 'green',
  warn: 'yellow',
  crit: 'red',
  fatal: 'red',
};

const logger = winston.createLogger({
  colors: customColors,
  levels: {
    trace: 0,
    debug: 1,
    info: 2,
    warn: 3,
    crit: 4,
    fatal: 5,
  },
  transports: [
    new winston.transports.Console({
      name: 'consoleLogger',
      // level: 'fatal',
      // colorize: true,
      // timestamp: true,
    }),
    new winston.transports.File({ filename: 'filelogs.log' }),
  ],
});

winston.addColors(customColors);

// Extend logger object to properly log 'Error' types
const origLog = logger.log;

logger.log = function (level, msg) {
  if (msg instanceof Error) {
    const args = Array.prototype.slice.call(arguments);
    args[1] = msg.stack;
    origLog.apply(logger, args);
  } else {
    origLog.apply(logger, arguments);
  }
};
/* LOGGER EXAMPLES
    app.logger.trace('testing');
    app.logger.debug('testing');
    app.logger.info('testing');
    app.logger.warn('testing');
    app.logger.crit('testing');
    app.logger.fatal('testing');
*/

module.exports = logger;
