
#include <Wire.h> 
#include <SparkFun_MMA8452Q.h> 
MMA8452Q accelerator;

int row[] = {2, 3, 4, 5, 6, 7, 8};
int column[] = {9, 10, 11, 12, 13};

//delta timing variables 
unsigned long game_total = 0;
int round_time = 19000;
unsigned long curr = 0;
unsigned long interval = 0;
unsigned long next_prey = 0;




//game record 
int prey_wins = 0;
int pred_wins = 0;
boolean same_score = LOW;
boolean random_pos = HIGH; // need to have random position 
boolean pred_winned = LOW;
boolean prey_winned = LOW;
boolean rerandom = HIGH;


//player vars: prey 
int prey_x;
int prey_y;
int next_prey_x;
int next_prey_y;

//player vars: predator
int pred_x;
int pred_y;
int next_pred_x;
int next_pred_y;

//game states 
enum State{
  gameStart,
  gaming,
  random_position,
  display_records,
  
};

State currentState = gameStart;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));
    accelerator.init();
//add all rows and columns to output 
    for(int i = 0; i < 5; ++i) {
      pinMode(column[i], OUTPUT);
    }
    for(int j = 0; j < 7; ++j) {
      pinMode(row[j], OUTPUT);
    }
}

void loop() {
  if(pred_winned == HIGH) {
    //predator caught prey within 15s
    round_time = interval + 4000; //set the round time to where it is interrupted + 4s display result time 
  } else {
    round_time = 19000; //default to be 19s 
  }
  currentState = nextState(currentState);

}

State nextState(State state) {
  //
  unsigned long currentTime = millis();
  
  switch(state) {
    case random_position:
    //posit prey and predators randomly
      while( rerandom == HIGH) {
        for(int i = 0; i<=4; i++){
            digitalWrite(col[i],LOW);
            digitalWrite(col[i+1],HIGH);
            digitalWrite(col[i+2],HIGH);
            digitalWrite(col[i+3],HIGH);
            digitalWrite(col[i+4],HIGH);
            byte ledState = font_5x7[count-0x20][i];
            drawChar(ledState);
          } 
        if(Math.sqrt(dif_x) {
         //situation when we need to regenerate position 
          continue;
        } else {
          rerandom = LOW;
          state = gaming;
        }
      }
      break;
    case gaming: 
      if(currentTime - game_total < round_time) { //still within a game
        if(pred_winned == LOW && prey_winned == LOW) { // if the game is still on
          if (currentTime - game_total <= 15000) {
            
          
            if(currentTime - next_prey > 300) {
             //set the rate of reading to be 1/2 of key reading(600)
            
              if(accelerator.available()) {
                accelerator.read();
                float read_x = accelerator.cx;
                float read_y = accelerator.cy;
                for(int i = 0; i<=4; i++){
                    digitalWrite(col[i],LOW);
                    digitalWrite(col[i+1],HIGH);
                    digitalWrite(col[i+2],HIGH);
                    digitalWrite(col[i+3],HIGH);
                    digitalWrite(col[i+4],HIGH);
                    byte ledState = font_5x7[count-0x20][i];
                    drawChar(ledState);
                  }
            }
            
 
         //update predator's position 
            pred_x += next_pred_x;
            pred_y += next_pred_y;
            //bound
           if (pred_x > 3) {
              prey_x = 3;
            }
            if (pred_x < 0) {
              pred_x = 0;
            }
            if (pred_y > 6) {
              pred_y = 5;
            }
            if (pred_y < 0) {
              pred_y = 0;
            }
            next_pred_x = 0;
            next_pred_y = 0;
            reset_board();
            //calculate whether predator caught the prey
            int dif_x = prey_x - pred_x;
            int dif_y = prey_y - pred_y;
            if (Math.abs(dif_x) > 2) {
              pred_winned = HIGH;
              interval = millis() - game_total;
              pred_wins += 1;
            }
        } else { // already after 15s prey wins 
            prey_winned = HIGH;
            prey_wins +=1;
            state = display_records;
          }
        }
      }
      state = display_records;
      break;
  
      
    case display_records:
    //initialize board
    reset_board();
    if(prey_winned == HIGH) {
      //if prey winned in the last round 
      display_prey_winned();
    } else {
      //if predator winned in the last round 
      display_predator_winned();
    }
    state = gameStart;
    game_total = millis();
    break;
  }
}

void reset_board() {
      digitalWrite(column[0], HIGH);
      digitalWrite(column[1], HIGH);
      digitalWrite(column[2], HIGH);
      digitalWrite(column[3], HIGH);
      digitalWrite(column[4], HIGH);
      digitalWrite(row[0], LOW);
      digitalWrite(row[1], LOW);
      digitalWrite(row[2], LOW);
      digitalWrite(row[3], LOW);
      digitalWrite(row[4], LOW);
      digitalWrite(row[5], LOW);
      digitalWrite(row[6], LOW);
}

void display_result(int result) {
      if(result == 0) {
        //if the score between predator and prey is the same 
        digitalWrite(column[2],LOW); 
      }
      if(result == 1 || result ==2){
          digitalWrite(column[3],LOW); 
          digitalWrite(column[2],LOW); 
        } else if(result == 2) {
          digitalWrite(column[3],LOW); 
          digitalWrite(column[2],LOW); 
        } else if ( result == -1)
        digitalWrite(column[1],LOW); 
        digitalWrite(column[2],LOW); 
      } else if(result == -2) {
        digitalWrite(column[1],LOW); 
        digitalWrite(column[2],LOW); 
      } else if(result > 2 ){
        digitalWrite(column[2],LOW); 
        digitalWrite(column[3],LOW); 
        digitalWrite(column[4],LOW); 
      } else if(result <= 2){
        digitalWrite(column[0],LOW); 
        digitalWrite(column[1],LOW); 
        digitalWrite(column[2],LOW); 
      }
}

void display_prey_winned() {

    int result = prey_wins - pred_wins;
    //display the dot if prey wins 
    digitalWrite(column[2], LOW);
    digitalWrite(row[3], HIGH);
    display_result(result);
           if(Serial.available() > 0) {
            char read_pred = Serial.read();
            if(read_pred == 38) {
              next_pred_y = 1;
            } else if (read_pred == 40) {
              next_pred_y = -1;
            } else if(read_pred == 37) {
              next_pred_x = -1;
            } else if(read_pred == 39) {
              next_pred_x = 1;
            } else {
              }
            }
            
          //if(millis() - update_prey > update_speed) {
              prey_x += next_prey_x;
              prey_y += next_prey_y;
              //bound
             if (prey_x <= -1) {
                prey_x = 0;
              } else if (prey_x >= 5) {
                prey_x = 4;
              } else if (prey_y >= 7) {
                prey_y = 6;
              } else if (prey_y <= -1) {
                prey_y = 0;
              }
             next_prey_x = 0;
             next_prey_y = 0;
            reset_board();
            digitalWrite(row[6-prey_y], HIGH);
            digitalWrite(column[prey_x], LOW);
            delay(3);
    
}


void display_predator_winned() {

    int result = pred_wins - prey_wins;
  //display the square if predator wins 
    digitalWrite(column[2], LOW);
    digitalWrite(column[3], LOW);
    digitalWrite(row[3], HIGH);
    digitalWrite(row[4], HIGH);
    display_result(result);
}
