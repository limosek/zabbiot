

String fetchUrl(char *url) {
  HTTPClient http;
  http.begin(DEFAULT_PROV_URL);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (http.hasHeader("location")) {
      http.begin(http.header("location"));
      PRINT("[HTTP] New location:");
      PRINTln(http.header("location"));
    } else {
      PRINTf("[HTTP] GET code: %d\n", httpCode);
    }
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      PRINTln(payload);
      return (payload);
    } else {
      PRINTf("[HTTP] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
      delay(10000);
      Reset();
    }
  }
}

bool httpSetup() {
  
}

bool httpLoopStart() {
  
}

bool httpLoopEnd() {
  
}

