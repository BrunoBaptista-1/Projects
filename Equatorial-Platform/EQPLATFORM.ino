
#include <AccelStepper.h>
#include <LiquidCrystal.h>

//----------------MOTOR CONFIG-------------------
#define STEP_PIN 3
#define DIR_PIN 2

#define END_TRACK_BUTTON 5
//#define END_REVERSE_BUTTON 5
#define START_BUTTON 8

#define CONFIG_SPEED_BUTTON 14  //A0
#define SPEED_MOTOR_UP 15       //A1
#define SPEED_MOTOR_DOWN 16     //A2
#define MODE_UP 17              //A3
#define MODE_DOWN 18            //A4

AccelStepper stepper01(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
//-----------------------------------------

//---------------LCD CONFIG----------------
LiquidCrystal lcd(13, 12, 10, 9, 7, 6);
//-----------------------------------------


//---------------VARIABLES-----------------
int start = 0;          //button that helps control start/stop functionality
int end_of_track = 0;   //button that indicates that tracking plate has finished tracking
//int begin_of_track = 0; //button that indicates that the plate has finished reset and returned to initial position
int enabled = 0;        //control variable for start/stop functionality

int config_button = 0;  ///////////
int mode_speed = 1;     ///////

bool was_pressed = false;           //boolean variable for start/stop feature, to call response functions without delay
bool reached_track_limit = false;   //variable for reaching track limit, to reverse
bool is_reversing = false;          //variable that will show the current track state when resuming tracking

bool configure_speed = false; ///////
bool settings = false;        ///////
bool update_speed_up = false;
bool update_speed_down = false;
bool update_mode_up = false;
bool update_mode_down = false;

unsigned long millis_timer, update_state_timer, config_timer;
unsigned long lcd_settings_timer, speed_up_timer, speed_down_timer, mode_up_timer, mode_down_timer;
int button_delay = 300;

int tracking_speed = 150;
int reverse_speed = -2000;
int temp_speed = 0;
//------------------------------------------

void tracking(){

  stepper01.setSpeed(tracking_speed);
  is_reversing = false;
  reached_track_limit = true;
  update_state_timer = millis();

}

void reverse(){
  
  stepper01.setSpeed(reverse_speed);
  is_reversing = true;
  reached_track_limit = true;
  update_state_timer = millis();

}

void pause(){

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Paused");

  enabled = 0;

  stepper01.stop();

}

void resume(){
  
  lcd.clear();
  lcd.setCursor(0, 0);

  if(is_reversing){
    lcd.print("Reversing");
    stepper01.setSpeed(reverse_speed);
  }else{
    lcd.print("Tracking");
    stepper01.setSpeed(tracking_speed);
  }
  enabled = 1;

}

void update_lcd(){

  lcd.clear();
  lcd.setCursor(0, 0);
  if(enabled){
    is_reversing ? lcd.print("Reversing") : lcd.print("Tracking");
  }
  else{
    pause();
  } 

}

void begin_config(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set speed: ");
  lcd.print(temp_speed);
  lcd.setCursor(0, 1);
  lcd.print("Mode: ");
  lcd.print(mode_speed);
  settings = true;
}

void apply_changes(){
  tracking_speed = temp_speed;
  stepper01.setSpeed(tracking_speed);
  update_lcd();
}

void setup(){

  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  stepper01.setMaxSpeed(4000);
  stepper01.setSpeed(1000);

  //initialize end of track and end reverse buttons and start button
  pinMode(END_TRACK_BUTTON, INPUT_PULLUP); //when button is pressed, it means that it has finished the EQ tracking process, meaning it will start reversing 
  //pinMode(END_REVERSE_BUTTON, INPUT_PULLUP); //when button is pressed, it means that it is ready to start tracking again.
  pinMode(START_BUTTON, INPUT_PULLUP);


  //SPEED CONFIG BUTTONS
  pinMode(CONFIG_SPEED_BUTTON,INPUT_PULLUP);
  pinMode(SPEED_MOTOR_UP,INPUT_PULLUP);
  pinMode(SPEED_MOTOR_DOWN,INPUT_PULLUP);
  pinMode(MODE_UP,INPUT_PULLUP);
  pinMode(MODE_DOWN,INPUT_PULLUP);


  lcd.begin(16, 2); //Initialize screen
  lcd.setCursor(0, 0); //Place cursor on screen
  lcd.print("Press start");
    
}

void loop(){

  //START/STOP MODE
  start = digitalRead(START_BUTTON);
  if(start == LOW){
    was_pressed = true;
    millis_timer = millis();
  }
  if(was_pressed && millis() - millis_timer >= button_delay){

    if(!settings)
      enabled ? pause() : resume();
    // on startup, tracking won't be enabled, therefore first button press will start tracking.
    // if start/stop button was pressed after tracking process was enabled, it will pause tracking process. Pressing this same button again resumes it.

    was_pressed = false;

  }

  //TRACKING MODE
  if(enabled){

    end_of_track = digitalRead(END_TRACK_BUTTON);     //check if reached end of track, to start reversing
    if(end_of_track == LOW)
      pause();
      //reverse();
    
    
    /*
    begin_of_track = digitalRead(END_REVERSE_BUTTON); //check if reached reversing to starting position
    if(begin_of_track == LOW)
      tracking();
    
    if(reached_track_limit && millis() - update_state_timer >= button_delay){

      update_lcd();
      reached_track_limit = false;

    }
    */
    stepper01.runSpeed();
    
  }

  //SETTINGS MODE
  config_button = digitalRead(CONFIG_SPEED_BUTTON);
  if(config_button == LOW){
    configure_speed = true;
    config_timer = millis();
  }
  if(configure_speed && millis() - config_timer >= button_delay){
    if(settings){
      settings = false;
      apply_changes();
    }else{
      settings = true;
      temp_speed = tracking_speed;
      lcd_settings_timer = millis();
    }
    configure_speed = false;
  }
  if(settings){
    // constantly update speed, depending on 100, 10 or 1 mode
    // update lcd screen and update info
    // when pressed same button again, should set new speed and exit
    if(millis() - lcd_settings_timer >= button_delay){
      begin_config();
      lcd_settings_timer = millis();
    }

    if(digitalRead(SPEED_MOTOR_UP) == LOW){
      speed_up_timer = millis();
      update_speed_up = true;
    }
    else if(digitalRead(SPEED_MOTOR_DOWN) == LOW){
      speed_down_timer = millis();
      update_speed_down = true;
    }
    else if(digitalRead(MODE_UP) == LOW){
      mode_up_timer = millis();
      update_mode_up = true;
    }
    else if(digitalRead(MODE_DOWN) == LOW){
      mode_down_timer = millis();
      update_mode_down = true;
    }   

    if(update_speed_up && millis() - speed_up_timer >= button_delay){
      update_speed_up = false;
      temp_speed = temp_speed + mode_speed;
    }
    else if(update_speed_down && millis() - speed_down_timer >= button_delay){
      update_speed_down = false;
      temp_speed = temp_speed - mode_speed;
    }
    else if(update_mode_up && millis() - mode_up_timer >= button_delay){
      update_mode_up = false;
      if(mode_speed != 100)
        mode_speed = mode_speed * 10;
    }
    else if(update_mode_down && millis() - mode_down_timer >= button_delay){
      update_mode_down = false;
      if(mode_speed != 1)
        mode_speed = mode_speed/10;
    }

  }
}


