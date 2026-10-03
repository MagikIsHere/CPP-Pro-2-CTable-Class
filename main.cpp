#include <iostream>
#include <string>

class CTable {
private:
    std::string s_name;
    int* pi_table;
    int i_table_len;
    const static int DEFAULT_LEN = 10;
    const std::string DEFAULT_NAME = "default_table";

public:
    // 1. Default Constructor
    CTable() {
        s_name = DEFAULT_NAME;
        i_table_len = DEFAULT_LEN;
        pi_table = new int[i_table_len];
        std::cout << "without: '" << s_name << "'\n";
    }

    // 2. Parameterized Constructor
    CTable(std::string sName, int iTableLen) {
        s_name = sName;
        i_table_len = iTableLen;
        pi_table = new int[i_table_len];
        std::cout << "parameter: '" << s_name << "'\n";
    }

    // 3. Copy Constructor
    CTable(const CTable& pcOther) {
        s_name = pcOther.s_name + "_copy";
        i_table_len = pcOther.i_table_len;
        pi_table = new int[i_table_len];

        // Deep copy of the array elements
        for (int i = 0; i < i_table_len; ++i) {
            pi_table[i] = pcOther.pi_table[i];
        }

        std::cout << "copy: '" << s_name << "'\n";
    }

    // Destructor
    ~CTable() {
        delete[] pi_table;
        std::cout << "remowing: '" << s_name << "'\n"; // Note: spelling matches homework prompt
    }

    // Setters & Methods
    void vSetName(std::string sName) {
        s_name = sName;
    }

    bool bSetNewSize(int iTableLen) {
        if (iTableLen <= 0) return false;

        int* pi_new_table = new int[iTableLen];
        int elements_to_copy = (iTableLen < i_table_len) ? iTableLen : i_table_len;

        for (int i = 0; i < elements_to_copy; ++i) {
            pi_new_table[i] = pi_table[i];
        }

        delete[] pi_table;
        pi_table = pi_new_table;
        i_table_len = iTableLen;
        return true;
    }

    // Clone method
    CTable* pcClone() {
        return new CTable(*this); // Reuses copy constructor logic to avoid redundant code
    }
};

// Procedures for testing pass-by-pointer vs pass-by-value
void v_mod_tab(CTable* pcTab, int iNewSize) {
    if (pcTab != nullptr) {
        pcTab->bSetNewSize(iNewSize);
    }
}

void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}

int main() {
    std::cout << "--- Testing Constructors & Destructors ---\n";
    {
        CTable c1;
        CTable c2("custom", 5);
        CTable c3 = c2; // Triggers copy constructor
    } // c1, c2, c3 destroyed here out of scope

    std::cout << "\n--- Testing Clone Method ---\n";
    CTable c_tab("original", 4);
    CTable* pc_new_tab = c_tab.pcClone();
    delete pc_new_tab;

    std::cout << "\n--- Testing v_mod_tab (Pointer vs Value) ---\n";
    CTable c_test("test_obj", 3);
    
    std::cout << "Calling v_mod_tab with pointer:\n";
    v_mod_tab(&c_test, 8); // Modifies original object directly, no extra copies created

    std::cout << "Calling v_mod_tab with value:\n";
    v_mod_tab(c_test, 12); // Creates a temporary copy (copy constructor + destructor called)

    return 0;
}