char receivedChar;

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        Serial.print("Received:[");
        if(receivedChar!='\n')
            Serial.print(receivedChar);
        else
            Serial.print("\\n");
        Serial.println("]");
    }
    Serial.println("Waiting for input");
    delay(1000);
}
