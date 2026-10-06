#include <Arduino.h>

#define Pot_Speed 34
#define Pot_Dir 35

SemaphoreHandle_t mutex_Serial;

void Leer_velocidad(void *Parametro) {
  // put your task code here, to run repeatedly:
  for (;;) {
    int velocidad = analogRead(Pot_Speed);
    xSemaphoreTake(mutex_Serial, portMAX_DELAY); 
    Serial.print("velocidad : ");
    Serial.println(velocidad);
    xSemaphoreGive(mutex_Serial);
    vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 1 second
  }
  
}

void Distancia_colision(void *Parametro) {
  // put your task code here, to run repeatedly:
  for (;;) {
    int distancia = analogRead(Pot_Dir);
    Serial.print("Distancia ante una colision : ");
    Serial.println(distancia);
    vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 1 second
  }
  
}

void setup() {
    // put your setup code here, to run once:
  Serial.begin(115200);
  mutex_Serial = xSemaphoreCreateMutex();
  xTaskCreate(Leer_velocidad, "Leer velocidad", 2048, NULL, 1, NULL);
  xTaskCreate(Distancia_colision, "Distancia para colision", 2048, NULL, 1, NULL);

}

void loop() {
  // put your main code here, to run repeatedly:
}

