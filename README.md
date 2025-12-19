# Alien Selector Simulator based on the Omnitrix from the series "Ben 10"

As the title suggests, this project is based on the mysterious internal behavior of the Omnitrix in the Ben 10 series,  
where its usage follows the behavior described below:

> Example 1: Guided Selection  
>  
> Step 1: Enter the selection criteria, which can be strength, speed, endurance, a combination of these, or the total.  
> If the criteria is not valid, speed or endurance will be used by default (depending on whether one or two criteria are selected).  
> Step 2: View the aliens as they appear until the desired one is reached.
>
> Example 2: Free Selection  
>
> Step 1: Enter the name of the alien you want to select (you have a limited number of attempts that reset when a valid, non-repeated alien is chosen).  
> Step 2: Continue selecting aliens (you cannot select the same alien twice in a row) until desired or until attempts run out.
>            

Additionally, I include functions to register new aliens, delete them, view an alien by name along with its statistics, view the complete alien list, or view the list including attributes.  
The order of the aliens in the “lists” corresponds to the order in which they were added; this vector is never modified so the insertion order is always preserved.

# Corrections

> In this submission, I was unable to change many things. The only modification I made was implementing a Hash for name-based searches that do not modify any alien attributes, which speeds up the program (the time complexity of name-based search went from O(n) when using a vector to O(1) in the best case, although average and worst cases remain O(n)).  
> I should mention that to achieve this, I had to modify the Omnitrix.h, Main, and Menu files mainly. I tried to reproduce the error encountered during the demonstration, but it was impossible to do so.

## SICT0302B: Decision Making

### Selects and uses an appropriate linear data structure for the problem

I use a queue in the guided selection mode since aliens are ordered to be retrieved in descending order without repetition; for storing aliens, I use a simple vector.  
Each alien is an object containing the following integer attributes: intelligence, strength, speed, endurance, total, battles won, times used, and times selected;  
and a name attribute of type string.  

The first five attributes are used to sort aliens according to the desired criteria in guided selection mode; additionally, total, battles won, and times selected are used to determine the order in the splay tree.

---

### Selects an appropriate sorting algorithm for the problem

For this problem, I used two different sorting algorithms: Insertion Sort and Merge Sort.  
Specifically, if there are 20 or fewer aliens, Insertion Sort is used; if there are more (in the original series, the future version of Ben 10 had more than 10,000 aliens), Merge Sort is used.  

The reason is that when the number of elements is small, Insertion Sort can be just as efficient or even more efficient than Merge Sort in some cases. I chose Merge Sort because, among those studied in class, it is the most efficient, as its time complexity does not depend on the initial ordering of the elements (which is beneficial for the worst case, though it slightly affects the best case).  

InsertionSort (line 26) and MergeSort (line 151) are located in the file `ordenamiento.h`. It is also worth mentioning that MergeSort requires additional functions to work, such as `mergeArray` (line 73) and `mergeSplit` (line 125).

---

### Uses an appropriate tree to solve a problem

I used a Splay Tree to quickly access recently used aliens and to organize them based on three criteria (times selected, battles won, and finally total).  
The logic is that if two aliens have the same number of selections, battles won is used; if that attribute is also equal, total is used (an attribute that is the sum of four others, making ties unlikely).

The functions where it is used include `seleccionLibre` in `menu.h` at line 437 (which uses `registrarEleccionSplay` at line 32 of `omnitrix.h`, which in turn uses `find` from the `SplayTree` class and `find` from the `Node` class, located at lines 591 and 112 of `arbol.h`, respectively).  

It is also used in `registrarAlien` at line 187 of `menu.h` (which calls `anadirAlien` in `omnitrix.h` at line 86 and `anadirSplay` at line 26; the latter uses `add` from the `Node` and `SplayTree` classes, declared in `arbol.h` at lines 67 and 542, respectively).  

Finally, it is used in `eliminarADN` in `menu.h` at line 295 (which calls `eliminarAlienSplay` declared at line 29 of `omnitrix.h`, which in turn uses `remove` from the `Node` and `SplayTree` classes, declared in `arbol.h` at lines 189 and 554, respectively).

---

## SICT0301B: Component Evaluation

### Presents correct and complete test cases for all functions and procedures of the program

The test cases I recommend are as follows:

- Add and remove aliens, then display the alien list to verify that all added aliens are present and in the correct insertion order; afterward, close and reopen the program to test data persistence.
- Test different sorting scenarios by sorting the default 20 aliens and then adding another alien provided by the user, in order to test both Insertion Sort and Merge Sort.
- Adding an alien, free selection, and deleting dangerous DNA involve the Splay Tree; these operations can be performed and followed by requesting the alien list or using `printTree`.
- Data persistence can be tested by modifying aliens (adding and/or deleting), closing the program, reopening it, and then displaying the alien list.

---

### Provides a correct and complete complexity analysis for the entire program and its components

#### Queue, Splay Tree, and Alien Hash

- **Guided selection function (queue):**  
  Since the aliens are already ordered, retrieving the next alien is O(1), as it only accesses and removes the first element. Sorting is discussed separately; however, if combined, the complexity would be O(n log n) when there are more than 20 aliens and O(n²) otherwise. According to some sources, when there are very few elements, Insertion Sort can be as good as or even better than Merge Sort, so the complexity can be considered O(n log n).

- **Display alien by name (Hash):**  
  This function is where the hash truly shines, since no data updates are required and neither the Splay Tree nor the vector needs to be used.

- **Free selection function (Splay Tree find + Hash):**  
  The Hash can achieve O(1) in very favorable cases, but overall the complexity is O(log n) due to the Splay Tree operations.

- **Add alien function (insert Splay Tree / vector / Hash):**  
  This operation is O(log n), as it behaves similarly to a search that inserts the new alien at its appropriate position and at the end of the vector. Although Hash insertion is O(1), the other structures increase the overall complexity.

- **Delete alien function (delete Splay Tree / vector):**  
  If only a Splay Tree were used, the complexity would be O(log n); however, since the vector must also be processed, the worst-case complexity increases to O(n), as the vector is scanned to locate the alien by name.

---

#### Alien sorting (20 or fewer)

- **Guided selection based on one parameter / balanced:** O(n²), due to the use of Insertion Sort.
- **Guided selection based on two parameters:** O(n²), since Insertion Sort is applied to a new vector generated from the sum of two attributes.

---

#### Alien sorting (21 or more)

- **Guided selection based on one parameter / balanced:** O(n log n) in all cases.
- **Guided selection based on two parameters:** O(n log n), applied to a new vector generated from the sum of two attributes.

---

#### Tree usage

- **Create alien tree:** A tree is created on each program execution based on the registered connections.
- **Add alien (node) to tree:** O(log n)
- **Find alien (node) in tree:** O(log n); this is the basis for other operations such as adding or deleting, which is why they share similar time complexity.
- **Delete alien (node) from tree:** O(log n)

---

## SICT0303B: Implements Scientific Actions

### Implements correct and useful mechanisms to query information from data structures within a program

The program allows displaying aliens based on five composite criteria, based on a selection of two out of four attributes, or by name.  
It enables retrieving information about all aliens or a specific one.

---

### Implements correct and useful file reading mechanisms within a program

Aliens and their information, along with nodes and their connections, are stored in a file called `ADN.txt`.

---

### Implements correct and useful file writing mechanisms within a program

Aliens are saved at the end of each program execution to avoid re-registering them every time they are needed.  
If the Omnitrix is initialized with no aliens, the 20 default aliens are inserted to allow easy testing of Insertion Sort and Merge Sort.

