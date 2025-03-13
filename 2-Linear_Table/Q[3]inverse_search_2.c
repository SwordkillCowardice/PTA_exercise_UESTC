// 先求链表逆序，找出元素后再还原

// 定义逆序函数
List inverse(List p, List head, const List loc)
{
    // 基本情况
    if (p->next == NULL)
    {
        head->next = p;
        return head;
    }

    // 递归情况
    else
    {
        inverse(p->next, head, loc);
        p->next->next = p;

        // 判断是否为新的尾部节点
        if (p == loc)
            p->next = NULL;

        return head;
    }
}

// 顺序查找
ElemSet Find(List list, int m)
{
    // 判断是否空表
    if (list->next == NULL)
        return ERROR;

    // 链表取反
    const List sign = list->next;
    list = inverse(list->next, list, sign);
    List tmp = list;

    // 循环,若m大于表长，则报错，否则完成循环
    for (int i = 0; i < m; i++)
    {
        tmp = tmp->next;
        if (tmp == NULL)
            return ERROR;
    }

    // 还原链表
    const List new = list->next;
    list = inverse(list->next, list, new);

    return tmp->data;
}
