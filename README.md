Power Consumption Application in C++ (OOP)

This C++ application calculates average power costs for a household based on various factors such as the number of persons, square meters, types of consumers, and power suppliers. It's designed using object-oriented programming principles for better organization and scalability.
Developer Information:


Overview:

This application allows users to simulate and analyze the power consumption and associated costs for different households. It offers functionalities to add various types of consumers (Immobile, Mobile, Solar) to a household, input household details, move devices within a household, and write/read data to/from a file.
Getting Started:
![Archeticture](https://github.com/Omranjr/Power-Consumption-App/assets/156198295/af7d4029-01a9-4358-bd68-15fcd69a6ddf)



Usage:
![Screenshot 2024-04-16 041512](https://github.com/Omranjr/Power-Consumption-App/assets/156198295/acd56b75-0564-4173-afaa-30492ed38de0)


    h: Initialize a new house.
    i: Add an immobile consumer to a household.
    m: Add a mobile consumer to a household.
    s: Add a solar producer to a household.
    u: Move up a device within a household.
    n: Input new household details.
    c: Copy all devices within a household.
    a: Print all households and their power consumption.
    r: Read household data from a file.
    w: Write household data into a file.
    p: Print a specific household's details.

File Input/Output:

    File Format: Data is stored in a CSV format.
    Read from File (r): Reads household data from a CSV file.
    Write to File (w): Writes household data into a CSV file.

Notes:

    Ensure proper input to avoid unexpected behavior.
    Always initialize a house before adding consumers or performing any operations
