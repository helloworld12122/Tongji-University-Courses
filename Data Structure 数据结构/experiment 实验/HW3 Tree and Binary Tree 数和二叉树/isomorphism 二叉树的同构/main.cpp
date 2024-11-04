#include <iostream>
#include <cstdlib>
 
struct TreeNode {
    char value;
    int left;
    int right;
};
 
// 使用动态分配的数组来代替 vector<TreeNode>
TreeNode* loadTree(int& rootIndex, int& nodeCount) {
    std::cin >> nodeCount;
 
    if (nodeCount == 0) {
        rootIndex = -1; // 没有节点时树的根为-1
        return nullptr;
    }
 
    TreeNode* tree = new TreeNode[nodeCount];
    bool* hasParent = new bool[nodeCount] {false};
 
    for (int i = 0; i < nodeCount; ++i) {
        char val;
        char left[10], right[10];
        std::cin >> val >> left >> right;
 
        tree[i].value = val;
        tree[i].left = (left[0] == '-' ? -1 : std::atoi(left));
        tree[i].right = (right[0] == '-' ? -1 : std::atoi(right));
 
        if (tree[i].left != -1) hasParent[tree[i].left] = true;
        if (tree[i].right != -1) hasParent[tree[i].right] = true;
    }
 
    for (int i = 0; i < nodeCount; ++i) {
        if (!hasParent[i]) {
            rootIndex = i;
            break;
        }
    }
 
    delete[] hasParent;
    return tree;
}
 
bool isIsomorphic(int root1, int root2, TreeNode* tree1, TreeNode* tree2) {
    if (root1 == -1 && root2 == -1) return true;
    if (root1 == -1 || root2 == -1) return false;
    if (tree1[root1].value != tree2[root2].value) return false;
 
    bool ll_rr = isIsomorphic(tree1[root1].left, tree2[root2].left, tree1, tree2) &&
        isIsomorphic(tree1[root1].right, tree2[root2].right, tree1, tree2);
    bool lr_rl = isIsomorphic(tree1[root1].left, tree2[root2].right, tree1, tree2) &&
        isIsomorphic(tree1[root1].right, tree2[root2].left, tree1, tree2);
 
    return ll_rr || lr_rl;
}
 
int calculateDepth(int root, TreeNode* tree) {
    if (root == -1) return 0;
    int leftDepth = calculateDepth(tree[root].left, tree);
    int rightDepth = calculateDepth(tree[root].right, tree);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}
 
int main() {
    int root1, root2, nodeCount1, nodeCount2;
    TreeNode* tree1 = loadTree(root1, nodeCount1);
    TreeNode* tree2 = loadTree(root2, nodeCount2);
 
    if (isIsomorphic(root1, root2, tree1, tree2)) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }
 
    std::cout << calculateDepth(root1, tree1) << std::endl;
    std::cout << calculateDepth(root2, tree2) << std::endl;
 
    delete[] tree1;
    delete[] tree2;
 
    return 0;
}
