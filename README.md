# Bank Client Management System (v2)

A console-based Bank Management System written in **C++** using **Object-Oriented Programming**. This is a complete OOP rebuild of [Bank-Client-Management-System (v1)](https://github.com/farida285/Bank-Client-Management-System), introducing inheritance, a permission-based user system, encrypted credential storage, transaction rollback, and a currency exchange module.

> Built with Visual Studio (Windows). Uses MSVC-specific extensions (`__declspec(property)`) and Windows console calls (`system("cls")`), so it is intended to run on Windows / Visual Studio rather than cross-platform compilers.

---

## Table of Contents

- [Overview](#overview)
- [What's New in v2](#whats-new-in-v2)
- [Features](#features)
- [Project Architecture](#project-architecture)
- [Class Reference](#class-reference)
- [Data Storage](#data-storage)
- [Permissions System](#permissions-system)
- [Getting Started](#getting-started)
- [Default Admin Account](#default-admin-account)
- [Project Structure](#project-structure)
- [Possible Future Improvements](#possible-future-improvements)
- [Author](#author)

---

## Overview

This system simulates a real banking environment from the console, supporting two kinds of accounts:

- **Bank Clients** — people who hold bank accounts and perform deposits, withdrawals, and transfers.
- **Bank Users (employees)** — staff members who log in to operate the system, each with a specific set of permissions (Admin or restricted).

All data is persisted in flat text files, with no external database required, making the project fully portable and easy to inspect/debug.

## What's New in v2

The v1 project ([single-file procedural implementation](https://github.com/farida285/Bank-Client-Management-System)) was rebuilt from scratch into a proper multi-class OOP design:

| Aspect | v1 | v2 |
|---|---|---|
| Code structure | Procedural, single file (`BankProject.cpp`) | OOP, multi-class architecture (40+ files) |
| Code reuse | Client and User logic duplicated | Shared base class `clsPerson`, inherited by `clsBankClient` and `clsBankUser` |
| Access control | Bitwise permissions, but no inheritance | Same bitwise model, now combined with full OOP and added `loginRegisterlist` permission |
| Credential storage | Plain text | Passwords and PIN codes encrypted before being written to file |
| Transfer between accounts | Not present | `Transfer()` with automatic rollback if either leg of the transfer fails, plus a full transfer log |
| Multi-currency | Not present | Full currency exchange module (rates, lookup, calculator) |
| Login auditing | Not present | Login Register: every login attempt logged with timestamp and permission level |
| Screens | Monolithic | Each screen isolated in its own class, all inheriting from a shared `clsScreen` base |

## Features

**Client Management**
- Add, update, delete, and search for clients by account number
- View a complete list of all registered clients
- Soft-delete mechanism (records are flagged, not physically removed mid-file, then rewritten cleanly)

**Transactions**
- Deposit and withdraw funds with balance validation
- Transfer funds between two different accounts, with automatic rollback if the deposit step fails after a successful withdrawal
- View a full transfer log (date/time, sender, receiver, amounts, resulting balances, and the user who performed it)
- View total balances across all clients

**User & Access Management**
- Add, update, delete, and search for system users (bank employees)
- Each user is assigned either full admin access or a custom combination of permissions
- Login attempts are limited to 3 trials before lockout for that session
- Every login is recorded with a timestamp in a login register, viewable by authorized users

**Currency Exchange**
- Browse a list of 200+ world currencies with their exchange rate against the US Dollar
- Find a currency by country name or currency code
- Update a currency's exchange rate
- Currency calculator to convert an amount between any two currencies

**Input Validation**
- Strict validation for names (letters only, single optional space or hyphen for compound names, no leading/trailing separators)
- Email format validation (single `@`, valid local part, domain, and extension, no spaces)
- Phone number validation (digits only, fixed length)
- Numeric input validation with custom ranges and re-prompting on invalid input

## Project Architecture

The project follows a layered, object-oriented structure:

```
clsPerson (base class)
   ├── clsBankClient   → account holder: balance, account number, PIN, transactions
   └── clsBankUser     → system employee: username, password, permission bitmask

clsScreen (base class for all UI screens, provides shared header/denied-access rendering)
   ├── clsLoginScreen
   ├── clsMainScreen
   │     ├── clsClientsListScreen / clsAddNewClientScreen / clsUpdateClientScreen
   │     │   / clsDeleteClientScreen / clsFindClientScreen
   │     ├── clsTransactionScreen
   │     │     ├── clsDepositScreen / clsWithdrawScreen / clsTransferScreen
   │     │     └── clsTotalBalancesListScreen / clsTransferLogListScreen
   │     ├── clsManageUsersScreen
   │     │     ├── clsUserListScreen / clsAddNewUserScreen / clsUpdateUserScreen
   │     │     └── clsDeleteUserScreen / clsFindUserScreen
   │     ├── clsLoginRegisterScreen
   │     └── clsCurrencyExchangeScreen
   │           ├── clsCurrenciesListScreen / clsFindCurrencyScreen
   │           └── clsUpdateCurrencyRateScreen / clsCurrencyCalculatorScreen

clsCurrencyExchange  → independent of clsPerson, models currency records and conversion logic

Supporting libraries: clsInputValidate, clsBankInputs (clsClientInput / clsUserInput),
StringLibrary, DateLibrary, PeriodLibrary, UtilityLibrary
```

Each screen class is responsible only for console I/O and delegates all business logic and persistence to the relevant data class (`clsBankClient`, `clsBankUser`, `clsCurrencyExchange`). This keeps the UI layer thin and the data/logic layer testable and reusable.

## Class Reference

### `clsPerson`
Base class holding shared personal data: first name, last name, email, and phone number, plus a `FullName()` helper. Both `clsBankClient` and `clsBankUser` inherit from it, avoiding duplicated fields and getters/setters.

### `clsBankClient : public clsPerson`
Represents a bank account holder. Adds account number, PIN code, and balance on top of the inherited personal data.

Key responsibilities:
- `Save()` — handles both insert and update depending on the object's internal mode (`AddNewMode` / `UpdateMode`), and prevents saving over an existing account number
- `Deposit(amount)` / `Withdraw(amount)` — validate the amount and roll back the in-memory balance change if the file save fails
- `Transfer(amount, to)` — withdraws from the source account, deposits into the target account, and if the deposit fails, reverses the withdrawal so the source account is never left short. On success, the transfer is recorded via `TransferLog()`
- `Find()` — overloaded to search by account number alone, or account number + PIN
- Static helpers (`GetClientsList`, `GetTotalBalances`, `GetTransferList`) for reporting screens

### `clsBankUser : public clsPerson`
Represents a bank employee/system user. Adds username, encrypted password, and a permission bitmask.

Key responsibilities:
- `CheckAccessPermission(enPermission)` — returns true if the user has full access (`-1`) or if the specific permission bit is set
- `EnsureAdminExistAndSetup()` — guarantees a default Admin account exists the first time the system runs
- `RegisterLogin()` / `GetLoginRegistersList()` — records and retrieves a full audit trail of login attempts
- Deletion is blocked for the `Admin` account to prevent accidental lockout

### `clsCurrencyExchange`
Standalone class (not inherited from `clsPerson`) representing a single currency: country, ISO code, name, and exchange rate against USD.

Key responsibilities:
- `FindByCountry()` / `FindByCode()` — case-insensitive lookup
- `ConvertAmountToUSD()` / `ConvertAmountToOtherCurrency()` — performs conversion through USD as a common base
- `UpdateRate()` — only allowed when the object was loaded from file (`UpdateMode`), not on empty/not-found results

### `clsScreen`
Shared base for every screen class. Centralizes the repeated header rendering (title, current logged-in user, current date) and the "Access Denied" message shown when a user without sufficient permission tries to reach a restricted screen.

### Supporting Libraries
- **`clsInputValidate`** — generic, reusable input readers: ranged numbers, yes/no prompts, bounded-length strings, valid dates
- **`clsBankInputs`** (base for `clsClientInput` / `clsUserInput`) — domain-specific input readers built on top of `clsInputValidate`, including the name, email, and phone number validators
- **`StringLibrary`** — string utilities (split, trim, case conversion) plus the `EncryptString` / `DecryptString` functions used for credentials
- **`DateLibrary` / `PeriodLibrary`** — date handling and date-range utilities, used for timestamps in transfer and login logs
- **`UtilityLibrary`** — miscellaneous shared helper functions

## Data Storage

The system uses plain text files as a lightweight persistence layer, with no external database dependency:

| File | Stores |
|---|---|
| `Clients.txt` | All bank client records |
| `Users.txt` | All system user (employee) records |
| `Transfers.txt` | Full transfer history between client accounts |
| `LoginRegister.txt` | Timestamped log of every login attempt |
| `Currencies.txt` | World currency list with exchange rates against USD |

Each record is stored as a single line with fields separated by a custom delimiter (`#//#`), and each entity class (`clsBankClient`, `clsBankUser`, `clsCurrencyExchange`) handles its own line-to-object and object-to-line conversion internally.

Sensitive fields — client PIN codes and user passwords — are encrypted with a simple shift-cipher (`EncryptString` / `DecryptString`) before being written to disk, and decrypted transparently when records are loaded back.

> **Note:** In v1, `BankClients.txt` was also shared with a separate [ATM System](https://github.com/farida285/ATM-System) project. In v2, the client file format has changed (additional fields, different encryption) as part of the OOP rebuild, so `Clients.txt` here is not directly compatible with the v1/ATM file format.

## Permissions System

Access control is implemented with a bitwise permission scheme defined in `clsBankUser::enPermission`:

| Permission | Bit value |
|---|---|
| `all` (Admin) | `-1` |
| `clientsList` | `1` |
| `addClients` | `2` |
| `deleteClient` | `4` |
| `updateClient` | `8` |
| `findClient` | `16` |
| `transaction` | `32` |
| `manageUsers` | `64` |
| `loginRegisterlist` | `128` |

When creating or updating a user, the admin is asked to either grant full access or select any combination of the permissions above; the selected values are summed into a single `short` and stored against the user. At runtime, `CheckAccessPermission()` uses a bitwise `AND` to check whether a specific permission bit is set, allowing a single integer field to represent any combination of access rights without needing a separate boolean for each one.

## Getting Started

### Requirements
- Windows OS
- Visual Studio (2019 or later recommended)
- C++17 (the project relies on MSVC-specific `__declspec(property)` syntax for property-style getters/setters)

### Running the project
1. Clone the repository.
2. Open the `.sln` / project in Visual Studio.
3. Build and run `BankProjectMain.cpp`.
4. On first run, the system automatically creates a default `Admin` account if `Users.txt` does not already contain one.
5. Log in and use the Main Menu to navigate between Clients, Transactions, Manage Users, Login Register, and Currency Exchange.

## Default Admin Account

On first launch, if no `Admin` user exists in `Users.txt`, the system automatically inserts one with full access (`enPermission::all`) so the system is never left without an administrator:

```
UserName: Admin
Password: 1111
```

It is recommended to change this password (via the Update User screen) after the first login in any real deployment.

## Project Structure

This is the actual Solution Explorer layout in Visual Studio (filters, not physical folders):

```
BankProject
├── Header Files
│   ├── Core
│   │   ├── clsBankClient.h          # Client entity + persistence + transactions
│   │   ├── clsBankUser.h            # User entity + persistence + permissions
│   │   ├── clsCurrencyExchange.h    # Currency entity + conversion logic
│   │   └── ClsPerson.h              # Base class: shared personal data
│   │
│   ├── Lib
│   │   ├── clsBankInputs.h          # Domain-specific input base (name/email/phone)
│   │   ├── clsClientInput.h
│   │   ├── clsInputValidate.h       # Generic input validation
│   │   ├── clsUserInput.h
│   │   ├── DateLibrary.h
│   │   ├── PeriodLibrary.h
│   │   ├── StringLibrary.h          # String utilities + encryption
│   │   └── UtilityLibrary.h
│   │
│   ├── Screens
│   │   ├── ClientScreens
│   │   │   ├── TransctionScreens
│   │   │   │   ├── TransctionCoreScreen
│   │   │   │   │   └── clsTransactionScreen.h
│   │   │   │   ├── clsDepositScreen.h
│   │   │   │   ├── clsTotalBalancesListScreen.h
│   │   │   │   ├── clsTransferLogListScreen.h
│   │   │   │   ├── clsTransferScreen.h
│   │   │   │   └── clsWithdrawScreen.h
│   │   │   ├── clsAddNewClientScreen.h
│   │   │   ├── clsClientsListScreen.h
│   │   │   ├── clsDeleteClientScreen.h
│   │   │   ├── clsFindClientScreen.h
│   │   │   └── clsUpdateClientScreen.h
│   │   │
│   │   ├── CoreScreens
│   │   │   ├── clsLoginScreen.h
│   │   │   └── clsMainScreen.h
│   │   │
│   │   ├── CurrenciesScreens
│   │   │   ├── clsCurrenciesListScreen.h
│   │   │   ├── clsCurrencyCalculatorScreen.h
│   │   │   ├── clsCurrencyExchangeScreen.h
│   │   │   ├── clsFindCurrencyScreen.h
│   │   │   └── clsUpdateCurrencyRateScreen.h
│   │   │
│   │   ├── UserScreens
│   │   │   ├── UsersCoreScreen
│   │   │   │   └── clsManageUsersScreen.h
│   │   │   ├── clsAddNewUserScreen.h
│   │   │   ├── clsDeleteUserScreen.h
│   │   │   ├── clsFindUserScreen.h
│   │   │   ├── clsLoginRegistersScreen.h
│   │   │   ├── clsUpdateUserScreen.h
│   │   │   └── clsUserListScreen.h
│   │   │
│   │   └── clsScreen.h              # Base screen (header/denied-access rendering)
│   │
│   └── Global.h                     # Holds the currently logged-in user
│
├── Resource Files
│
└── Source Files
    └── BankProjectMain.cpp          # Entry point
```

> **Note:** These filters organize the project inside Visual Studio's Solution Explorer only — all header files physically live in the same project directory alongside the data files below (`Clients.txt`, `Users.txt`, `Transfers.txt`, `LoginRegister.txt`, `Currencies.txt`).

## Possible Future Improvements

- Replace flat-file storage with a real database (SQLite/SQL Server) for better scalability and concurrent access
- Strengthen the encryption scheme used for passwords/PINs beyond a simple character shift
- Make the codebase cross-platform by removing MSVC-specific extensions (`__declspec(property)`) and Windows-only calls (`system("cls")`)
- Add unit tests around the data classes (`clsBankClient`, `clsBankUser`, `clsCurrencyExchange`)
- Support multi-currency account balances instead of a single base currency per client

## Author

**Farida** — [github.com/farida285](https://github.com/farida285)

This project was built as a practical exercise in applying Object-Oriented Programming principles (inheritance, encapsulation, static factory methods) to a realistic, file-based business application, as part of an ongoing C++ learning path.
