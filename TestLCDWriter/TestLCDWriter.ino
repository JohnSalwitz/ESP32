//
// Tests the LCD writer AND Dual Threads on ESP32
//


#include "LCDWriter.h"

TaskHandle_t Task1;
TaskHandle_t Task2;
static int _linecount = 0;

// LED pins
const int led1 = 2;
const int led2 = 4;

void setup() {
  
  Serial.begin(115200); 
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  LCDWriter.Init();
  for(int row = 0; row < LCD_ROWS;row++)
  {
    LCDWriter.WriteRow(row, "12345678901234567890");
    LCDWriter.Render();
    delay(700);
  }

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    BackgroundTask,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 2 and executed on core 1
  xTaskCreatePinnedToCore(
                    ForegroundTask,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 

  
}

// prints short form of up-time (03:05:01:00)
const char *logger_time()
{
    static char _timeBuffer[128];
    long seconds = ((long)millis() + 500L) / 1000L;
    int days = (int)(seconds / (24L * 60L * 60L));
    seconds -= (long)(days * 24 * 60 * 60);
    int hours = (int)(seconds / (60L * 60L));
    seconds -= (long)(hours * 60 * 60);
    int minutes =  (int)(seconds / 60L);
    seconds -= (long)(minutes * 60);
  
    sprintf(_timeBuffer,"%02d:%02d:%02d:%02d",days, hours, minutes, seconds);
    return _timeBuffer;
}


// Task1code: blinks an LED every 1000 ms and injects new message.
void BackgroundTask( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    delay(500);

    LCDWriter.WriteRow(0, logger_time());
    char buffer[20];
    sprintf(buffer,"New Line: %d", _linecount++);
    LCDWriter.WriteLn(buffer);   
  } 
}

// Updates the lcd display in foreground.
void ForegroundTask( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    LCDWriter.Render();
    delay(100);
  }
}

void loop() {
  
}
