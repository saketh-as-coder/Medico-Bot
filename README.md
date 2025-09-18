Medico Bot uses Arduino to simplify medication management and ensure adherence to prescribed schedules. The system integrates an RTC (Real-Time Clock) module for precise timing, an LCD screen for user-friendly schedule setup and information display, LEDs for visualalerts, and a buzzer for audible reminders. At predefined times, the dispenser opens the compartment of the container containing the correct medicine, accompanied by notifications via LEDs and the buzzer to alert the user.


## MODEL:
 1. Areal time clock embedded in Arduino is used to keep track of the current time.
 2. Buzzer and LED are used to provide auditory and visual alerts to notify the patient when it’s time to take medication.
 3. A Servo Motor controls the mechanism that indicates correct medicine. Only the compartment which has correct medicine will be open and all others will be kept closed.
 4. An LCD Screen displays current time and message to take medicine when it is time to take.
 5. Timing and compartment inputs of particular medicines are taken through GPIOs of arduino. One input pin “confirm” is used to take these inputs. When time and compartment are set and confirm input is on, the system takes time input of that particular compartment.
 6. Areal time clock embedded in Arduino is used to keep track of the current time.
 7. Arduino is responsible for coordinating all components and executing the control logic.
