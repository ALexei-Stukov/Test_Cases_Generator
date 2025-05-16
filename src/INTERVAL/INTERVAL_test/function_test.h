#include "interval.h"

#ifndef GOOGLETEST_SAMPLES_SAMPLE1_H_
#define GOOGLETEST_SAMPLES_SAMPLE1_H_

    //构造（包括初始化）并检测区间是否合法
    bool build_and_check_is_valid();
    
    //设置开闭类型并正确生效
    bool set_close();

    // 区间取反（相对于全体实数范围）,将产生1或2个区间。如果是全体实数，则不产生区间。
    bool invert();

    //区间内随机数生成，可以生成int型或者double型。只需检查产生的值是否在区间内即可。
    bool random_in_range();

    //区间内临界值生成。不仅要检查是否合规，还要检查离区间端点是否足够近。在目前的设计中，可以取距离<=1作为判断依据
    bool critical_random_in_range();
    
#endif  // GOOGLETEST_SAMPLES_SAMPLE1_H_
