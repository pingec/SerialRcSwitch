# SerialRcSwitch
Allows to trigger rc-switch tx command sending via serial port (via Arduino)

![demo](https://github.com/pingec/SerialRcSwitch/blob/master/demo/demo.gif?raw=true)

## Instructions
- install RCSwitch as an arduino library (copy the folder to the arduino libraries folder)
- flash arduino
- trigger commands on serial port (9600 baud)

### Syntax
    Supported commands on 9600 baud serial:
    ON(<int>,<int>) - where int is a digit between 1 and 4
    OFF(<int>,<int>) - where int is a digit between 1 and 4
    For example: OFF(2,4)
    Terminate command (line) with either CR or LF, not both.

## Dependencies 
- depends on rc-switch https://code.google.com/p/rc-switch/ https://github.com/sui77/rc-switch





