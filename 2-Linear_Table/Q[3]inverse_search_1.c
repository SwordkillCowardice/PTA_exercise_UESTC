ElemSet Find(List list, int m)
{
    // 定义长度，临时指针
    int length = 0;
    List tmp = list;

    // 遍历链表，求出长度
    while (list->next != NULL)
    {
        list = list->next;
        length++;
    }

    // 判断访问合法性
    if (length < m)
        return ERROR;

    // 查找
    int order = length - m + 1;
    for (int i = 0; i < order; i++)
    {
         tmp = tmp->next;
    }

    return tmp->data;
}
