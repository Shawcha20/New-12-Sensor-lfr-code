# STM32 Line Following Robot with Maze Solving

🏆 **Champion — BITFest Line Follower Robot Contest, Department of CSE, KUET**

A line following robot built around an STM32F103C8T6 (Blue Pill), with an IR
sensor array read through a multiplexer, PD-based line tracking, ultrasonic
obstacle avoidance, and a path-planning mode for maze solving. Built by a team
of three as our fifth line follower — and the first one on STM32.

<!-- Put your photo at images/robot.jpg (create the folder in the repo root).
     Rename below if you use a different filename or extension. -->
<p align="center">
  <img src="lfr image.jpg" alt="Line following robot" width="480">
</p>

---

## Specifications

| Component | Detail |
|---|---|
| Microcontroller | STM32F103C8T6 (Blue Pill) |
| Line sensors | 12× TCRT5000 IR, read via a 16-channel multiplexer |
| Distance sensors | 3× ultrasonic (front, left, right) |
| Motors | 25GA geared, 1000 RPM, with quadrature encoders |
| Motor drivers | 2× BTS7960 |
| Display | 128×64 OLED |
| Controls | 6 push buttons + rotary encoder |
| Memory | External EEPROM for storing calibration and tuning |
| Control algorithm | PD controller with path planning |

Using a multiplexer to read the sensor array is what makes 12 sensors practical
on a Blue Pill — instead of consuming 12 ADC pins, the array is scanned through
a single analog input with a few digital select lines.

---

## Repository layout

These are Arduino `.ino` tabs. When the sketch is opened, the file matching the
folder name is the main sketch and all other tabs are concatenated after it, so
they share one global scope. Each tab groups one area of functionality.

| File | Purpose |
|---|---|
| `line_following_robot_code_with_maze_solver.ino` | Main sketch — setup, mode selection, main loop |
| `reading.ino` | Multiplexer scanning and IR array sampling |
| `calibration.ino` | Sensor calibration; min/max per channel, stored to EEPROM |
| `line_follow.ino` | Core PD line following |
| `line_follow_right.ino` | Right-hand-rule variant for maze traversal |
| `line_obstacle.ino` | Line following combined with obstacle handling |
| `obstacle.ino` | Obstacle detection and avoidance manoeuvres |
| `sonar.ino` | Ultrasonic ranging for the three sensors |
| `motor.ino` | BTS7960 PWM control and differential drive |
| `button_function.ino` | Button and rotary encoder handling, OLED menu |
| `bluetooth.ino` | Wireless control and telemetry |

---

## How it works

**Reading the line.** The 12 IR sensors are scanned in sequence through the
multiplexer, and each reading is normalised against the per-sensor calibration
values. A weighted average across the array gives the robot's lateral position
relative to the line, which becomes the error term for the controller.

**Following it.** A PD controller turns that error into a differential speed
command for the two motors. The proportional term corrects the current offset;
the derivative term damps the oscillation that pure proportional control
produces at speed — which is what lets the robot run fast without weaving.

**Calibration.** Before a run, the robot sweeps across the line while recording
the minimum and maximum reading for every sensor. This is what makes it robust
to different track surfaces and ambient lighting, and the values persist in
EEPROM so calibration survives a power cycle.

**Obstacles.** The three ultrasonic sensors detect blockages on the track. When
one is found, the robot leaves the line, drives around the obstacle, and
reacquires the line on the far side.

**Maze solving.** For maze sections the robot applies a wall-following rule
(see `line_follow_right.ino`) to explore, recording the turn sequence taken.
That path is then simplified so subsequent runs can take the direct route
rather than repeating dead ends.

---

## Controls

The six buttons and rotary encoder drive a menu on the OLED, so speed, gains,
and mode can be adjusted at the track without reflashing — which matters in a
contest, where you get very little time between runs to react to how the track
actually behaves.

---

## Build and flash

Requires the Arduino IDE with the **STM32duino** core (or PlatformIO).

1. Board: *Generic STM32F1 series* → *BluePill F103C8*
2. Upload method: STLink, or serial via a USB-TTL adapter with BOOT0 set high
3. Open `line_following_robot_code_with_maze_solver.ino` — the other tabs load
   automatically
4. Flash

Note that many Blue Pill boards ship without a working USB bootloader, so an
STLink is the reliable option.

---

<p align="center">
  <img src="images/contest.jpg" alt="BITFest contest" width="480">
</p>

---

## Team

Built with [Amit Kairy](https://www.linkedin.com/in/amit-kairy-696b7016b/) and
Shihabul Ahsan, Department of CSE, KUET.

