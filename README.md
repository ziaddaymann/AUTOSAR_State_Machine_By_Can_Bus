# State_Machine_By_Can_Bus

ECU 1 has the following functionality: 
a. Read the input switches (the on-board switches). 
b. Send a command on the CAN network based on the switch's states. 
c. SW1 & 2controls ECU2. 
d. ECU 1 sends a message each 500 ms
ECU 2 has the following functionality 
a. ECU 2 State machine are periodic tasks with 10ms periodicities
b. Read the commands from the CAN networks. 
c. Execute the state machine as the following: 
- Move to the next state (clockwise) whenever the SW1 is pressed
- Move to the next state (anticlockwise) whenever the SW2 is pressed
- If both are pressed. The output on both ECUs will return to (RED)
d. If no state change was identified for more than 5 seconds ECU should go to IDLE state(WHITE)

