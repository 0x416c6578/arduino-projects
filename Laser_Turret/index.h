const char page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <title>Servo Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body>
  <h1>Servo X</h1>
  <div>
    <input type="range" min="0" max="180" step="5" value="90" class="slider" id="posX">
  </div>

  <h1>Servo Y</h1>
  <div>
    <input type="range" min="0" max="180" step="5" value="90" class="slider" id="posY">
  </div>

  <script>
    function sendPos(posX, posY) {
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "setPos?x=" + posX + "&y=" + posY, true);
      xhttp.send();
    }

    var sliderX = document.getElementById("posX");
    var sliderY = document.getElementById("posY");

    sliderX.onchange = function () {
      sendPos(180 - sliderX.value, sliderY.value);
      console.log("X: " + sliderX.value + " Y: " + sliderY.value);
    }

    sliderY.onchange = function () {
      sendPos(180 - sliderX.value, sliderY.value);
      console.log("X: " + sliderX.value + " Y: " + sliderY.value);
    }

    sendPos(90,90);
  </script>
</body>

</html>
)=====";