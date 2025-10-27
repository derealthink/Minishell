#!/bin/bash

# Trap SIGINT (Ctrl+C)
trap 'echo -e "\nCaught Ctrl+C (SIGINT)! Exiting gracefully." ; exit 1' INT

echo "PID: $$"
echo "Starting an infinite loop. Press Ctrl+C to test the trap."

# Loop indefinitely to keep the script running
while true; do
    sleep 1
    echo -n "."
done

# The script should never reach this point
