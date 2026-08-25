# Development Log

This log documents everything from start to end of this arm.


## PHASE 0 -- Initial Prototype
### Beginning the arm

I started this project by building a small robotic arm using an Arduino Uno
and servo motors.

### Goal

The goal was to create a robotic arm that could be controlled manually
using joysticks.


## PHASE 1 -- Initial Hardware Testing
### Testing components

Check all the servos, joysticks before beginning the project. Wire them individually and then run test codes. The goal was just to make sure before beginning if i needed to change any components.

### First Design

After the hardware was tested and working, I started to think about ideas for mechanical design. I came up with popsicle sticks because anything wrong can easily be fixed. It was the most simple and inexpensive design.

This became the first working version of the arm.


## PHASE 2 -- Programming and power 

### First Control Program

After building the initial popsicle-stick arm, I started writing the Arduino
code to control the servo motors.

The goal was to control the different joints of the arm using joystick input.

### First Major Problem — Power Supply

Once I started testing multiple servo motors at the same time, I realized
that choosing the correct power source was important.

The Arduino could not be expected to provide enough current for all of the
servos, especially when multiple motors were moving at the same time.

I experimented with powering the servos separately while keeping the Arduino
and servo power supply connected through a common ground.

This became one of the first major hardware challenges of the project.


## Phase 3 — Servo Problems and Debugging

### The Biggest Problem

After adding an external power supply, I encountered the biggest problem
with the project so far.

The servos would sometimes:

- Jitter unexpectedly
- Freeze while moving
- Move unpredictably
- Stop responding correctly
- Occasionally behave differently after extended use

As a beginner, I initially didn't know what was causing these problems.

### Debugging

I spent a significant amount of time testing different parts of the system
to figure out why the servos were not behaving consistently.

After a lot of troubleshooting I asked for help on reddit and thankfully my problem was solved
after making changes to the joystick deadzone and servo speed for stability.

This problem took several months to work through because I was still
learning how servo motors, power supplies, Arduino control signals, and
electronics worked together.


## Phase 4 — Completing the First Version

### Reassembling and Strengthening the Arm

After solving the servo problems, I reassembled the robotic arm and made the
structure stronger and more stable.

### Adding the Claw

I added a claw to the end of the arm, giving it the ability to grip objects.

### Adding the Home Position Feature

I added a feature that allowed the arm to return to its home position.

Instead of all the servos suddenly moving at the same time, the joints
returned to their home positions one by one. This made the reset movement
more controlled and predictable.

### First Version Complete

After the mechanical assembly, programming, and testing were completed, I
recorded the robotic arm operating successfully.

This marked the completion of the first version of the project and gave me
a working foundation to build on in the future.
