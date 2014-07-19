#ifndef TREENODE_H
#define TREENODE_H

class TreeNode
{
public:
	TreeNode()
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	TreeNode(int val)
	{
		value = val;
		left = nullptr;
		parent = nullptr;
		right = nullptr;
	}

	int value;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
};

#endif
