#  Hospital Management System
A comprehensive Hospital Management System implemented in C++ as a console application. This project demonstrates various C++ programming concepts including Object-Oriented Programming, dynamic memory management, data structures, and file organization.

# Run key :
.\hospital_system.exe

##  Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Technical Requirements](#technical-requirements)
- [Project Structure](#project-structure)
- [Installation & Setup](#installation--setup)
- [How to Run](#how-to-run)
- [Modules](#modules)
- [C++ Concepts Demonstrated](#c-concepts-demonstrated)
- [Usage Guide](#usage-guide)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

##  Overview

This Hospital Management System is a complete console-based application developed in standard C++. It serves as a practical implementation of various C++ programming concepts taught in university-level courses. The system manages patients, doctors, appointments, rooms, and billing operations through an intuitive menu-driven interface.

**Project Type:** University Semester Project  
**Level:** Intermediate  
**Language:** Standard C++  
**IDE:** Visual Studio 2022  
**External Libraries:** None (Pure C++)

##  Features

### Core Modules
- ** Dashboard**: Real-time statistics of hospital operations
- ** Patient Management**: Complete CRUD operations for patients
- ** Doctor Management**: Manage doctor profiles and availability
- ** Room Management**: 2D array-based room allocation system
- ** Appointment Management**: Book and cancel appointments
- ** Billing System**: Generate and manage patient bills

### Technical Features
-  Auto-growing dynamic arrays
-  Double pointer implementation (3D arrays)
-  Jagged arrays for variable-length data
-  Input validation
-  Formatted tabular output
-  Memory leak prevention
-  Object-Oriented Design

## 🛠 Technical Requirements

### Software Requirements
- **Operating System**: Windows 10/11
- **IDE**: Visual Studio 2022 (Community Edition or higher)
- **Compiler**: MSVC C++ Compiler (C++17 standard)
- **Framework**: .NET Framework 4.6.1 or higher (for Visual Studio)

### Hardware Requirements
- **Processor**: Intel Core i3 or equivalent
- **RAM**: 4 GB minimum (8 GB recommended)
- **Storage**: 100 MB free space

## 📁 Project Structure

HospitalManagementSystem/
│
├── HospitalManagementSystem.sln # Visual Studio Solution File
│
├── HospitalManagementSystem/ # Main Project Directory
│ │
│ ├── Header Files (.h)
│ │ ├── Utils.h # Utility functions
│ │ ├── Patient.h # Patient class & structure
│ │ ├── Doctor.h # Doctor class & structure
│ │ ├── Appointment.h # Appointment class & structure
│ │ ├── Billing.h # Billing class & structure
│ │ └── Hospital.h # Main Hospital class
│ │
│ ├── Source Files (.cpp)
│ │ ├── main.cpp # Program entry point
│ │ ├── Utils.cpp # Utility function implementations
│ │ ├── Patient.cpp # Patient management implementations
│ │ ├── Doctor.cpp # Doctor management implementations
│ │ ├── Appointment.cpp # Appointment management implementations
│ │ ├── Billing.cpp # Billing management implementations
│ │ └── Hospital.cpp # Hospital class implementations
│ │
│ └── README.md # Project documentation
│
└── .gitignore # Git ignore file


##  Installation & Setup

### Method 1: Visual Studio 2022 (Recommended)

1. **Clone or Download the Project**
   ```bash
   git clone https://github.com/yourusername/HospitalManagementSystem.git"# HMS" 
