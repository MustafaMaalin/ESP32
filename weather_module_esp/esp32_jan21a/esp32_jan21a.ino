#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "Familie Maalin";
const char* password = "tijdelijk";

#define DHTPIN 27     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTemp() {
  float t = dht.readTemperature();

  // here we check if there are any failed reads
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor");
    return "--";
  } else {
    Serial.println(t);
    return String(t);
  }
}

// string that reads the humidity of the weather.
String readHum() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor");
    return "--";
  } else {
    Serial.println(h);
    return String(h);
  }
}

//progmem will store a webpage in a arduino program.
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Verdana, Geneva, Tahoma, sans-serif;
     display: inline-block;
     text-align: center;
     background-color: lightblue;
    }
    h2 { font-size: 60px; }
    p { font-size: 20px; }
    .units { font-size: 1.2rem; }
    .sensorinfo{
      font-size: 20px;
      text-align: center;
    }
    .border{
        border: ridge; 
        background: gray;
    }
  </style>
</head>
<body>
  <h2>Temp/Hum check</h2>
  <div class="border">
  <p>
    <i class="fas fa-thermometer-half" style="color:red"></i> 
    <span class="sensorinfo">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i>
     
    <span class="sensorinfo">Humidity/Vochtigheid</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</div>
</body>
//ajax functionalities for temp and hum. these js functions will update the temp and humidty every 10 seconds. 
setInterval(function(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readystate == 4 && this.status == 200){
      document.getElementById("temperature").innerHTML = this.responseText;
    }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
  }, 10000);
  
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

</script>
  
</html>)rawliteral";

// to replace the the placeholder i'll use the function down below

String processor(const String& var) {
  // if the webpage is requested  this statement checks if there is any placeholder that is named %TEMPERATURE%
  if (var == "TEMPERATURE") {
    return readTemp();
  }
  //same goes for %HUMIDITY%
  else if (var == "HUMIDITY") {
    return readHum();
  }
  return String();
}

void setup() {
  // serial port for debugging purposes
  Serial.begin(115200);

  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to wifi...");
  }
}

// Print Local IP Address
Serial.println(WiFi.localIP());

// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html, processor);
});
server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send_P(200, "text/plain", readTemp().c_str());
});
server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send_P(200, "text/plain", readHum().c_str());
});
}

// Start server
server.begin();
}

void loop() {

}
