int smrv = 12;
int srv = 11;
int scv = 10;
int slv = 9;
int smlv = 8;

int counter = 0;
bool sensorsInBlack = false;

void setup() {
  Serial.begin(9600);

  pinMode(smlv, INPUT);
  pinMode(slv, INPUT);
  pinMode(scv, INPUT);
  pinMode(srv, INPUT);
  pinMode(smrv, INPUT);
}

void loop() {
  // Read the digital readings from all five sensors
  int mrv = digitalRead(smrv);
  int rv = digitalRead(srv);
  int cv = digitalRead(scv);
  int lv = digitalRead(slv);
  int mlv = digitalRead(smlv);

  // Print the readings for debugging (optional)
  Serial.print("Sensor mrv: ");
  Serial.print(mrv);
  Serial.print(" | ");

  Serial.print("Sensor rv: ");
  Serial.print(rv);
  Serial.print(" | ");

  Serial.print("Sensor cv: ");
  Serial.print(cv);
  Serial.print(" | ");

  Serial.print("Sensor lv: ");
  Serial.print(lv);
  Serial.print(" | ");

  Serial.print("Sensor mlv: ");
  Serial.println(mlv);

  // Check if all sensors are on black
  bool allSensorsOnBlack = (mrv == LOW && rv == LOW && cv == LOW && lv == LOW && mlv == LOW);

  // Check for transition from white to black
  if (allSensorsOnBlack && !sensorsInBlack) {
    // Increment the counter only once for the transition
    counter++;
    sensorsInBlack = true;  // Set the flag to true to indicate that sensors are in black
    // Print the count to the serial monitor
    Serial.print("Count: ");
    Serial.println(counter);
  } else if (!allSensorsOnBlack) {
    // Reset the flag when sensors go back to white
    sensorsInBlack = false;
  }

  // You might want to add a delay to avoid rapid counting
  delay(10);  // Adjust the delay value as needed
}
