# C++ CTable Class & Memory Management

An object-oriented C++ project implementing a custom dynamic array wrapper class (`CTable`) to explore constructors, destructor lifecycles, deep copying, and memory management patterns.

## 🚀 Features

* **Custom Constructors**:
  * **Default Constructor**: Initializes objects with predefined fallback constants and a default array size.
  * **Parameterized Constructor**: Accepts custom names and table lengths.
  * **Copy Constructor**: Performs a deep copy of arrays and appends `_copy` to the object's name.
* **Destructor**: Safely releases heap-allocated memory and logs object destruction.
* **Memory Management Methods**:
  * `vSetName`: Updates the identifier string.
  * `bSetNewSize`: Safely resizes the underlying array while preserving existing data.
  * `pcClone`: Returns a new heap-allocated clone of the object utilizing copy logic.

## 💡 Key Conceptual Findings

1. **`pcClone()` code reuse**: The `pcClone()` method is functionally identical to the copy constructor workflow. Calling `new CTable(*this)` inside `pcClone()` prevents redundant code duplication.
2. **Pass-by-Pointer vs Pass-by-Value (`v_mod_tab`)**:
   * Passing via pointer (`CTable *pcTab`) modifies the original object directly without creating overhead copies.
   * Passing via value (`CTable cTab`) invokes the copy constructor when entering the function and the destructor upon exit, modifying only a local copy.