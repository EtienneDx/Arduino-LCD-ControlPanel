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

For the input part, one way is to use three buttons : 

    /******Buttons*******/
    #define NEXT_BUTTON 2
    #define PREV_BUTTON 4
    #define MAIN_BUTTON 3
    int lastN = LOW;
    int lastP = LOW;
    int lastM = LOW;
    
    
    void setup()
    {
      menu.init();
      pinMode(NEXT_BUTTON, INPUT);
      pinMode(PREV_BUTTON, INPUT);
      pinMode(MAIN_BUTTON, INPUT);
    }
    
    void loop()
    {
      // read buttons value
      int n = digitalRead(NEXT_BUTTON);
      int p = digitalRead(PREV_BUTTON);
      int m = digitalRead(MAIN_BUTTON);
      
      // compare with last values, and if needed, update the menu
      if (n != lastN && n)
        menu.nextLine();
      if (p != lastP && p)
        menu.prevLine();
      if (m != lastM && m)
        menu.selectLine();
      
      //update the last values
      lastN = n;
      lastP = p;
      lastM = m;
      
      delay(20);
    }
    
Another way would be to use a rotary encoder. I'll post the code as soon as I get one.

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
