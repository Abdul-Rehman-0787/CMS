# Complaint Management System

## Project Description
This C++ program implements a comprehensive customer service management system with user management and complaint handling capabilities. The system uses efficient data structures including AVL Trees and Doubly Linked Lists to manage user data and prioritize customer complaints based on user types.

## Key Features

### User Management System
- User registration with details (ID, name, email, country, type)
- Multiple search functionalities:
  - Search by User ID (primary key)
  - Search by Name (with optional index)
  - Search by Email (with optional index)
- User deletion capability
- Print all users functionality

### Index Management
- Dynamic index creation/deletion for:
  - User names
  - Email addresses
  - Country
  - User type
- View active indices
- Group viewing by country or user type

### Complaint Management
- Priority-based complaint queue:
  - Platinum users (highest priority)
  - Gold users
  - Silver users
  - Regular users
  - New users (lowest priority)
- Complaint registration
- Complaint servicing (processes highest priority first)
- Priority escalation
- View complaints by user or country

## Technical Implementation

### Data Structures
1. **Doubly Linked List** - Main storage for user records
2. **AVL Trees** - For efficient searching/indexing:
   - Primary index on User ID
   - Secondary indices (optional) on name, email
3. **Group AVL Trees** - For grouping users by:
   - Country
   - User type
4. **Priority Queue** - For complaint handling

### User Types
The system recognizes five user types with different priority levels:
1. Platinum (Highest priority)
2. Gold
3. Silver
4. Regular
5. New (Lowest priority)




                                                  For any questions or issues with the program, please contact:

Abdul-Rehman
Student ID: 23L-0787
University Email: l230787@lhr.nu.edu.pk
Personal Email: abdulrehmannaseer572@gmail.com