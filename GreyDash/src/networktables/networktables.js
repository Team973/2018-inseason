const ipc = require('electron').ipcRenderer;

const NetworkTables =
    (() => {
      const keys = {};
      const connectionListeners = [];
      let connected = false;
      const globalListeners = [];
      const keyListeners = {};
      const robotAddress = '127.0.0.1';
      ipc.send('ready');
      ipc.on('connected', (ev, con) => {
        connected = con;
        connectionListeners.map(e => e(con));
      });
      ipc.on('add', (ev, mesg) => {
        keys[mesg.key] = {
          val: mesg.val, valType: mesg.valType, id: mesg.id, flags: mesg.flags, new: true,
        };
        globalListeners.map(e => e(mesg.key, mesg.val, true));
        if (globalListeners.length > 0) { keys[mesg.key].new = false; }
        if (mesg.key in keyListeners) {
          keyListeners[mesg.key].map(e => e(mesg.key, mesg.val, true));
          keys[mesg.key].new = false;
        }
      });
      ipc.on('delete', (ev, mesg) => {
        delete keys[mesg.key];
      });
      ipc.on('update', (ev, mesg) => {
        const temp = keys[mesg.key];
        temp.flags = mesg.flags;
        temp.val = mesg.val;
        globalListeners.map(e => e(mesg.key, temp.val, temp.new));
        if (globalListeners.length > 0) { keys[mesg.key].new = false; }
        if (mesg.key in keyListeners) {
          keyListeners[mesg.key].map(e => e(mesg.key, temp.val, temp.new));
          temp.new = false;
        }
      });
      ipc.on('flagChange', (ev, mesg) => {
        keys[mesg.key].flags = mesg.flags;
      });
      const d3Map = function () {
        this._ = Object.create(null);
        this.forEach = function (f) {
          for (const key in this._) { f.call(this, d3MapUnescape(key), this._[key]); }
        };
        this.get = function (key) {
          return this._[d3MapEscape(key)];
        };
        this.getKeys = function () {
          const keys = [];
          for (const key in this._) { keys.push(d3MapUnescape(key)); }
          return keys;
        };
        this.has = function (key) {
          return d3MapEscape(key) in this._;
        };
        this.set = function (key, value) {
          return this._[d3MapEscape(key)] = value;
        };
      };
      const d3MapProto = '__proto__';
      const d3MapZero = '\x00';
      function d3MapEscape(key) {
        return (key += '') === d3MapProto || key[0] === d3MapZero ? d3MapZero + encodeURIComponent(key) : encodeURIComponent(key);
      }
      function d3MapUnescape(key) {
        return (key += '')[0] === d3MapZero ? decodeURIComponent(key.slice(1)) : decodeURIComponent(key);
      }
      return {
        /**
         * Sets a function to be called when the robot connects/disconnects to the pynetworktables2js server via NetworkTables. It will also be called when the websocket connects/disconnects.
         *
         * When a listener function is called with a ‘true’ parameter, the NetworkTables.getRobotAddress() function will return a non-null value.
         * @param {(connected: boolean) => any} f a function that will be called with a single boolean parameter that indicates whether the robot is connected
         * @param {boolean} [immediateNotify] If true, the function will be immediately called with the current robot connection state
         */
        addRobotConnectionListener(f, immediateNotify) {
          if (typeof f !== 'function') return new Error('Invalid argument');

          connectionListeners.push(f);
          if (immediateNotify) { f(connected); }
        },

        /**
         * Set a function that will be called whenever any NetworkTables value is changed
         * @param {(key: string, value: any, isNew: boolean) => any} f When any key changes, this function will be called with the following parameters; key: key name for entry, value: value of entry, isNew: If true, the entry has just been created
         * @param {boolean} [immediateNotify] If true, the function will be immediately called with the current value of all keys
         */
        addGlobalListener(f, immediateNotify) {
          if (typeof f !== 'function') return new Error('Invalid argument');

          globalListeners.push(f);
          if (immediateNotify) {
            for (const key in keys) {
              f(key, keys[key].val, keys[key].new);
              keys[key].new = false;
            }
          }
        },

        /**
         * Set a function that will be called whenever a value for a particular key is changed in NetworkTables
         * @param {string} key A networktables key to listen for
         * @param {(key: string, value: any, isNew: boolean) => any} f When the key changes, this function will be called with the following parameters; key: key name for entry, value: value of entry, isNew: If true, the entry has just been created
         * @param {boolean} [immediateNotify] If true, the function will be immediately called with the current value of the specified key
         */
        addKeyListener(key, f, immediateNotify) {
          if (typeof key !== 'string' || typeof f !== 'function') return new Error('Valid Arguments are (string, function)');

          if (typeof keyListeners[key] !== 'undefined') {
            keyListeners[key].push(f);
          } else {
            keyListeners[key] = [f];
          }
          if (immediateNotify && key in keys) {
            const temp = keys[key];
            f(key, temp.val, temp.new);
          }
        },

        /**
         * Use this to test whether a value is present in the table or not
         * @param {string} key A networktables key
         * @returns true if a key is present in NetworkTables, false otherwise
         */
        containsKey(key) {
          if (typeof f !== 'string') return false;
          return key in keys;
        },

        /**
         * Get all keys in the NetworkTables
         * @returns all the keys in the NetworkTables
         */
        getKeys() {
          return Object.keys(keys);
        },

        /**
         * Returns the value that the key maps to. If the websocket is not open, this will always return the default value specified.
         * @param {string} key A networktables key
         * @param {any} [defaultValue] If the key isn’t present in the table, return this instead
         * @returns value of key if present, undefined or defaultValue otherwise
         */
        getValue(key, defaultValue) {
          if (typeof key !== 'string') return new Error('Invalid Argument');

          if (typeof keys[key] !== 'undefined') {
            return keys[key].val;
          }

          return defaultValue;
        },

        /**
         * @returns null if the robot is not connected, or a string otherwise
         */
        getRobotAddress() {
          return connected ? robotAddress : null;
        },

        /**
         * @returns true if the robot is connected
         */
        isRobotConnected() {
          return connected;
        },

        /**
         * Sets the value in NetworkTables. If the websocket is not connected, the value will be discarded.
         * @param {string} key A networktables key
         * @param value The value to set (see warnings)
         * @returns True if the websocket is open, False otherwise
         */
        putValue(key, value) {
          if (typeof key !== 'string') return new Error('Invalid Argument');

          if (typeof keys[key] !== 'undefined') {
            keys[key].val = value;
            ipc.send('update', {
              key, val: value, id: keys[key].id, flags: keys[key].flags,
            });
          } else {
            ipc.send('add', { key, val: value, flags: 0 });
          }
          return connected;
        },

        /**
         * Creates a new empty map (or hashtable) object and returns it. The map is safe to store NetworkTables keys in.
         * @returns map object, with forEach/get/has/set functions defined. Simlar to a map object when using d3.js
         */
        create_map() {
          return new d3Map();
        },

        /**
         * Escapes NetworkTables keys so that they’re valid HTML identifiers.
         * @param key A networktables key
         * @returns Escaped value
         */
        keyToId: encodeURIComponent,

        /**
         * Escapes special characters and returns a valid jQuery selector. Useful as NetworkTables does not really put any limits on what keys can be used.
         * @param {string} key A networktables key
         * @returns Escaped value
         */
        keySelector(key) {
          return encodeURIComponent(key).replace(/([;&,\.\+\*\~':"\!\^#$%@\[\]\(\)=>\|])/g, '\\$1');
        },
      };
    })();
