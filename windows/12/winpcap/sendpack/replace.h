//
// 内存替换函数，修改自memfind函数
// 成功替换返回1,其它返回0
//
int memreplace(const void *in_block,     /* 数据块 */
              const size_t block_size,  /* 数据块长度 */
              const void *in_pattern,   /* 需要查找的数据 */
              const size_t pattern_size,        /* 查找数据的长度 */
              const void *in_newpattern, /* 要替换的新数据 */
              const size_t newpattern_size, /* 要替换的新数据的长度 */
              size_t * shift,   /* 移位表，应该是256*size_t的数组 */
              bool * init)
{                               /* 是否需要初始化移位表 */
	size_t byte_nbr,            /* Distance through block */
	match_size,                /* Size of matched part */
	limit;
    const unsigned char *match_ptr = NULL;
    const unsigned char *block = (unsigned char *) in_block,    /* Concrete pointer to block data */
        *pattern = (unsigned char *) in_pattern;        /* Concrete pointer to search value */

    if (block == NULL || pattern == NULL || shift == NULL)
        return (NULL);

/* 查找的串长应该小于 数据长度*/
    if (block_size < pattern_size)
        return 0;

    if (pattern_size == 0)      /* 空串匹配第一个 */
    {
		memcpy((void *) (block), in_newpattern, newpattern_size); // 找到并开始替换
        return 1;
    }

/* 如果没有初始化，构造移位表*/
    if (!init || !*init) {
        for (byte_nbr = 0; byte_nbr < 256; byte_nbr++)
            shift[byte_nbr] = pattern_size + 1;
        for (byte_nbr = 0; byte_nbr < pattern_size; byte_nbr++)
            shift[(unsigned char) pattern[byte_nbr]] = pattern_size - byte_nbr;

        if (init)
            *init = true;
    }

/* 开始搜索数据块，每次前进移位表中的数量 */
    limit = block_size - pattern_size + 1;
    for (byte_nbr = 0; byte_nbr < limit; byte_nbr += shift[block[byte_nbr + pattern_size]]) {
        if (block[byte_nbr] == *pattern) {
            /*
             * 如果第一个字节匹配，那么继续匹配剩下的
             */
            match_ptr = block + byte_nbr + 1;
            match_size = 1;

            do {
                if (match_size == pattern_size)
                {
					/* 找到并开始替换 */
					memcpy((void *) (block + byte_nbr), in_newpattern, newpattern_size);
                    return 1;
                }
            } while (*match_ptr++ == pattern[match_size++]);
        }
    }
    return 0;
}

//
//  内存替换函数，主要为了操作memreplace函数更方便
//
BOOL Replace(const void *in_block, const size_t block_size,
			 const char *szOld, const char *szNew)
{
    size_t shift[256];
    bool init = false;

    return memreplace(in_block, block_size, szOld, strlen(szOld), szNew,
		strlen(szNew), shift, &init);
}