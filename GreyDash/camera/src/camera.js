const cameraUrl = 'http://roborio-973-frc.local:1181/stream.mjpg';
const cameraContainer = document.getElementById('cameraContainer');

function reloadCamera() {
  const content = cameraContainer.innerHTML;
  cameraContainer.innerHTML = content;
  console.log('reloaded camera');
}

function createCamera(url) {
  const camera = document.createElement('img');
  camera.setAttribute('src', url);
  camera.setAttribute('id', 'camera');
  camera.setAttribute('onerror', 'reloadCamera()');
  cameraContainer.insertBefore(camera, cameraContainer.firstChild);
}
// window.setInterval(new XMLHttpRequest().open('GET', cameraUrl), 10);
window.setTimeout(createCamera(cameraUrl), 2000);
