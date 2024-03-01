# Reverse-Parking-Assistance-System
Implemented by using two nodes, Node-A which acts as a dashboard control inwhich a switch is provided with external interrupt for enabling and disabling the reverse parking option. When ever we are enabling the reverse parking option(ie, switch is pressed odd number of times), the Node-A sends a remote frame to the Node-B through the CAN bus. 
Upon receiving the remote frame by the Node-B, the ultrasonic sensor attached to the Node-B gets activated and analyses the distance between the vehicle and the wall and after the successful analysis, the result of analysis is send to Node-A as data frame by Node-B.
After the reception of dataframe Node-A analyse the data and, the buzzer and LED's attached on the Node-A gets worked according to the test cases mentioned below:

1) Range Less Than 50cm
2) Range b/w 50cm & 100cm
3) Range b/w 100cm & 200cm
4) Range b/w 200cm & 300cm

Software Used: Keil uVision5

The results can be analysed using the uart window, GPIO window, CAN communication window, tool box window, memory window and watch window options in the Keil uVision5.

Node A:
![Node A Window](https://github.com/officialmeliorate/Reverse-Parking-Assistance-System-Using-CAN/assets/157610672/97aede7e-b896-48c5-8244-2690f9c25db6)

Node B:
![Node B Window](https://github.com/officialmeliorate/Reverse-Parking-Assistance-System-Using-CAN/assets/157610672/d2811923-4d8e-4627-8bf5-86e26e4a438b)
