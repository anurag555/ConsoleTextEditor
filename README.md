#  ConsoleTextEditor 
A simple command-line text editor written in C that supports file editing operations and undo/redo functionality.

---

## 🚀 Features

* Load and save text files
* Insert, delete, and edit lines
* Undo and redo operations using stacks
* Command-driven interface
* Modular code structure

---

## 🛠️ Tech Stack

* C (GCC)
* Standard Libraries (stdio.h, string.h)

---

## 📁 Project Structure

```
src/
  main.c
  editor.c
  editor.h
  file.c
  file.h
Makefile
```

---

## ⚙️ Build

```
gcc src/main.c src/editor.c src/file.c -o editor
```

---

## ▶️ Run

On Windows:

```
editor.exe filename.txt
```

On Linux/macOS:

```
./editor filename.txt
```

---

## 💡 Commands

* `insert` → insert a new line
* `delete` → delete a line
* `edit` → modify a line
* `undo` → revert last change
* `redo` → reapply last undone change
* `save` → save file
* `exit` → exit editor

---

## 🧪 Example

```
insert
1
Hello World

edit
1
Updated Line

undo
save
```

---

## 🧠 Implementation Details

* Text is stored as an array of lines
* Undo and redo are implemented using two stacks
* Each edit operation saves the previous state

---

## 📌 Notes

* Designed for terminal use
* No external dependencies
* Suitable for learning basic editor and data structure concepts

---

