这是一个针对整数测试生成测试目标的工具。

大多数情况下，只需提供输入参数的类型，就可以生成所有可能的参数组合。

目前支持两种参数：
整数范围类型
整数枚举类型

每个参数独立存在，不影响其它参数。

如果输入不是整数类型，那么不妨把它量化为整数类型。
事实上，非整数类型的测试比较难做，但该工具仍然能提供不少便利。

make doc可以制作文档，生成文档需要依赖于doxygen和graphviz
