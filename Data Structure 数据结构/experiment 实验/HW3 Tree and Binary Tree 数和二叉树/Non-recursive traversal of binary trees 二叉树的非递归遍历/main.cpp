#include <iostream>
#include <string>
using namespace std;
 
struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : value(x), left(nullptr), right(nullptr) {}
};
 
void postOrderTraversal(TreeNode* node, string& result) {
    if (!node) return;
    postOrderTraversal(node->left, result);
    postOrderTraversal(node->right, result);
    result += node->value;
}
 
void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
 
TreeNode* buildTree(int& index, int total_ops) {
    if (index >= total_ops) return nullptr; // 超过指令数量，返回空指针
 
    string operation;
    cin >> operation;
 
    if (operation == "push") {
        char value;
        cin >> value;
        TreeNode* node = new TreeNode(value);
        index ++; // 移动至下一个操作，考虑到push和pop都要占用一个位置
        node->left = buildTree(index, total_ops); // 递归构建左子树
        node->right = buildTree(index, total_ops); // 递归构建右子树
        return node;
    }
    else if (operation == "pop") {
        index++; // 只移动到下一个操作
        return nullptr; // pop操作表示当前子树结束
    }
 
    return nullptr; // 无效操作
}
 
int main() {
    int n;
    cin >> n;
    int total_ops = 2 * n; // 总指令数，包括push和pop
 
    int index = 0;
    TreeNode* root = buildTree(index, total_ops);
 
    string result;
    postOrderTraversal(root, result);
    cout << result << endl;
 
    deleteTree(root); // 清理内存
    return 0;
}
