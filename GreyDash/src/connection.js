const loginDialog = document.getElementById('loginDialog');
const connectAddress = document.getElementById('connectAddress');
const connectButton = document.getElementById('connectButton');
const closeButton = document.getElementById('closeButton');

let loginShown = true;

// Function for hiding the connect box
onkeydown = (key) => {
  if (key.key === 'Escape') {
    loginDialog.close();
    loginShown = false;
  }
};

if (!loginDialog.showModal) {
  dialogPolyfill.registerDialog(loginDialog);
}

closeButton.addEventListener('click', () => {
  loginDialog.close();
});

function connectRobot() {
  ipc.send('connect', connectAddress.value);
  connectAddress.disabled = connectButton.disabled = true;
  connectButton.textContent = 'Connecting...';
}

function setLogin() {
  // Add Enter key handler
  // Enable the input and the button
  connectAddress.disabled = false;
  connectButton.disabled = false;
  connectButton.textContent = 'Connect';
  // Add the default address and select 973
  connectAddress.value = 'roborio-973-frc.local';
  connectAddress.focus();
  connectAddress.setSelectionRange(8, 11);
}

/**
 * Function to be called when robot connects
 * @param {boolean} connected
 */
function onRobotConnection(connected) {
  const state = connected ? 'Robot connected!' : 'Robot disconnected.';
  console.log(state);
  ui.misc.robotState.textContent = state;

  if (connected) {
    // On connect hide the connect popup
    loginDialog.close();
    loginShown = false;
  } else if (loginShown) {
    setLogin();
  }
}

// On click try to connect and disable the input and the button
connectButton.onclick = () => {
  connectRobot();
};

connectAddress.onkeydown = (ev) => {
  if (ev.key === 'Enter') {
    connectRobot();
    ev.preventDefault();
    ev.stopPropagation();
  }
};

// Set function to be called on NetworkTables connect. Not implemented.
// NetworkTables.addWsConnectionListener(onNetworkTablesConnection, true);

// Set function to be called when robot dis/connects
NetworkTables.addRobotConnectionListener(onRobotConnection, false);

// Sets function to be called when any NetworkTables key/value changes
// NetworkTables.addGlobalListener(onValueChanged, true);


// Show login when starting
loginDialog.showModal();
setLogin();
