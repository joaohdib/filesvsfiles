# Book Management System (C with File Handling)

This project is a **book management system** implemented in C, which allows performing operations such as creating, listing, reading, updating, and deleting books using different file handling techniques (**text files, binary files, sorted files, and heap structures**). 

The project also measures execution times for each operation, allowing comparisons between different storage methods.

---

## 📌 Features
- ✅ Store books using **text files**, **binary files**, **sorted files**, and **heap files**.
- ✅ Perform **CRUD** (Create, Read, Update, Delete) operations.
- ✅ Compare execution times of different storage methods.
- ✅ Supports structured data, including **title, author, genre, price, and page count**.

---

## 📂 Project Structure
```/project-root │── heap.h │── normal.h │── sorted.h │── task.h │── main.c │── manager.dat │── livros.txt │── livrosBin.dat │── livrosSortedTxt.txt │── livrosSortedBin.dat │── livrosHeapTxt.txt │── livrosHeapBin.dat```

## ⚙️ **Compilation & Execution**
### **1️⃣ Compile the Program**
To compile the project, use `gcc`:
>>>
gcc -o book_manager main.c heap.c normal.c sorted.c task.c -Wall
>>>

### **2️⃣ Run the Program**
>>>
./book_manager
>>>

---

## 📖 **How It Works**
### **1️⃣ Creating Books**
Books are created with the following attributes:
- **ID**
- **Title**
- **Author**
- **Genre**
- **Number of pages**
- **Price**
- **Active status (1 = active, 0 = deleted)**

Example function for book creation:
```
void create_fileTxt(char *filename) {
    FILE *arq;
    arq = fopen(filename, "w");
    fclose(arq);
}
```

---

### **2️⃣ Listing Books**
The program supports listing books stored in different formats:

Example listing function for text files:
```
void listTxt(char *filename, int size) {
    FILE *arq = fopen(filename, "r");
    if (!arq) {
        printf("File not found!\\n");
        return;
    }
    Book book;
    while (fscanf(arq, "%d %s %s %s %d %f %d", &book.id, book.title, book.author, 
                  book.genre, &book.qtdPag, &book.price, &book.active) != EOF) {
        if (book.active) {
            printf("Book: %s, Author: %s, Pages: %d, Price: %.2f\\n",
                   book.title, book.author, book.qtdPag, book.price);
        }
    }
    fclose(arq);
}
```

---

### **3️⃣ Reading a Specific Book**
To retrieve a book by ID:
```
void readTxt(char *filename, int id, int size) {
    FILE *arq = fopen(filename, "r");
    if (!arq) {
        printf("File not found!\\n");
        return;
    }
    Book book;
    while (fscanf(arq, "%d %s %s %s %d %f %d", &book.id, book.title, book.author, 
                  book.genre, &book.qtdPag, &book.price, &book.active) != EOF) {
        if (book.id == id && book.active) {
            printf("Found Book: %s, Author: %s\\n", book.title, book.author);
            fclose(arq);
            return;
        }
    }
    printf("Book not found!\\n");
    fclose(arq);
}
```

---

### **4️⃣ Updating a Book**
Updating a book modifies its information while keeping its original ID.

Example:
```
void updateTxt(char *filename, Book updatedBook, int size) {
    FILE *arq = fopen(filename, "r+");
    if (!arq) {
        printf("File not found!\\n");
        return;
    }
    Book book;
    while (fscanf(arq, "%d %s %s %s %d %f %d", &book.id, book.title, book.author, 
                  book.genre, &book.qtdPag, &book.price, &book.active) != EOF) {
        if (book.id == updatedBook.id && book.active) {
            fseek(arq, -sizeof(Book), SEEK_CUR);
            fwrite(&updatedBook, sizeof(Book), 1, arq);
            fclose(arq);
            printf("Book updated!\\n");
            return;
        }
    }
    printf("Book not found!\\n");
    fclose(arq);
}
```

---

### **5️⃣ Deleting a Book**
Instead of removing a book from the file, it is marked as inactive (`active = 0`).

Example:
```
void deleteTxt(char *filename, int id, int size) {
    FILE *arq = fopen(filename, "r+");
    if (!arq) {
        printf("File not found!\\n");
        return;
    }
    Book book;
    while (fscanf(arq, "%d %s %s %s %d %f %d", &book.id, book.title, book.author, 
                  book.genre, &book.qtdPag, &book.price, &book.active) != EOF) {
        if (book.id == id) {
            book.active = 0;
            fseek(arq, -sizeof(Book), SEEK_CUR);
            fwrite(&book, sizeof(Book), 1, arq);
            fclose(arq);
            printf("Book deleted!\\n");
            return;
        }
    }
    printf("Book not found!\\n");
    fclose(arq);
}
```

---

## ⏱ **Performance Comparison**
The program compares execution times for different storage methods:
- **Text Files**
- **Binary Files**
- **Sorted Text Files**
- **Sorted Binary Files**
- **Heap Text Files**
- **Heap Binary Files**

Example performance measurement:
```
clock_t start, end;
double executionTime;

start = clock();
listTxt("livros.txt", get_file_sizeTxt("livros.txt"));
end = clock();

executionTime = (double)(end - start) / CLOCKS_PER_SEC;
printf("Execution Time: %f seconds\\n", executionTime);
```

---

## 📌 **Final Thoughts**
This project demonstrates how **different file handling methods** affect performance and how structured data can be efficiently stored and retrieved in C. 

🔥 **Key Takeaways:**
- **Using binary files is generally faster than text files.**
- **Sorted files help in faster retrieval of records.**
- **Heap structures optimize insertion and deletion operations.**

---

## 🛠 **Future Improvements**
- ✅ Implement indexing for faster searches.
- ✅ Add a GUI for better user interaction.
- ✅ Support exporting data to JSON or CSV formats.

If you have suggestions, feel free to contribute! 🚀
