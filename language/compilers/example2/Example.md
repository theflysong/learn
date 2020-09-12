# Example2

实现功能：将中缀表达式转化为前缀表达式(只含+ - * / ( ))
语法：list -> list + digit
      list -> list - digit
      list -> list * digit
      list -> list / digit
      list -> list + (list)
      list -> list - (list)
      list -> list * (list)
      list -> list / (list)
      digit -> {0|1|2|3|4|5|6|7|8|9}
实现语言：C++ ISO 11 标准, TMD-GCC 4.8.1 64-bit编译器, 无优化