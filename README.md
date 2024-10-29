## 📖 Description

`minishell` is a project from 42 Common Core cursus, in which a simple shell based on Bash Posix must be created, interpret the user's input and execute the command.*

This project was done by two students : [6jeanne6](https://github.com/6jeanne6) and [Lothinnt](https://github.com/Lothinnt)

**Main features asked for this minishell are:**

• History to browse through former prompts
• Executables based on PATH variable or with an absolute or relative path
• Signal management: `SIGINT`, `SIGQUIT`
• Redirections: standard input and output, namely `<` `<<` `>` and `>>`
• Handle environment and expand their variables starting with `$`
• $? to display exit status
• Pipelines
• A few builtins: `echo with -n option`, `cd with only a relative or absolute path`, `pwd`, `export`, `unset`, `env`, `exit`


## ⚙️ Installation

1. Clone the git repository

```
git clone https://github.com/6jeanne6/minishell.git minishell
```

2.Go to minishell directory

```
cd minishell
```

3. Compile

```
make
```

## 🚀 Usage

To launch our shell: 

```
./minishell
```
