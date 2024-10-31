#include <iostream>
using namespace std;

class Node
{
public:
    char data;
    Node *next;
    Node(char value) : data(value), next(nullptr) {}
};

class Stack
{
private:
    Node *top;

public:
    Stack() : top(nullptr) {}

    void push(char value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    char pop()
    {
        if (isEmpty())
        {
            return '\0';
        }
        char value = top->data;
        Node *temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    char peek()
    {
        if (isEmpty())
        {
            return '\0';
        }
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    ~Stack()
    {
        while (top != nullptr)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }
};

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

char *infixToPostfix(const char *infix)
{
    Stack stack;
    int i = 0, j = 0;
    int len = 0;
    while (infix[len] != '\0')
        len++;
    char *postfix = new char[len * 2];

    while (infix[i] != '\0')
    {
        char c = infix[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix[j++] = stack.pop();
            }
            if (!stack.isEmpty())
            {
                stack.pop();
            }
        }
        else if (isOperator(c))
        {
            while (!stack.isEmpty() && stack.peek() != '(' &&
                   precedence(stack.peek()) >= precedence(c))
            {
                postfix[j++] = stack.pop();
            }
            stack.push(c);
        }
        i++;
    }

    while (!stack.isEmpty())
    {
        postfix[j++] = stack.pop();
    }

    postfix[j] = '\0';
    return postfix;
}

char *infixToPrefix(const char *infix)
{

    int len = 0;
    while (infix[len] != '\0')
        len++;

    char *reversed = new char[len + 1];
    int j = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        char c = infix[i];
        if (c == '(')
            reversed[j] = ')';
        else if (c == ')')
            reversed[j] = '(';
        else
            reversed[j] = c;
        j++;
    }
    reversed[j] = '\0';

    char *postfix = infixToPostfix(reversed);
    delete[] reversed;

    len = 0;
    while (postfix[len] != '\0')
        len++;
    char *prefix = new char[len + 1];
    j = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        prefix[j++] = postfix[i];
    }
    prefix[j] = '\0';

    delete[] postfix;
    return prefix;
}

int evaluatePostfix(const char *postfix)
{
    Stack stack;
    int i = 0;

    while (postfix[i] != '\0')
    {
        char c = postfix[i];

        if (c >= '0' && c <= '9')
        {
            stack.push(c - '0');
        }
        else if (isOperator(c))
        {
            int val1 = stack.pop();
            int val2 = stack.pop();

            switch (c)
            {
            case '+':
                stack.push(val2 + val1);
                break;
            case '-':
                stack.push(val2 - val1);
                break;
            case '*':
                stack.push(val2 * val1);
                break;
            case '/':
                stack.push(val2 / val1);
                break;
            case '^':
            {
                int result = 1;
                for (int j = 0; j < val1; j++)
                {
                    result *= val2;
                }
                stack.push(result);
                break;
            }
            }
        }
        i++;
    }

    return stack.pop();
}

int evaluatePrefix(const char *prefix)
{

    int len = 0;
    while (prefix[len] != '\0')
        len++;

    Stack stack;

    for (int i = len - 1; i >= 0; i--)
    {
        char c = prefix[i];

        if (c >= '0' && c <= '9')
        {
            stack.push(c - '0');
        }
        else if (isOperator(c))
        {
            int val1 = stack.pop();
            int val2 = stack.pop();

            switch (c)
            {
            case '+':
                stack.push(val1 + val2);
                break;
            case '-':
                stack.push(val1 - val2);
                break;
            case '*':
                stack.push(val1 * val2);
                break;
            case '/':
                stack.push(val1 / val2);
                break;
            case '^':
            {
                int result = 1;
                for (int j = 0; j < val2; j++)
                {
                    result *= val1;
                }
                stack.push(result);
                break;
            }
            }
        }
    }

    return stack.pop();
}

int main()
{
    char choice;
    char infix[100];

    do
    {
        cout << "\nExpression Converter and Evaluator Menu:\n";
        cout << "1. Convert Infix to Postfix\n";
        cout << "2. Convert Infix to Prefix\n";
        cout << "3. Evaluate Postfix Expression\n";
        cout << "4. Evaluate Prefix Expression\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case '1':
        {
            cout << "Enter infix expression: ";
            cin.getline(infix, 100);
            char *postfix = infixToPostfix(infix);
            cout << "Postfix expression: " << postfix << endl;
            delete[] postfix;
            break;
        }

        case '2':
        {
            cout << "Enter infix expression: ";
            cin.getline(infix, 100);
            char *prefix = infixToPrefix(infix);
            cout << "Prefix expression: " << prefix << endl;
            delete[] prefix;
            break;
        }

        case '3':
        {
            cout << "Enter postfix expression: ";
            cin.getline(infix, 100);
            int result = evaluatePostfix(infix);
            cout << "Result: " << result << endl;
            break;
        }

        case '4':
        {
            cout << "Enter prefix expression: ";
            cin.getline(infix, 100);
            int result = evaluatePrefix(infix);
            cout << "Result: " << result << endl;
            break;
        }

        case '5':
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != '5');

    return 0;
}
