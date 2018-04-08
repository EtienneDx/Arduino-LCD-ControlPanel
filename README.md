# Arduino-LCD-ControlPanel

I've been working on different little project lately, and had a need of some sort of controller. I therefore decided to create my own, a LCD solution, and I then turned it into a little library, in case anyone else can use it.

## What is this ?

This is a simple library that allow you to create a menu on a LCD screen, using (for now) three button input, which I'll soon change to a rotary encoder. The screen size can vary, as long as it has I2C connectors.
With this system, you can have, for now, labels, int fields, toggle fields, and buttons with callback.

## How does it work ?

Simply import the two files "menu.h" and "menu.cpp" into your project folder, and add this code to your main .ino file :

    #import "menu.h"
    
    #define ITEM_COUNT 4
    MenuItem items[ITEM_COUNT]{
      { MENU_LABEL, "Controller"},
      { MENU_INT, "Some int", 5, 0, 10 },
      { MENU_BUTTON, "Some Button", &callback },
      { MENU_TOGGLE, "Toggle : " }, 
    };
    
    // the lcd adress, column count, row count, a pointer to the first item and the number of items
    Menu menu(0x27, 16, 2, &items[0], ITEM_COUNT);
    
    void setup()
    {
      //...
      menu.init();// needed to init the lcd
      //...
    }

Here are the different Menu Items : 

    { MENU_LABEL, "your label" }
    { MENU_INT, "your label", BASE_VALUE, MIN, MAX, STEP }
    { MENU_BUTTON, "your label", &callback } // callback being the name of a void function
    { MENU_TOGGLE, "your label" }

You need however to specify how many items you have when creating the menu (as specified above)

To access the value, simply get the field "value" from the object. For example : 

    #define ITEM_COUNT 1
    MenuItem items[ITEM_COUNT]{
      { MENU_TOGGLE, "Toggle" }// only one field
    };
    
    void loop() {
      digitalWrite(13, items[0].value);
    }
    
You can find more examples in the provided ino file ("ControlPanel.ino")

For the inputs, you can use either a rotary encoder or three different buttons : 

    //first solutions : three buttons
    #define NEXT_BUTTON 2
    #define PREV_BUTTON 4
    #define MAIN_BUTTON 3
    
    Menu menu(0x27, 16, 2, &items[0], ITEM_COUNT, BUTTONS_MENU, NEXT_BUTTON, PREV_BUTTON, MAIN_BUTTON);
    
    //second solution : rotary encoder
    //I haven't been able to test this since I don't own any rotary encoder for the time being, but it should work...
    #define PIN_A 2
    #define PIN_B 4
    #define BUTTON_PIN 3
    
    Menu menu(0x27, 16, 2, &items[0], ITEM_COUNT, ROTARY_ENCODER_MENU, PIN_A, PIN_B, BUTTON_PIN);
    

## Other Infos

You can disable and re-enable the menu simply : 
    
    menu.disable();
    menu.enable();
    
This allows you to take over the lcd to make, for example, a loading screen or something : 

    menu.disable();
    menu.lcd.clear();
    menu.lcd.setCursor(0, 0);
    for(int i = 0; i < 16; i++)
    {
      menu.lcd.print("#");
      delay(50);
    }
    
For any other questions, contact me at etiennedx00@gmail.com
