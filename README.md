# OOP Command Line Interpreter
A C++ object-oriented command-line interpreter (CLI) implementing basic Unix-like commands with support for:

- Pipes (`|`) between commands
- Input/output redirection (`<` and `>`)
- Command options and arguments
- Custom commands: `echo`, `date`, `time`, `touch`, `truncate`, `rm`, `wc`, `tr`, `head`, `prompt`
- Stream-based communication between commands

This project demonstrates OOP principles such as:

- **Encapsulation** – separating `Command`, `Parser`, `InputStream`, and `OutputStream`
- **Polymorphism** – commands share a common interface for execution
- **Single Responsibility Principle (SRP)** – parsing, validation, execution, and error handling are decoupled
- **Factory Pattern** – dynamic creation of commands and streams

### Features

- Execute single commands or pipelines
- Inline arguments or file-based input
- Centralized error handling
- Flexible design for adding new commands

