#ifndef __HUFFMAN_TREE_NODE_H__
#define __HUFFMAN_TREE_NODE_H__

// �������������ģ��
template <class WeightType>
struct HuffmanTreeNode
{
// ���ݳ�Ա:
	WeightType weight;							// Ȩ���ݳ�Ա
	unsigned int parent, leftChild, rightChild;	// ˫��,���Һ��ӳ�Ա

// ���캯��ģ��:
	HuffmanTreeNode();							// �޲����Ĺ��캯��ģ��
	HuffmanTreeNode(WeightType w, int p = 0, int lChild = 0, int rChild = 0);
		// ��֪Ȩ,˫�׼����Һ��ӹ���ṹ
};

// �������������ģ���ʵ�ֲ���
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode()
// �������������ս��
{
	parent = leftChild = rightChild = 0;
}

template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int lChild, int rChild)									// �Һ���
// �������������һ��ȨΪw,˫��Ϊp,����ΪlChild,�Һ���ΪrChild�Ľ��
{
	weight = w;								// Ȩ
	parent = p;								// ˫��
	leftChild = lChild;						// ����
	rightChild = rChild;					// �Һ���
}

#endif
