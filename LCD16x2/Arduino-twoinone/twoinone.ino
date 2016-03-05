#include <lcd.h>

enum graphics {
  HEAD = 0x00,
  RUN1 = 0x01,
  RUN2 = 0x02,
  HEAD_JUMP = 0x03,
  BODY_JUMP = 0x04,
};

enum settings {
  SPEED = 250,
};

enum modes {
  GAME,
  SENSOR,
};

volatile int mode = GAME;  // Start in game mode

volatile int button_pressed = 0;

// Game variables
uint8_t obstacle;  // Katakana character
int obstacle_block;  // Block number for obstacle
int score = 0;  // Player score
int frame_speed = SPEED;  // Delay between frames (lower number = faster game speed)
int idle_count;  // If player is idle in game, switch to sensor mode

// Sensor variables
int photocell = 0;
int photocellReading;
int led = 13;
int temp = 1;
int tempReading;

void setup() {
  attachInterrupt(0, button_press, FALLING);
  digitalWrite(2, HIGH);  // Internal pull-up
  pinMode(led, OUTPUT);
  
  lcd_init();
  lcd_cursor_off();
  
  // Game setup
  load_graphics();
}

void loop() {
  obstacle = 0xA5;  // Before first katakana character (will be incremented)
  score = 0;
  frame_speed = SPEED;
  lcd_clear();
  draw_score();
  while (mode == GAME) {
    // Run 5 times before next obstacle appears
    for (int i = 0; i < 5; i++) {
      draw_head(HEAD);
      draw_body(RUN1);
      frame_delay();
      
      if (button_pressed == 1) {
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        frame_delay();
        draw_head(RUN1);
        draw_body(0x20);
        frame_delay();
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        frame_delay();
        draw_head(HEAD);
        draw_body(RUN1);
        frame_delay();
        button_pressed = 0;
      }
      
      draw_head(HEAD);
      draw_body(RUN2);
      frame_delay();
      
      if (button_pressed == 1) {
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        frame_delay();
        draw_head(RUN1);
        draw_body(0x20);
        frame_delay();
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        frame_delay();
        draw_head(HEAD);
        draw_body(RUN1);
        button_pressed = 0;
      }
    }
    
    create_obstacle();  // Incoming katakana character!
    
    while (obstacle_block > 0) {
      draw_head(HEAD);
      draw_body(RUN1);
      shift_obstacle();
      possible_loss();  // The player may have been hit by the obstacle
      frame_delay();
      
      if (button_pressed == 1) {
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        shift_obstacle();
        possible_loss();
        frame_delay();
        draw_head(RUN1);
        draw_body(0x20);
        shift_obstacle();
        possible_loss();
        frame_delay();
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        shift_obstacle();
        possible_loss();
        frame_delay();
        draw_head(HEAD);
        draw_body(RUN1);
        shift_obstacle();
        possible_loss();
        frame_delay();
        button_pressed = 0;
      }
      
      draw_head(HEAD);
      draw_body(RUN2);
      shift_obstacle();
      possible_loss();
      frame_delay();
      
      if (button_pressed == 1) {
        draw_head(HEAD_JUMP);
        draw_body(BODY_JUMP);
        shift_obstacle();
        possible_loss();
        frame_delay();
        draw_head(RUN1);
        draw_body(0x20);
        shift_obstacle();
        // This is the only possible place the player can avoid the obstacle
        if (obstacle_block == 0) {
          score++;
          frame_speed = SPEED - score;
          draw_score();
          frame_delay();
          shift_obstacle();
          draw_head(HEAD_JUMP);
          draw_body(BODY_JUMP);
          frame_delay();
        } else {
          frame_delay();
          draw_head(HEAD_JUMP);
          draw_body(BODY_JUMP);
          shift_obstacle();
          possible_loss();
          frame_delay();
          draw_head(HEAD);
          draw_body(RUN1);
          shift_obstacle();
          possible_loss();
        }
        button_pressed = 0;
      }
    }
    
    // Standing around getting hit by katakana characters is considered being idle
    if (score == 0) {
      idle_count++;
    }
    
    // Player has been idle for too long, switch to sensor mode
    if (idle_count >= 2) {
      mode = SENSOR;
    }
  }

  lcd_write1("Light: ");
  lcd_write2("Temp: ");
  while (mode == SENSOR) {
    photocellReading = analogRead(photocell);
    tempReading = analogRead(temp);
    float tempmv = tempReading * (5000.0/1024.0);
    float tempc = (tempmv - 500.0) / 10.0;
    
    char lightstr[4];
    snprintf(lightstr, 4, "%d", photocellReading);
    update_light(lightstr);
    
    char tempstr[3];
    snprintf(tempstr, 3, "%d", int(tempc));
    update_temp(tempstr);
    
    if (photocellReading < 580) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }
    
    delay(500);
  }
}

/*
 Interrupt service routine for button press
 */
void button_press() {
  delay(10);  // Delay 10 ms for debouncing
  // Make sure it's a press down, not lift up with bounce
  if (digitalRead(2) == HIGH) {
    button_pressed = 0;  // False detection
  }
  if (mode == GAME) {
    button_pressed = 1;  // Button press detected
    idle_count = 0;  // Reset idle counting
  } else {  // mode == SENSOR
    mode = GAME;  // Switch to game mode
  }
}

/*
 Delay for the length of one frame
 */
void frame_delay() {
  delay(frame_speed);
}

/*
 Draw the player's head, given the style
 */
void draw_head(uint8_t head) {
  lcd_cmd(0x80);  // Set DDRAM address to 0x00
  lcd_data(head);
}

/*
 Draw the player's body, given the style
 */
void draw_body(uint8_t body) {
  lcd_cmd(0xC0);  // Set DDRAM address to 0x40
  lcd_data(body);
}

/*
 Draw score at top right
 */
void draw_score() {
  lcd_cmd(0x87);  // Set DDRAM address to 0x07
  char scorestr[10];
  snprintf(scorestr, 10, "Score: %d", score);
  if (score < 10) {  // Formatting
    scorestr[8] = ' ';
  }
  for (int i = 0; i < 9; i++) {
    lcd_data(scorestr[i]);
  }
}

/*
 Create a given character as an obstalce
 */
void create_obstacle() {
  // Next katakana character
  obstacle++;
  if (obstacle > 0xDD) {
    obstacle = 0xA6;
  }
  obstacle_block = 16;  // Set global variable
}

/*
 Shift obstacle one block to the left
 */
void shift_obstacle() {
  lcd_cmd(0xC0 | obstacle_block);  // Clear current block
  lcd_data(0x20);
  obstacle_block = max(obstacle_block-1, 0);
  lcd_cmd(0xC0 | obstacle_block);  // Draw obstacle on next block (left)
  lcd_data(obstacle);
}

/*
 The player may be getting hit by the obstacle, which is a loss
 */
void possible_loss() {
  if (obstacle_block == 0) {
    score = 0;
    draw_score();
    delay(1000);
  }
}

/*
 Update the light number on LCD
 */
void update_light(char *s) {
  lcd_cmd(0x87);  // 3 digits starting at address 0x07
  lcd_data(*s++);
  lcd_data(*s++);
  lcd_data(*s);
}

/*
 Update the temperature on LCD
 */
void update_temp(char *s) {
  lcd_cmd(0xC6);  // 2 digits starting at address 0x46
  lcd_data(*s++);
  lcd_data(*s);
}

/*
 Load the custom graphics into CGRAM
 */
void load_graphics() {
  // HEAD at CGRAM 0x00
  lcd_cmd(0x40);  // Set CGRAM address 0x00
  lcd_data(0x1F);
  lcd_cmd(0x41);  // Set CGRAM address 0x01
  lcd_data(0x11);
  lcd_cmd(0x42);  // Set CGRAM address 0x02
  lcd_data(0x13);
  lcd_cmd(0x43);  // Set CGRAM address 0x03
  lcd_data(0x11);
  lcd_cmd(0x44);  // Set CGRAM address 0x04
  lcd_data(0x17);
  lcd_cmd(0x45);  // Set CGRAM address 0x05
  lcd_data(0x11);
  lcd_cmd(0x46);  // Set CGRAM address 0x06
  lcd_data(0x1F);
  lcd_cmd(0x47);  // Set CGRAM address 0x07
  lcd_data(0x04);
  
  // RUN1 at CGRAM 0x01
  lcd_cmd(0x48);  // Set CGRAM address 0x08
  lcd_data(0x05);
  lcd_cmd(0x49);  // Set CGRAM address 0x09
  lcd_data(0x07);
  lcd_cmd(0x4A);  // Set CGRAM address 0x0A
  lcd_data(0x1C);
  lcd_cmd(0x4B);  // Set CGRAM address 0x0B
  lcd_data(0x14);
  lcd_cmd(0x4C);  // Set CGRAM address 0x0C
  lcd_data(0x04);
  lcd_cmd(0x4D);  // Set CGRAM address 0x0D
  lcd_data(0x04);
  lcd_cmd(0x4E);  // Set CGRAM address 0x0E
  lcd_data(0x0A);
  lcd_cmd(0x4F);  // Set CGRAM address 0x0F
  lcd_data(0x11);
  
  // RUN2 at CGRAM 0x02
  lcd_cmd(0x50);  // Set CGRAM address 0x10
  lcd_data(0x04);
  lcd_cmd(0x51);  // Set CGRAM address 0x11
  lcd_data(0x17);
  lcd_cmd(0x52);  // Set CGRAM address 0x12
  lcd_data(0x1D);
  lcd_cmd(0x53);  // Set CGRAM address 0x13
  lcd_data(0x04);
  lcd_cmd(0x54);  // Set CGRAM address 0x14
  lcd_data(0x04);
  lcd_cmd(0x55);  // Set CGRAM address 0x15
  lcd_data(0x04);
  lcd_cmd(0x56);  // Set CGRAM address 0x16
  lcd_data(0x0A);
  lcd_cmd(0x57);  // Set CGRAM address 0x17
  lcd_data(0x0A);
  
  // HEAD_JUMP at CGRAM 0x03
  lcd_cmd(0x58);  // Set CGRAM address 0x18
  lcd_data(0x11);
  lcd_cmd(0x59);  // Set CGRAM address 0x19
  lcd_data(0x17);
  lcd_cmd(0x5A);  // Set CGRAM address 0x1A
  lcd_data(0x11);
  lcd_cmd(0x5B);  // Set CGRAM address 0x1B
  lcd_data(0x1F);
  lcd_cmd(0x5C);  // Set CGRAM address 0x1C
  lcd_data(0x04);
  lcd_cmd(0x5D);  // Set CGRAM address 0x1D
  lcd_data(0x05);
  lcd_cmd(0x5E);  // Set CGRAM address 0x1E
  lcd_data(0x07);
  lcd_cmd(0x5F);  // Set CGRAM address 0x1F
  lcd_data(0x1C);
  
  // BODY_JUMP at CGRAM 0x04
  lcd_cmd(0x60);  // Set CGRAM address 0x20
  lcd_data(0x14);
  lcd_cmd(0x61);  // Set CGRAM address 0x21
  lcd_data(0x04);
  lcd_cmd(0x62);  // Set CGRAM address 0x22
  lcd_data(0x04);
  lcd_cmd(0x63);  // Set CGRAM address 0x23
  lcd_data(0x0A);
  lcd_cmd(0x64);  // Set CGRAM address 0x24
  lcd_data(0x11);
  lcd_cmd(0x65);  // Set CGRAM address 0x25
  lcd_data(0x00);
  lcd_cmd(0x66);  // Set CGRAM address 0x26
  lcd_data(0x00);
  lcd_cmd(0x67);  // Set CGRAM address 0x27
  lcd_data(0x00);
}
