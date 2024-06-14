#include <bits/stdc++.h>
using namespace std;

// Structure for Product
struct Product
{
    string name;
    string category;
    string productID;
    int price;

    void display() const
    {
        cout << "Product ID: " << productID << ", Name: " << name
             << ", Category: " << category << ", Price: " << price << " BDT" << endl;
    }
};

// Structure for Order
struct Order
{
    string orderID;
    string productID;
    int quantity;
    int totalPrice;

    void display() const
    {
        cout << "Order ID: " << orderID << ", Product ID: " << productID
             << ", Quantity: " << quantity << ", Total Price: " << totalPrice << " BDT" << endl;
    }
};

// Global data structures
unordered_map<string, Product> productTable;  // Hash table for quick lookup

struct ProductNode
{
    Product data;
    ProductNode* left;
    ProductNode* right;
    ProductNode(Product p) : data(p), left(nullptr), right(nullptr) {}
};

ProductNode* productBST = nullptr;  // BST for sorted display

list<Order> orderList;  // Linked list for orders

int nextProductID = 1;  // Variable to track the next product ID

// Helper function to insert a product into the BST
// Data structure used: Binary Search Tree (BST)
ProductNode* insertProduct(ProductNode* node, Product p)
{
    if (node == nullptr) return new ProductNode(p);
    if (p.name < node->data.name)
        node->left = insertProduct(node->left, p);
    else
        node->right = insertProduct(node->right, p);
    return node;
}

// Helper function for inorder traversal of BST
// Data structure used: Binary Search Tree (BST)
void inorderDisplay(ProductNode* node)
{
    if (node == nullptr) return;
    inorderDisplay(node->left);
    node->data.display();
    inorderDisplay(node->right);
}

// Function to add a new product with auto-generated productID
// Data structure used: Hash Table (unordered_map)
void addProduct() {
    Product p;
    cout << "\nEnter product details:\n";
    cout << "Product Name: ";
    getline(cin >> ws, p.name);
    cout << "Category: ";
    getline(cin, p.category);
    cout << "Product ID: ";
    getline(cin, p.productID);
    cout << "Price in BDT: ";
    cin >> p.price;

    productTable[p.productID] = p;
    productBST = insertProduct(productBST, p);
    cout << "Product added successfully!\n";
}

// Function to search for a product by name
// Data structure used: Binary Search Tree (BST)
void searchProduct()
{
    string searchName;
    cout << "\nEnter the name of the product to search: ";
    getline(cin >> ws, searchName);

    ProductNode* current = productBST;
    while (current != nullptr)
    {
        if (current->data.name == searchName)
        {
            cout << "\nProduct found:\n";
            current->data.display();
            return;
        }
        if (searchName < current->data.name)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    cout << "Product not found!\n";
}

// Function to display all products sorted by name
// Data structure used: Binary Search Tree (BST)
void displayProducts()
{
    if (productBST == nullptr)
    {
        cout << "\nNo products in the inventory!\n";
    }
    else
    {
        cout << "\nAll products in the inventory:\n";
        inorderDisplay(productBST);
    }
}

// Function to place an order
void placeOrder()
{
    Order o;
    cout << "\nEnter order details:\n";
    cout << "Order ID: ";
    getline(cin >> ws, o.orderID);
    cout << "Product ID: ";
    getline(cin, o.productID);
    cout << "Quantity: ";
    cin >> o.quantity;

    auto it = productTable.find(o.productID);
    if (it != productTable.end())
    {
        o.totalPrice = it->second.price * o.quantity;
        orderList.push_back(o);
        cout << "Order placed successfully!\n";
    }
    else
    {
        cout << "Product not found!\n";
    }
}

// Function to display all orders
void displayOrders()
{
    if (orderList.empty())
    {
        cout << "\nNo orders placed yet!\n";
    }
    else
    {
        cout << "\nAll orders:\n";
        for (auto& o : orderList)
        {
            o.display();
        }
    }
}

int main()
{
    cout<<"hello"<<endl;
    int choice;
    do
    {
        cout << "\n                                                ------ Menu ------\n\n";
        cout << "                                                1. Add Product\n";
        cout << "                                                2. Search Product\n";
        cout << "                                                3. Display Products\n";
        cout << "                                                4. Place Order\n";
        cout << "                                                5. Display Orders\n";
        cout << "                                                6. Exit\n\n";
        cout << "                                                Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            addProduct();
            break;
        }
        case 2:
            searchProduct();
            break;
        case 3:
            displayProducts();
            break;
        case 4:
            placeOrder();
            break;
        case 5:
            displayOrders();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please enter a number from 1 to 6.\n";
            break;
        }
    }
    while (choice != 6);

    return 0;
}
