# RideSharing

# Assignment 5 — Class-Based Ride Sharing System (C++ & Smalltalk)

This repository contains two implementations of a simple ride-sharing model in **C++** and **Smalltalk**, demonstrating **encapsulation**, **inheritance**, and **polymorphism**.

## Contents
- `cpp_main.cpp` — C++ implementation with classes `Ride`, `StandardRide`, `PremiumRide`, `Driver`, and `Rider`.
- `RideSharing.st` — Smalltalk implementation (tested syntax for GNU Smalltalk/Pharo style).
- `Assignment5_RideSharing_Report.docx` — Brief APA-style report with screenshots of code and sample output.
- `images/` — Screenshot-like PNG exports of code/output used by the report.

## Build & Run

### C++
```bash
g++ -std=c++17 -O2 -o rides cpp_main.cpp
./rides
```

### Smalltalk (GNU Smalltalk)
```bash
gst RideSharing.st
```

## Notes
- The demo creates a heterogeneous list of rides and calls `fare()` and `rideDetails()` polymorphically.
- `Driver` and `Rider` encapsulate their ride collections and expose modification via methods only.
- Update the GitHub URL in the report after pushing these files to your repository.

