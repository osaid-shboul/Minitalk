#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
RESET='\033[0m'

if [ -z "$1" ]; then
    echo -e "${RED}Error: Server PID is required.${RESET}"
    echo "Usage: ./tester.sh [SERVER_PID]"
    exit 1
fi

PID=$1

echo -e "${GREEN}========================================${RESET}"
echo -e "${GREEN}      MANDATORY PART TESTER 42         ${RESET}"
echo -e "${GREEN}========================================${RESET}"

run_test() {
    TEST_NAME=$1
    MESSAGE=$2
    
    echo -e "${YELLOW}[TEST] $TEST_NAME...${RESET}"
    ./client $PID "$MESSAGE"
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✔ Client sent successfully.${RESET}"
    else
        echo -e "${RED}✘ Client failed (Error returned)!${RESET}"
        exit 1
    fi
    sleep 1 
}

run_test "Basic Short String" "Hello World"

run_test "Numbers" "1234567890"

run_test "Special Characters" "!@#$%^&*()_+-=[]{}|;':,./<>?"

run_test "Empty String" ""

run_test "Unicode (Arabic)" "Peace be upon you"

run_test "Emojis" "😀🚀💻"

LONG_TEXT=$(python3 -c "print('A' * 2000)")
run_test "Stress Test (2000 chars)" "$LONG_TEXT"

echo -e "\n${GREEN}========================================${RESET}"
echo -e "${GREEN}   DONE! Please check your SERVER output.  ${RESET}"
echo -e "${GREEN}========================================${RESET}"