/**************************************************
>	作	  者：杭电羊皮卷
>	文件名称：weixin:QQ2997675141
>   创建日期：2022年08月12日
>   描    述：排序二叉树的相关操作
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//有序二叉树
typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef TreeNode	*Tree;

//创建一个节点
TreeNode* create_node(int data)
{
	TreeNode* node  = malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/**************************************************
** @func:依赖函数，添加节点
**************************************************/
void _insert_tree(Tree* root,Tree node)
{
	if(NULL == *root)
	{
		*root = node;
		return;
	}
	if(node->data < (*root)->data)
	{
		_insert_tree(&(*root)->left,node);
	}
	else
	{
		_insert_tree(&(*root)->right,node);
	}
}

/**************************************************
** @func:添加数据
**************************************************/
void insert_tree(Tree* root,int data)
{
	_insert_tree(root,create_node(data));
}

/**************************************************
** @func:中序遍历打印
**************************************************/
void ldr_show(Tree tree)
{
	if(tree == NULL)	return;
	ldr_show(tree->left);
	printf("%d ",tree->data);
	ldr_show(tree->right);
}

/**************************************************
** @func:查找
**************************************************/
bool query_tree(Tree root,int data)
{
	if(root == NULL)	return false;
	if(root->data == data)	return true;
	if(data < root->data)
		return query_tree(root->left,data);
	else
		return query_tree(root->right,data);		
}

/**************************************************
** @func:密度
**************************************************/
int density_tree(Tree root)
{
	if(root == NULL)	return 0;
	return density_tree(root->left)+density_tree(root->right)+1;
}

/**************************************************
** @func:高度
**************************************************/
int high_tree(Tree root)
{
	if(root == NULL)	return 0;
	int hight_l = high_tree(root->left);
	int hight_r = high_tree(root->right);
	return hight_l>hight_r?hight_l+1:hight_r+1;
}

/**************************************************
** @func:销毁
**************************************************/
void destroy_tree(Tree tree)
{
	if(tree == NULL)	return;
	destroy_tree(tree->left);
	destroy_tree(tree->right);
	free(tree);
}

/**************************************************
** @func:按中序进行访问

**************************************************/
//依赖函数
bool _access_tree(Tree root,int* cnt,size_t index,int* val)
{
	if(root == NULL)	return false;
	bool lflag = _access_tree(root->left,cnt,index,val);
	if(lflag == true)	return true;
	if(*cnt==index)
	{
		*val = root->data;
		return true;
	}
	(*cnt)++;
	return _access_tree(root->right,cnt,index,val);
}
bool access_tree(Tree root,size_t index,int* val)
{
	int cnt =0;
	return _access_tree(root,&cnt,index,val);
}


/**************************************************
** @func:按值删除
**************************************************/
bool delete_value_tree(Tree *root,int data)
{
	if(NULL == *root)	return false;
	if((*root)->data == data)
	{
		TreeNode* temp = *root;
		*root = temp->left;
		_insert_tree(root,temp->right);
		free(temp);
		return true;
	}
	if(data < (*root)->data)
	{
		return delete_value_tree(&(*root)->left,data);
	}
	else
	{
		return delete_value_tree(&(*root)->right,data);
	}
}

/**************************************************
** @func:main测试主函数
**************************************************/
int main(int argc,const char* argv[])
{
	TreeNode* root = NULL;
	for(int i=0; i<10; i++)
	{
		int num = rand()%100;
		insert_tree(&root,num);
		printf("%d ",num);
	}

	delete_value_tree(&root,83);
	delete_value_tree(&root,77);

	printf("\nldr:");
	ldr_show(root);
	printf("\n%d",query_tree(root,83));
	int num = 0;
	access_tree(root,6,&num);
	printf("\naccess:%d\n",num);
}
