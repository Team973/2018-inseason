const loginDialog = document.getElementById('loginDialog');
const connectAddress = document.getElementById('connectAddress');
const connectButton = document.getElementById('connectButton');
const connectLoadingBar = document.getElementById('connectLoadingBar');
const closeButton = document.getElementById('closeButton');

// Function for hiding the connect box
onkeydown = (key) => {
  if (key.key === 'Escape') {
    loginDialog.close();
  }
};

if (!loginDialog.showModal) {
  dialogPolyfill.registerDialog(loginDialog);
}

closeButton.addEventListener('click', () => {
  loginDialog.close();
});

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
  } else {
    // On disconnect show the connect popup
    loginDialog.showModal();
    // Add Enter key handler
    connectAddress.onkeydown = (ev) => {
      if (ev.key === 'Enter') connectButton.click();
    };
    // Enable the input and the button
    connectAddress.disabled = false;
    connectButton.disabled = false;
    connectLoadingBar.hidden = true;
    connectButton.textContent = 'Connect';
    // Add the default address and select 973
    connectAddress.value = 'roborio-973-frc.local';
    connectAddress.focus();
    connectAddress.setSelectionRange(8, 11);
    // On click try to connect and disable the input and the button
    connectButton.onclick = () => {
      ipc.send('connect', connectAddress.value);
      connectAddress.disabled = true;
      connectButton.disabled = true;
      connectLoadingBar.hidden = false;
      connectButton.textContent = 'Connecting...';
    };
  }
}

// Set function to be called on NetworkTables connect. Not implemented.
// NetworkTables.addWsConnectionListener(onNetworkTablesConnection, true);

// Set function to be called when robot dis/connects
NetworkTables.addRobotConnectionListener(onRobotConnection, false);

// Sets function to be called when any NetworkTables key/value changes
// NetworkTables.addGlobalListener(onValueChanged, true);
