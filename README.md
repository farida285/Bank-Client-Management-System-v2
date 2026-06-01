# Bank Client Management System v2

A C++ console-based bank management system rebuilt from scratch using Object-Oriented Programming principles.

This is an upgraded version of [Bank-Client-Management-System](https://github.com/farida285/Bank-Client-Management-System) — rewritten with OOP and extended with new features.

---

## What's New in v2

| Feature | v1 | v2 |
|---|---|---|
| Code Structure | Procedural (single file) | OOP (multi-class architecture) |
| Password Storage | Plain text | Encrypted |
| Currency Exchange | ❌ | ✅ |
| Transfer Between Accounts | ❌ | ✅ with transaction log |
| Login Register | ❌ | ✅ |
| Input Validation | Basic | Advanced (email, name format) |
| Inheritance | ❌ | ✅ `clsPerson` as base class |

---

## Features

### Client Management
- Add, delete, update, and find clients
- View full clients list with account balances
- View total balances across all accounts

### Transactions
- Deposit and withdraw
- Transfer between accounts with automatic rollback on failure
- Full transfer log saved to file

### User Management
- Add, delete, and update users
- Bitwise permission system (per-feature access control)
- Admin account always protected from deletion

### Currency Exchange
- View all currencies list
- Find currency by code or country
- Update exchange rates
- Convert amount between any two currencies (via USD as base)
- Currency calculator

### Login Register
- Every login is recorded with date, time, username, and permission level

---

## Project Structure

**Core Classes**
- `ClsPerson.h` — Base class: first name, last name, email, phone
- `clsBankClient.h` — Inherits clsPerson — client data, file I/O, transactions
- `clsBankUser.h` — Inherits clsPerson — user data, permissions, login register
- `clsCurrencyExchange.h` — Currency data, rate updates, conversion logic

**Input & Validation**
- `clsBankInputs.h` — Shared input methods: name, email, phone validation
- `clsClientInput.h` — Client-specific input (account number, amount, pin)
- `clsUserInput.h` — User-specific input
- `clsInputValidate.h` — General validation utilities

**Screens**
- `clsScreen.h` — Base screen class: header, access denied screen
- `clsMainScreen.h` — Main menu + permission-based routing
- `clsLoginScreen.h` — Login screen
- `clsManageUsersScreen.h` — Users management sub-menu
- `clsTransactionScreen.h` — Transaction sub-menu
- `clsCurrencyExchangeScreen.h` — Currency exchange sub-menu
- And all individual feature screens (Add, Delete, Update, Find, List...)

**Libraries**
- `StringLibrary.h` — String utilities: split, encrypt, trim, etc.
- `DateLibrary.h` — Date utilities
- `PeriodLibrary.h` — Period/duration utilities
- `UtilityLibrary.h` — General utilities

**Other**
- `Global.h` — Global currentUser object
- `Currencies.txt` — Static exchange rates (see note below)
- `BankProjectMain.cpp` — Entry point

> **Note:** `Currencies.txt` contains static exchange rates for demonstration purposes. Rates are not updated automatically.

---

## Permissions System

Each user has a permission value stored as a bitmask:

| Permission | Value |
|---|---|
| Show Clients List | 1 |
| Add Clients | 2 |
| Delete Client | 4 |
| Update Client | 8 |
| Find Client | 16 |
| Transactions | 32 |
| Manage Users | 64 |
| Login Register List | 128 |
| All Permissions (Admin) | -1 |

---

## How to Run

1. Open the project in **Visual Studio**
2. Build and run `BankProject.cpp`
3. Login with default admin credentials:
   - Username: `Admin`
   - Password: `1111`

> The system creates the Admin account automatically if it doesn't exist.

---

## Technologies

- **Language:** C++17
- **Paradigm:** Object-Oriented Programming
- **Storage:** File-based (.txt files)
- **IDE:** Visual Studio
