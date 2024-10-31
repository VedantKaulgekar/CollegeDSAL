#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        this->data = value;
        left = nullptr;
        right = nullptr;
    }

    Node()
    {
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }

        return node;
    }

    Node *deleteNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (key < root->data)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->data)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    void levelOrder(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        Node *queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        while (front < rear)
        {
            Node *current = queue[front++];
            cout << current->data << " ";

            if (current->left != nullptr)
            {
                queue[rear++] = current->left;
            }

            if (current->right != nullptr)
            {
                queue[rear++] = current->right;
            }
        }
        cout << endl;
    }

public:
    Node *root;

    BST() : root(nullptr) {}

    void insert(int value)
    {
        root = insert(root, value);
    }

    void deleteNode(int value)
    {
        root = deleteNode(root, value);
    }

    void levelOrder()
    {
        levelOrder(root);
    }
};

int main()
{
    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Level-order traversal of the tree:\n";
    bst.levelOrder();

    cout << "Deleting 20\n";
    bst.deleteNode(20);

    cout << "Level-order traversal of the tree after deleting 20:\n";
    bst.levelOrder();

    cout << "Deleting 30\n";
    bst.deleteNode(30);

    cout << "Level-order traversal of the tree after deleting 30:\n";
    bst.levelOrder();

    cout << "Deleting 50\n";
    bst.deleteNode(50);

    cout << "Level-order traversal of the tree after deleting 50:\n";
    bst.levelOrder();

    return 0;
}
