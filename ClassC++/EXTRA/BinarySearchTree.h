#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <queue>
#include <stack>

template <typename T>
struct TreeNode
{
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& value)
        : data(value), left(nullptr), right(nullptr)
    {
    }
};

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree()
        : m_root(nullptr), m_size(0)
    {
    }

    BinarySearchTree(const BinarySearchTree& other)
        : m_root(nullptr), m_size(0)
    {
        m_root = copyTree(other.m_root);
        m_size = other.m_size;
    }

    ~BinarySearchTree()
    {
        clear(m_root);
        m_root = nullptr;
        m_size = 0;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
        if (this != &other)
        {
            clear(m_root);
            m_root = copyTree(other.m_root);
            m_size = other.m_size;
        }
        return *this;
    }

    void insert(const T val)
    {
        insertRecursive(m_root, val);
        m_size++;
    }

    int size() const
    {
        return m_size;
    }

    void printInOrder() const
    {
        printInOrderRecursive(m_root);
        std::cout << std::endl;
    }

    void printPreOrder() const
    {
        printPreOrderRecursive(m_root);
        std::cout << std::endl;
    }

    void printPostOrder() const
    {
        printPostOrderRecursive(m_root);
        std::cout << std::endl;
    }

    void printBreadthOrder() const
    {
        if (m_root == nullptr)
        {
            std::cout << std::endl;
            return;
        }

        std::queue<TreeNode<T>*> q;
        q.push(m_root);

        while (!q.empty())
        {
            TreeNode<T>* current = q.front();
            q.pop();

            std::cout << current->data << " ";

            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }

        std::cout << std::endl;
    }

    void printDepthOrder() const
    {
        if (m_root == nullptr)
        {
            std::cout << std::endl;
            return;
        }

        std::stack<TreeNode<T>*> s;
        s.push(m_root);

        while (!s.empty())
        {
            TreeNode<T>* current = s.top();
            s.pop();

            std::cout << current->data << " ";

            if (current->right != nullptr)
            {
                s.push(current->right);
            }
            if (current->left != nullptr)
            {
                s.push(current->left);
            }
        }

        std::cout << std::endl;
    }

    void printByLevels() const
    {
        if (m_root == nullptr)
        {
            return;
        }

        std::queue<TreeNode<T>*> q;
        q.push(m_root);

        int level = 1;

        while (!q.empty())
        {
            int nodesThisLevel = (int)q.size();
            std::cout << "Level " << level << ": ";

            for (int i = 0; i < nodesThisLevel; i++)
            {
                TreeNode<T>* current = q.front();
                q.pop();

                std::cout << current->data;

                if (i < nodesThisLevel - 1)
                {
                    std::cout << " ";
                }

                if (current->left != nullptr)
                {
                    q.push(current->left);
                }
                if (current->right != nullptr)
                {
                    q.push(current->right);
                }
            }

            std::cout << std::endl;
            level++;
        }
    }

    void height() const
    {
        std::cout << treeHeight(m_root) << std::endl;
    }

private:
    TreeNode<T>* m_root;
    int m_size;

    void insertRecursive(TreeNode<T>*& node, const T val)
    {
        if (node == nullptr)
        {
            node = new TreeNode<T>(val);
            return;
        }

        if (val < node->data)
        {
            insertRecursive(node->left, val);
        }
        else
        {
            insertRecursive(node->right, val);
        }
    }

    TreeNode<T>* copyTree(TreeNode<T>* otherNode)
    {
        if (otherNode == nullptr)
        {
            return nullptr;
        }

        TreeNode<T>* newNode = new TreeNode<T>(otherNode->data);
        newNode->left = copyTree(otherNode->left);
        newNode->right = copyTree(otherNode->right);
        return newNode;
    }

    void clear(TreeNode<T>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    void printInOrderRecursive(TreeNode<T>* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        printInOrderRecursive(node->left);
        std::cout << node->data << " ";
        printInOrderRecursive(node->right);
    }

    void printPreOrderRecursive(TreeNode<T>* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        std::cout << node->data << " ";
        printPreOrderRecursive(node->left);
        printPreOrderRecursive(node->right);
    }

    void printPostOrderRecursive(TreeNode<T>* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        printPostOrderRecursive(node->left);
        printPostOrderRecursive(node->right);
        std::cout << node->data << " ";
    }

    int treeHeight(TreeNode<T>* node) const
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = treeHeight(node->left);
        int rightHeight = treeHeight(node->right);

        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        return rightHeight + 1;
    }
};

#endif
