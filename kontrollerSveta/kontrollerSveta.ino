#include <IRremote.h>
IRrecv irrecv(11);//контакт приемника
int RELAY_PIN1 = 12;//блок питаниясветодиодной подсветки
int RELAY_PIN2 = 7;//Свет1
int RELAY_PIN3 = 8;//Свет2
int LED = 13;//Информационный светодиод
boolean Flag_rele = 0;
decode_results results;//полученные данные



void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // включаем приемник
  pinMode(LED, OUTPUT); // настраиваем реле на выход
  digitalWrite(LED, LOW); //устанавливаем высокое значение
  pinMode(RELAY_PIN1, OUTPUT); // настраиваем реле на выход
  digitalWrite(RELAY_PIN1, LOW); //устанавливаем высокое значение
  pinMode(RELAY_PIN2, OUTPUT); // настраиваем реле на выход
  digitalWrite(RELAY_PIN2, HIGH); //устанавливаем высокое значение
  pinMode(RELAY_PIN3, OUTPUT); // настраиваем реле на выход
  digitalWrite(RELAY_PIN3, HIGH); //устанавливаем высокое значение
}

void loop() {
  if (irrecv.decode(&results)) {//если получены данные
    Serial.print("0x");
    Serial.println(results.value, HEX);//вывод полученного в терминал



    if  ((results.value == 0x20DF8679) || (results.value == 0xFD00FF)) {
      digitalWrite(RELAY_PIN1, !digitalRead(RELAY_PIN1));//если код кнопки 0x8FF40BF или 0xD72040BF меняем состояние реле на противоположное
      delay(100);// задержка от двойного срабатывания
    }

    if  ((results.value == 0x20DFC639) || (results.value == 0xFD807F)) {
      digitalWrite(RELAY_PIN2, !digitalRead(RELAY_PIN2));//если код кнопки 0x8FF40BF или 0xD72040BF меняем состояние реле на противоположное
      delay(100);// задержка от двойного срабатывания
    }
    if  ((results.value == 0x20DF8E71) || (results.value == 0xFD40BF)) {
      digitalWrite(RELAY_PIN3, !digitalRead(RELAY_PIN3));//если код кнопки 0x8FF40BF или 0xD72040BF меняем состояние реле на противоположное
      delay(100);// задержка от двойного срабатывания
    }
   
    
    if  ((results.value == 0x20DF4EB1) || (results.value == 0xFD20DF)) {
      digitalWrite(RELAY_PIN1, LOW);
      digitalWrite(RELAY_PIN2, HIGH);
      digitalWrite(RELAY_PIN3, HIGH);
      Flag_rele = 1;
      delay(100);// задержка от двойного срабатывания
    }
    if  ((results.value == 0x20DFF10E) || (results.value == 0xFDA05F)) {
      digitalWrite(RELAY_PIN1, HIGH);
      digitalWrite(RELAY_PIN2, LOW);
      digitalWrite(RELAY_PIN3, LOW);
      Flag_rele = 1;
      delay(100);// задержка от двойного срабатывания
    }



    irrecv.resume();// Получаем следующее значение
  }
}
