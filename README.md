# Door-Locker-Security-System
Developing a system to unlock a door using a password.  It is designed for embedded systems applications and uses a keypad, LCD screen, External EEPROM ,buzzer, and DC motor.
The system is based on a layered architecture model with two ATmega32 Microcontrollers running @8MHz.

Project Desciption :

MC1 (HMI_ECU) : Includes a Human Machine Interface with a 2x16 LCD and a 4x4 keypad. It serves as the user's gateway to the system, allowing them to interact easily. Users can enter and confirm their passwords through the keypad and receive feedback on the 2x16 LCD.

MC2 (Control_ECU) : Manages the system with an EEPROM, Buzzer, and Dc-Motor. This control unit is responsible for all system processes and decisions. It verifies the entered passwords, saves the password into the EEPROM ,controls the motor for door locking and unlocking, and provides security measures for incorrect password attempts

System Functionality :

1. Create a System Password: User is asked to create a 5-digit password through the HMI_ECU. The system ensures password matching through a confirmation process. The validated password is stored in the EEPROM.
2. Main Options: Main menu display is shown on the LCD and the user can choose the operation he wants to do.
3. Open Door: To unlock the door, user enter his password through the keypad, the HMI_ECU sends it to the Control_ECU via UART. The system verifies the entered password with the one stored in the EEPROM. Upon a match, the door motor rotates for 15 seconds in a clockwise direction (CW) and displays a message indicating that the door is unlocking. The motor is then held for 3 seconds before rotating 15 seconds counterclockwise (A-CW), locking the door.
4. Change Password: Users can change the system password by entering the current password. The system verifies the entered password with the one stored in the EEPROM. Upon a match, users can proceed to create a new password as in Step 1.
5. Security Measures for Incorrect Password Attempts: If a user enters an incorrect password during door opening or changing password for a total of three consecutive attempts, the system activates the Alarm System for one minute , and locks the system temporarily.
