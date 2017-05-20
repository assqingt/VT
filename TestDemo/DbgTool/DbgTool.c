#include "DbgTool.h"
p_save_handlentry CreateList() {
	ULONG i;

	p_save_handlentry phead = (p_save_handlentry)ExAllocatePool(NonPagedPool, sizeof(_save_handlentry));
	//ûʲô��  ���������ڴ� Ȼ��һֱ����taill
	p_save_handlentry ptail = phead;
	ptail->next = NULL;
	p_save_handlentry pnew = (p_save_handlentry)ExAllocatePool(NonPagedPool, sizeof(_save_handlentry));

	pnew->dbgProcessId = 0;
	pnew->dbgProcessStruct = 0;
	pnew->head = NULL;
	ptail->next = pnew;
	pnew->next = NULL;
	ptail->head = NULL;
	return phead;

}
// �������� 
p_save_handlentry InsertList(HANDLE dbgProcessId,
	PEPROCESS dbgProcessStruct, p_save_handlentry phead) {




	p_save_handlentry p = phead->next;

	while (p != NULL)
	{
		if (p->next == NULL) {
			break;
		}
		p = p->next;
	}

	p_save_handlentry pnew = (p_save_handlentry)ExAllocatePool(NonPagedPool, sizeof(_save_handlentry));

	pnew->dbgProcessId = dbgProcessId;
	pnew->dbgProcessStruct = dbgProcessStruct;




	p->next = pnew;
	pnew->next = NULL;
	pnew->head = p;


	return pnew;
}
p_save_handlentry QueryList(p_save_handlentry phead, HANDLE dbgProcessId, PEPROCESS dbgProcessStruct) {


	p_save_handlentry p = phead->next;
	while (p != NULL)
	{
		if (dbgProcessId != NULL
			)
		{
			if (p->dbgProcessId == dbgProcessId) {

				return p;
			}
		}

		if (dbgProcessStruct != NULL
			)
		{
			if (p->dbgProcessStruct == dbgProcessStruct) {

				return p;
			}

		}

		p = p->next;
	}


	return NULL;
}
//ɾ���ڵ�
void DeleteList(p_save_handlentry pclid) {
	p_save_handlentry p, pp;



	if (pclid->head != NULL) {//ͷ��
		p = pclid->head;
		pp = pclid->next;


		if (pp == NULL) {//���ڵ�
			p->next = NULL;
			ExFreePool(pclid);

			return;
		}


		p->next = pp;//�������ڵ�
		pp->head = p;
		ExFreePool(pclid);

		return;
	}


}