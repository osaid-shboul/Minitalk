_*This Project has been created as part of the 42 curriculum by oalshbou*_

# Minitalk

**Minitalk** is a data exchange program using UNIX signals. The goal of this project is to create a communication channel between a client and a server using only two signals: SIGUSR1 and SIGUSR2.

## Description

The project consists of two separate executables:

- **Server:** Launches first, prints its PID (Process ID), and waits for incoming signals. It reconstructs the string sent by the client and prints it to the standard output.
- **Client:** Takes the server's PID and a string as arguments, converts the string into binary, and sends it to the server signal by signal.

## Technical Implementation

The communication relies on **Bitwise Operations** and **UNIX Signals**:

1.  **Protocol:** `SIGUSR1` represents bit `0` and `SIGUSR2` represents bit `1`.
2.  **Client:** Iterates through each byte of the string. It uses bit-shifting (>>) and bitwise AND (&) to isolate and send the 8 bits of each character.
3.  **Server:** Uses `sigaction` to catch signals. It reconstructs the character using bit-shifting (<<) and bitwise OR (|). It acknowledges the end of a message upon receiving a null terminator.

## Installation and Usage

### 1. Compilation

Use the provided Makefile to compile both the server and the client:

```bash
make
```
### 2. Running the Server 

Start the server first. It will display its PID.
```bash
./server
```
Output example:

```bash
PID: 421337
```

### 3. Running the client

Open a new terminal window and run the client with the server's PID and your message:

```bash
./client [PID] [MESSAGE]
```

Example:

```bash 
./client 421337 "Hello 42 Network"
```

### 4.Cleaning up

To remove object files and executables:

```bash
make fclean
```