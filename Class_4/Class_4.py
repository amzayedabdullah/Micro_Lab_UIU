import RPi.GPIO as GPIO
import time

# Pin setup
LED_PIN = 18      # GPIO pin for LED
BUTTON_PIN = 23   # GPIO pin for Button

# Use BCM pin numbering
GPIO.setmode(GPIO.BCM)

# Set LED pin as output
GPIO.setup(LED_PIN, GPIO.OUT)

# Set button pin as input with internal pull-down resistor
GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

print("Press the button to turn ON the LED...")

try:
    while True:
        if GPIO.input(BUTTON_PIN) == GPIO.HIGH:  # Button pressed
            GPIO.output(LED_PIN, GPIO.HIGH)      # LED ON
        else:
            GPIO.output(LED_PIN, GPIO.LOW)       # LED OFF
        time.sleep(0.1)  # Small delay to avoid bouncing issues

except KeyboardInterrupt:
    print("\nProgram stopped")

finally:
    GPIO.cleanup()  # Reset GPIO pins
