/*
 * Copyright (C) 2021 Alessandro Ramos da Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include "DHT.h"

#define DHTPIN A0 // Pino do sensor
#define DHTTYPE DHT11 // Tipo do senor

const int relePin = 12; // Pino do rele

const float MINIMA = 17; // Temperatura minima para acionamento
const float MAXIMA = 19; // Temperatura para parar aquecimento

float temperatura = 0;
int aquecendo = 0; // Controla se ja esta aquecendo

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  // Inicializa serial
  Serial.begin(9600); 
  
  // Inicializa rele
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, HIGH); // Desliga

  // Inicializa sensor
  dht.begin();  
}

void loop(){  
  // Le a temperatura do sensor
  temperatura = dht.readTemperature(); 
  
  // Exibe informacoes
  mostrarInfo();
  
  // Verifica se deve aquecer ou parar
  if ((temperatura <= MINIMA) && !aquecendo) {
   aquecer(1);
  } else if ((temperatura >= MAXIMA) && aquecendo) {
   aquecer(0);
  }
  
  // Aguarda 5 segundos para proxima leitura
  delay(5000);
}

void mostrarInfo() {
  Serial.print("Temperatura = ");
  Serial.print(temperatura);
  Serial.println(" oC");
  Serial.print("Aquecendo = ");
  Serial.println(aquecendo ? "SIM" : "NAO");
}

void aquecer(int ativo) {
  aquecendo = ativo;
  
  // Aciona o rele
  if (ativo)
    digitalWrite(relePin, LOW);
  else
    digitalWrite(relePin, HIGH);
}
