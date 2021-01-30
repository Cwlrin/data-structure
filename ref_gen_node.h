#ifndef __GEN_NODE_H__
#define __GEN_NODE_H__

#ifndef __REF_GEN_LIST_NODE_TYPE__
#define __REF_GEN_LIST_NODE_TYPE__
enum RefGenListNodeType {HEAD, ATOM, LIST};
#endif

// �����������������ģ��
template<class ElemType>
struct RefGenListNode
{
// ���ݳ�Ա:
	RefGenListNodeType tag;				
		// ��־��Ա,HEAD(0):ͷ���, ATOM(1):ԭ�ӽṹ, LIST(2):����
	RefGenListNode<ElemType> *nextLink;	// ָ��ͬһ���е���һ�����ָ���Ա
	union
	{
		int ref;						// tag=HEAD,ͷ���,���������
		ElemType atom;					// tag=ATOM,���ԭ�ӽ������ݳ�Ա
		RefGenListNode<ElemType> *subLink;	// tag=LISK,���ָ���ӱ��ָ���Ա
	}; 

// ���캯��ģ��:
	RefGenListNode(RefGenListNodeType tg = HEAD, RefGenListNode<ElemType> *next = NULL);
		// �ɱ�־tg��ָ��next�������������������
};

// �����������������ģ���ʵ�ֲ���
template<class ElemType>
RefGenListNode<ElemType>::RefGenListNode(RefGenListNodeType tg, RefGenListNode<ElemType> *next)
// ����������ɱ�־tg��ָ��next�������������������
{
	tag = tg;							// ��־
	nextLink = next;					// ���
}

#endif
