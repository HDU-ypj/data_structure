/************************************
>	作	  者：杭电羊皮卷
>	文件名称：weixin:QQ2997675141
>   创建日期：2022年08月12日
>   描    述：
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TREE_TYPE char
#define EMPTY '#'
#define END	'\0'	//构建结束标志

//设计树的节点
typedef struct TreeNode
{
	TREE_TYPE data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef TreeNode *Tree;

/**************************************************
** @func:创建树的节点
**************************************************/
TreeNode* create_tree_node(TREE_TYPE data)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}


/**************************************************
** @func:构建一颗数,前序创建一棵树
**************************************************/
TreeNode* create_tree(void)
{
	TREE_TYPE data=0;
	scanf("%c",&data);
	if(data == EMPTY)	return NULL;
	TreeNode* node = create_tree_node(data);
	node->left = create_tree();
	node->right = create_tree();
	return node;
}

/**************************************************
** @func:构建一棵树
**************************************************/
//依赖函数
TreeNode* _create_tree(TREE_TYPE** str)
{
	if(**str == END || **str == EMPTY)	return NULL;
	TreeNode* node = create_tree_node(**str);
	*str+=1;
	node->left = _create_tree(str);
	*str+=1;
	node->right = _create_tree(str);
	return node;
}

TreeNode* create_tree_1(TREE_TYPE* str)
{
	_create_tree(&str);
}

/**************************************************
** @func:求树的高度
**************************************************/
int high_tree(TreeNode* root)
{
	if(root == NULL)	return 0;
	int lh=0;
	int rh=0;
	lh = high_tree(root->left);
	rh = high_tree(root->right);
	return lh>rh?lh+1:rh+1;
}

/**************************************************
** @func:求树的密度
**************************************************/
int density_tree(TreeNode* root)
{
	if(root == NULL)	return 0;
	return density_tree(root->left)+density_tree(root->right)+1;
}

/**************************************************
** @func:求对应数据的左子树
**************************************************/
TreeNode* left_tree(TreeNode* root,TREE_TYPE data)
{
	if(NULL == root)	return NULL;
	if(root->data == data)
	{
		return root->left;
	}
	else
	{
		TreeNode* lnode = left_tree(root->left,data);
		if(NULL != lnode)	return lnode;
		TreeNode* rnode = left_tree(root->right,data);
		return rnode;
	}
}


/**************************************************
** @func:插入一个节点，该节点只能是叶子节点,
** 		仅仅是为了演示以下二叉树的特性
**************************************************/
bool insert_tree(TreeNode* root,TREE_TYPE pdata,TREE_TYPE data)
{
	if(NULL == root)	return false;
	if(root->data == pdata)
	{
		if(NULL == root->left)
		{
			return root->left = create_tree_node(data);
		}
		if(NULL == root->right)
		{
			return root->right = create_tree_node(data);
		}
		return false;
	}
	bool lflag= insert_tree(root->left,pdata,data);
	if(lflag)	return true;
	bool rflag = insert_tree(root->right,pdata,data);
	return rflag;
}

/**************************************************
** @func:删除树的一个节点，要求必须为叶子节点，
** 仅为了演示树的结构，后面的二叉排序要求可以实现删除任意节点
**************************************************/
bool del_tree(TreeNode** root,TREE_TYPE data)
{
	if(NULL == root)	return false;
	if((*root)->data == data)
	{
		if((*root)->left || (*root)->right)	return false;
		free((*root));
		(*root) = NULL;
	}
}

/**************************************************
** @func:递归销毁一个树结构
**************************************************/
void destory_tree(TreeNode* root)
{
	if(NULL == root)	return;
	destory_tree(root->left);
	destory_tree(root->right);
	free(root);
}

/**************************************************
** @func:先序遍历二叉树
**************************************************/
void dlr_show(Tree tree)
{
	if(NULL == tree)	return;
	printf("%c ",tree->data);
	dlr_show(tree->left);
	dlr_show(tree->right);
}


/**************************************************
** @func:中序遍历
**************************************************/
void ldr_show(Tree tree)
{
	if(NULL == tree)	return;
	ldr_show(tree->left);
	printf("%c ",tree->data);
	ldr_show(tree->right);
}

/**************************************************
** @func:后序遍历
**************************************************/
void lrd_show(Tree tree)
{
	if(NULL == tree)	return;
	ldr_show(tree->left);
	ldr_show(tree->right);
	printf("%c ",tree->data);
}



/**************************************************
** @func:主函数测试
**************************************************/
char* str="ABD#G###CE##F##";
int main(int argc,const char* argv[])
{
	Tree tree;
//	tree = create_tree();
	tree = create_tree_1(str);
	
	insert_tree(tree,'B','X');



	
	dlr_show(tree);
	printf("\n");
	ldr_show(tree);
	printf("\n");
	lrd_show(tree);
	printf("\n");
	return 0;
}
