# SG90 Micro Servo Motor

With my [SG90 micro servo motor](https://handsontec.com/dataspecs/motor_fan/SG90-Servo.pdf) (&mu;SM), I have explored the different possible ways to control and integrate it for my various Internet-of-Things (IoT) projects. In this section, I summarize the different functionalities I experimented with links leading to a detailed explanation of the circuitry and code.

## SG90 &mu;SM rotation controlled by a 10-k&ohm; potentiometer knob 
&#128279;_Click the link_ [_here_](https://github.com/machinedeck/SG90-Micro-Servo-Motor-with-Potentiometer/tree/main/Activity-1) _to go to the individual project._

This project is concerned about manually rotating the &mu;SM using a potentiometer knob. The potentiometer is connected to a 5V rail, and has an output voltage that depends on the knob's rotated position. This 0-5V output range undergoes an equivalent conversion to pulse width range of 550-2400 &mu;s, which achieves SG90's shaft rotation of up to 180&deg;.
