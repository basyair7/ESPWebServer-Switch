const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server (Server 1)</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {
      font-family: Arial; 
      display: inline-block; 
      text-align: center;
    }
    h2 {
      font-size: 3.0rem;
    }
    p {
      font-size: 3.0rem;
    }
    body {
      max-width: 600px; 
      margin:0px auto; 
      padding-bottom: 25px;
    }
    .switch {
      position: relative; 
      display: inline-block; 
      width: 120px; 
      height: 68px;
    } 
    .switch input {
      display: none;
    }
    .slider {
      position: absolute; 
      top: 0; left: 0; right: 0; bottom: 0; 
      background-color: #ccc; 
      border-radius: 6px;
    }
    .slider:before {
      position: absolute; 
      content: ""; 
      height: 52px; 
      width: 52px; 
      left: 8px; 
      bottom: 8px; 
      background-color: #fff; 
      -webkit-transition: .4s; 
      transition: .4s; 
      border-radius: 3px;
    }
    input:checked+.slider {
      background-color: #b30000
    }
    input:checked+.slider:before {
      -webkit-transform: translateX(52px); 
      -ms-transform: translateX(52px); 
      transform: translateX(52px);
    }
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String &var)
{
  if (var == "BUTTONPLACEHOLDER")
  {
    String buttons = "";
    buttons += "<h4>Lampu Ruang Tamu</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(pinRelay_3) + "\" " + outputState(pinRelay_3) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Lampu Kamar 1</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(pinRelay_1) + "\" " + outputState(pinRelay_1) + "><span class=\"slider\"></span></label>";
    buttons += "<h4>Lampu Kamar 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(pinRelay_2) + "\" " + outputState(pinRelay_2) + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}

String outputState(int output)
{
  if (digitalRead(output))
  {
    return "checked";
  }
  else
  {
    return "";
  }
}

void webServerMain()
{
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      EEPROM.write(inputMessage1.toInt(), inputMessage2.toInt());
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
      EEPROM.commit();
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print(F("GPIO: "));
    Serial.print(inputMessage1);
    Serial.print(F(" - Set to: "));
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");

    Serial.println(F("\nState EEPROM"));
    Serial.print(F("EEPROM 1 : ")); Serial.println(EEPROM.read(pinRelay_1));
    Serial.print(F("EEPROM 2 : ")); Serial.println(EEPROM.read(pinRelay_2));
    Serial.print(F("EEPROM 3 : ")); Serial.println(EEPROM.read(pinRelay_3)); });
}