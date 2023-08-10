# Minishell

## Description

Minishell is a project that aims to create a simple shell.

## Usage

```bash
make
./minishell
```

## Norm

- Optimised variables types. ex: int8_t instead of int.
- Variables & functions names : lowercase and snake_case.
- Variables names: logical and explicit.
- Use libmms for memory management.
- Logical names at all times.

## How to push

- Never push directly on master.
- Create branch for your edits.
- After your edits, fetch and merge to master.
- Push.
```
alias sgit=git fetch --all && git pull --all && git branch

sgit
git branch <branch_name>
git switch <branch_name>
git add .
git commit -m "<message>"
git switch master
sgit
git merge <branch_name>
git push
```
