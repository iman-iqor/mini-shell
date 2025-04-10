🐚 Minishell

A tiny yet powerful shell project created as part of the 42 Network curriculum. This shell mimics the behavior of bash and offers you a deeper understanding of processes, pipes, redirections, signals, and memory management in Unix-like systems.
***********************************************************************************************************************************************************************************************************************************
👥 Team Members

👩‍💻 Imane Iqor 

👨‍💻 Mohamed Benjbara

***********************************************************************************************************************************************************************************************************************************
📁 Project Structure (Clear and Beginner Friendly)==>

minishell/
│
├── include/
│   └── minishell.h          # Central header file for all includes and declarations
│
├── src/
│   ├── main.c               # Entry point of the program
│   ├── parser/              # Tokenization, parsing logic, quote handling
│   ├── executor/            # Execution logic: redirection, pipes, external commands
│   ├── builtins/            # Builtin command implementations: echo, cd, etc.
│   ├── env/                 # Environment variable handling
│   ├── signals/             # Ctrl+C, Ctrl+D, Ctrl+\ behavior management
│   └── utils/               # Helper functions (error messages, memory utils...)
│
├── libft/                  # Your custom libft library
│
├── Makefile                # Compilation rules
└── README.md               # Project documentation

***************************************************************************************************************************************************************************************************************************************

🚀 Features

*Interactive prompt with command history

*Input parsing with proper quote and escape handling

*Support for pipes (|) and redirections (>, >>, <, <<)

*Environment variable expansion ($VAR, $?)

*Built-in commands:

    .echo [-n]

    .cd [dir]

    .pwd

    .export VAR=value

    .unset VAR

    .env

    .exit

*Signal handling like bash (Ctrl+C, Ctrl+D, Ctrl+)

**************************************************************************************************************************************************************************************************************************************

*****if you want to test and explore the project you can clone it and follow these steps*****

🔧 How to Compile
    make

This compiles the shell and its dependencies (including libft).


🔧 To clean the object files:
    make clean


🔧 To remove everything including the executable:
    make fclean


🔧  To recompile everything:
    make re


▶️   How to Run
    ./minishell
    

You'll see your custom prompt appear. From here, you can start typing commands like ls, pwd, or built-ins like export VAR=value.

**************************************************************************************************************************************************************************************************************************************

📚 What We Learned

    This project taught us:

        .How to create and manage processes with fork, execve, wait.....

        .Managing file descriptors and redirections

        .Building a command-line interpreter from scratch

        .Writing a parser and dealing with quotes and special characters

        .Handling Unix signals and terminal behavior

        .Memory management and leak prevention

*************************************************************************************************************************************************************************************************************************************

📌 Notes

    -Only one global variable is used (for signal management).

    -We followed strict memory discipline — no leaks allowed!

    -The shell only behaves like bash in interactive mode.

*************************************************************************************************************************************************************************************************************************************

💬 Contact

    👩‍💻  Imane Iqor          🔗https://www.linkedin.com/in/imane-iqor-b5075b323/        📩iqorimane85@gmail.com

    👨‍💻  Mohamed Benjbara    🔗https://www.linkedin.com/in/mohamed-benjbara-204886248/   📩mohamed.benjbara@um6p.ma

*************************************************************************************************************************************************************************************************************************************

Feel free to reach out for any questions or suggestions!

Thanks for reading — and welcome to our shell! 🐚