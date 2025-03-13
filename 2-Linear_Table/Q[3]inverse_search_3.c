// 快慢指针法
ElemSet Find(List list, int m)
{
    // 检查空表
    if (list->next == NULL)
        return ERROR;

    // 定义快慢指针
    List fast = list->next;
    List slow = list->next;

    // 快指针先走,走不了m步则报错
    for (int i = 0; i < m; i ++)
    {
        if (fast == NULL)
            return ERROR;
        fast = fast->next;
    }

    // 快指针和慢指针一起走
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow->data;
}
